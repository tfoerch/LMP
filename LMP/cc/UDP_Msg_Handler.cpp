/*
 * UDP_Msg_Handler.cpp
 *
 *  Created on: 20.02.2015
 *      Author: tom
 */

#include "UDP_Msg_Handler.hpp"
#include "IPCC_Impl.hpp"
#include "NetworkIFSocketIF.hpp"
#include "node/Node.hpp"
#include "neighbor/Neighbor.hpp"
#include <boost/asio/buffers_iterator.hpp>

namespace
{
  struct msg_variants_processor : boost::static_visitor<void>
  {
    msg_variants_processor(
        lmp::cc::IpccMsgReceiveIF&           ipcc,
      const boost::asio::ip::udp::endpoint&  sender_endpoint)
    : m_ipcc(ipcc),
      m_sender_endpoint(sender_endpoint)
    {}
    void operator()(const lmp::msg::ConfigMsg& config) const
    {
      m_ipcc.processReceivedMessage(m_sender_endpoint, config);
    }
    void operator()(const lmp::msg::ConfigAckMsg& configAck) const
    {
      m_ipcc.processReceivedMessage(m_sender_endpoint, configAck);
    }
    void operator()(const lmp::msg::ConfigNackMsg& configNack) const
    {
      m_ipcc.processReceivedMessage(m_sender_endpoint, configNack);
    }
    void operator()(const lmp::msg::HelloMsg& hello) const
    {
      m_ipcc.processReceivedMessage(m_sender_endpoint, hello);
    }
    void operator()(const lmp::msg::UnknownMessage& unknownMessage) const
    {
      m_ipcc.processReceivedMessage(m_sender_endpoint, unknownMessage);
    }
    lmp::cc::IpccMsgReceiveIF&                      m_ipcc;
    const boost::asio::ip::udp::endpoint&  m_sender_endpoint;
  };
}

namespace lmp
{
  namespace cc
  {
    UDPMsgHandler::UDPMsgHandler(
      node::Node&           node)
    : m_node(node)
    {
    }
    void UDPMsgHandler::sendMessage(
      NetworkIFSocketIF&                     networkIFSocket,
      const boost::asio::ip::udp::endpoint&  destination_endpoint,
      const msg::Message&                    message)
    {
      typedef boost::asio::buffers_iterator<boost::asio::mutable_buffers_1>  BufOutIterType;
      const lmp::WORD msgLength = lmp::msg::getLength(message);
      unsigned char sendSpace[msgLength];
      boost::asio::mutable_buffers_1 sendBuffer(sendSpace, msgLength);
      BufOutIterType  gen_begin = boost::asio::buffers_begin(sendBuffer);
      //BufOutIterType gen_last = boost::asio::buffers_end(emptyBuffer);
      lmp::msg::generate::message_grammar<BufOutIterType>  msgGenerateGrammar;
      if (generate(gen_begin,
                   msgGenerateGrammar,
                   message))
      {
        networkIFSocket.send(destination_endpoint, sendBuffer);
      }
    }
    void UDPMsgHandler::do_processReceivedMessage(
      NetworkIFSocketIF&                     networkIFSocket,
      const boost::asio::ip::udp::endpoint&  sender_endpoint,
      boost::asio::const_buffers_1&          messageBuffer)
    {
      IPCCMap::iterator ipccIter = m_IPCCs.find(sender_endpoint);
      if (ipccIter == m_IPCCs.end())
      {
        IpccImpl*  ipccPtr = new IpccImpl(m_node.getNodeId(), networkIFSocket.getLocalCCId(), false);
        if (ipccPtr)
        {
          ipccPtr->enable();
          ipccPtr->registerObserver(m_node);
          ipccIter = m_IPCCs.insert(IPCCMap::value_type(sender_endpoint,
                                                        ipccPtr)).first;
        }
      }
      if (ipccIter != m_IPCCs.end())
      {
        IpccMsgReceiveIF*  ipccPtr = ipccIter->second;
        if (ipccPtr)
        {
          using boost::spirit::qi::parse;
          typedef boost::asio::buffers_iterator<boost::asio::const_buffers_1>  BufIterType;
          BufIterType begin = boost::asio::buffers_begin(messageBuffer);
          BufIterType last = boost::asio::buffers_end(messageBuffer);
          lmp::msg::parse::message_grammar<BufIterType>  msgGrammar;
          lmp::msg::Message parsedMessage;
          if (parse(begin,
                    last,
                    msgGrammar,
                    parsedMessage))
          {
            boost::apply_visitor(msg_variants_processor(*ipccPtr, sender_endpoint), parsedMessage);
          }
        }
      }
    }
  } // namespace cc
} // namespace lmp
