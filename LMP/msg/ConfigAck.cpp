/*
 * ConfigAck.cpp
 *
 *  Created on: 20.02.2015
 *      Author: tom
 */

#include "ConfigAck_def.hpp"
#include <boost/asio/buffer.hpp>
#include <boost/asio/buffers_iterator.hpp>
#include <iostream>

typedef boost::asio::buffers_iterator<boost::asio::const_buffers_1>  BufIterType;
template struct lmp::msg::parse::config_ack_grammar<BufIterType>;
typedef boost::asio::buffers_iterator<boost::asio::mutable_buffers_1>  BufOutIterType;
template struct lmp::msg::generate::config_ack_grammar<BufOutIterType>;

namespace lmp
{
  namespace msg
  {
    lmp::DWORD getLength(
      const ConfigAckMsg& configAck)
    {
      lmp::DWORD length =
        ( lmp::msg::c_headerLength +
          lmp::obj::getLength(configAck.m_localCCId) +
          lmp::obj::getLength(configAck.m_localNodeId) +
          lmp::obj::getLength(configAck.m_remoteCCId) +
          lmp::obj::getLength(configAck.m_messageId) +
          lmp::obj::getLength(configAck.m_remoteNodeId) );
      return length;
    }
    bool operator==(
      const ConfigAckMsg&  first,
      const ConfigAckMsg&  second)
    {
      return
        ( first.m_flags == second.m_flags &&
          first.m_localCCId == second.m_localCCId &&
          first.m_localNodeId == second.m_localNodeId &&
          first.m_remoteCCId == second.m_remoteCCId &&
          first.m_messageId == second.m_messageId &&
          first.m_remoteNodeId == second.m_remoteNodeId );
    }
    std::ostream& operator<<(
      std::ostream&             os,
      const ConfigAckMsg& configAck)
    {
      std::cout << "ConfigAckMsg(" << static_cast<lmp::WORD>(configAck.m_flags)
	        << ", " << configAck.m_localCCId
	        << ", " << configAck.m_localNodeId
	        << ", " << configAck.m_remoteCCId
	        << ", " << configAck.m_messageId
	        << ", " << configAck.m_remoteNodeId
	        << ")";
      return os;
    }
  } // namespace msg
} // namespace lmp
