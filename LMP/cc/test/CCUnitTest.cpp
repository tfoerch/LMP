/*
 * CCUnitTest.cpp
 *
 *  Created on: 27.02.2015
 *      Author: tom
 */

#include "node/Node.hpp"
#include "cc/IPCC_Impl.hpp"
#include "cc/IPCC_NetIFSocket.hpp"
#include "cc/UDP_Msg_Handler.hpp"
#include "msg/Config.hpp"
#include "msg/ConfigAck.hpp"
#include "msg/ConfigNack.hpp"
#include "msg/Hello.hpp"
#include "Test_IPCC_Observer.hpp"
#include "Test_IPCC_Msg_Receiver.hpp"
#include "Test_NeighborDiscoveredCheckFtor.hpp"
#include "Test_Wait.hpp"

#include <boost/asio/io_service.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/spirit/include/qi_binary.hpp>
#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/spirit/include/phoenix_fusion.hpp>
#include <boost/spirit/include/phoenix_stl.hpp>
#include <boost/phoenix/object/static_cast.hpp>
#include <boost/asio/buffer.hpp>
#include <boost/asio/streambuf.hpp>
#include <boost/asio/buffers_iterator.hpp>

#include <vector>

#define BOOST_TEST_MODULE LMP
#include <BoostTestTargetConfig.h>
// #include <boost/test/included/unit_test.hpp>


// NetIFSocket <-> CCId
// NetIFSocket x sender_endpoint <-> IPCC

BOOST_AUTO_TEST_SUITE( lmp_socket )

BOOST_AUTO_TEST_CASE( getIfAddress )
{
  {
    std::string ifName = "wlp1s0";
    lmp::cc::NetworkIFSocket::OptAddresses addr = lmp::cc::NetworkIFSocket::getIfAddress(ifName);
    BOOST_CHECK(addr.first);
    if (addr.first)
    {
      // std::cout << *addr.first << std::endl;
      BOOST_CHECK_EQUAL(*addr.first, boost::asio::ip::address::from_string("192.168.2.106"));
    }
    BOOST_CHECK(addr.second);
    if (addr.second)
    {
      std::cout << *addr.second << std::endl;
    }
  }
  {
    std::string ifName = "lo";
    lmp::cc::NetworkIFSocket::OptAddresses addr = lmp::cc::NetworkIFSocket::getIfAddress(ifName);
    BOOST_CHECK(addr.first);
    if (addr.first)
    {
      // std::cout << *addr.first << std::endl;
      BOOST_CHECK_EQUAL(*addr.first, boost::asio::ip::address::from_string("127.0.0.1"));
    }
    BOOST_CHECK(addr.second);
    if (addr.second)
    {
      // std::cout << *addr.second << std::endl;
      BOOST_CHECK_EQUAL(*addr.second, boost::asio::ip::address::from_string("::1"));
    }
  }
}

BOOST_AUTO_TEST_CASE( bind_socket_to_loopback_addr)
{

  boost::asio::io_service io_service;
  std::string ifName = "lo";
  lmp::cc::NetworkIFSocket::OptAddresses addr = lmp::cc::NetworkIFSocket::getIfAddress(ifName);
  BOOST_CHECK(addr.first);
  if (addr.first)
  {
    lmp::DWORD  node1_nodeId = 1;
    lmp::node::Node  node1(node1_nodeId);
    lmp::cc::UDPMsgHandler node1_MsgHandler(node1);
    unsigned short node1_port = 9701;
    boost::asio::ip::udp::endpoint node1_endpoint(*addr.first, node1_port);
    lmp::DWORD  node1_1stCCId = 1;
    // lmp::cc::TestIpccMsgReceiver node1_msgReceiver;
    lmp::cc::NetworkIFSocket  node1_lmpSocket(io_service, node1_1stCCId, node1_endpoint, node1_MsgHandler);

    lmp::DWORD  node2_nodeId = 2;
    lmp::node::Node  node2(node2_nodeId);
    lmp::cc::UDPMsgHandler node2_MsgHandler(node2);
    unsigned short node2_port = 9702;
    boost::asio::ip::udp::endpoint node2_endpoint(*addr.first, node2_port);
    lmp::DWORD  node2_1stCCId = 1;
    // lmp::cc::TestIpccMsgReceiver node2_msgReceiver;
    lmp::cc::NetworkIFSocket  node2_lmpSocket(io_service, node2_1stCCId, node2_endpoint, node2_MsgHandler);

    lmp::obj::config::ConfigObjectSequence  configObjectSequence;
    {
      lmp::obj::config::HelloConfigData  helloConfig = { true, { 0x009A, 0x01CF } };
      configObjectSequence.push_back(lmp::obj::config::ConfigCTypes(helloConfig));
    }
    lmp::msg::ConfigMsg  configMsg =
      { false,
        false,
        { { false, { node1_1stCCId } },      // localCCId
          { false, { 0x1020508 } },      // messageId
          { false, { node2_nodeId } },      // localNodeId
          configObjectSequence } // configObjectss
      };
    lmp::msg::Message sendMessage = configMsg;

    node2_MsgHandler.sendMessage(node2_lmpSocket, node1_endpoint, sendMessage);
//    node1_lmpSocket.send(node2_endpoint, sendBuffer);

    lmp::cc::test::NeighborDiscoveredCheckFtor  neighborDiscoveredCheckFtor(node1, node2_nodeId);
    BOOST_CHECK(lmp::test::util::wait(neighborDiscoveredCheckFtor, io_service, boost::posix_time::seconds(1)));
    //io_service.run_one();
    //io_service.run_one();
  }
}

BOOST_AUTO_TEST_CASE( bind_socket_to_netif)
{
  unsigned short port = 9701;
  std::string ifName = "virbr0";
  lmp::node::Node  node1(1);
  lmp::cc::UDPMsgHandler node1_MsgHandler(node1);
  lmp::DWORD  node1_1stCCId = 1;

  boost::asio::io_service io_service;
  // lmp::cc::IpccImpl  activeIPCC(123, port, true);
  lmp::cc::NetworkIFSocket  lmpSocket(io_service, node1_1stCCId, ifName, port, node1_MsgHandler);

  boost::asio::ip::udp::endpoint remote_endpoint(boost::asio::ip::address::from_string("224.0.0.1"),
                                                 port);
  lmp::obj::config::ConfigObjectSequence  configObjectSequence;
  {
    lmp::obj::config::HelloConfigData  helloConfig = { true, { 0x009A, 0x01CF } };
    configObjectSequence.push_back(lmp::obj::config::ConfigCTypes(helloConfig));
  }
  lmp::msg::ConfigMsg  configMsg =
    { false,
      false,
      { { false, { 0x1020008 } },      // localCCId
        { false, { 0x1020508 } },      // messageId
        { false, { 0x8600420 } },      // localNodeId
        configObjectSequence } // configObjectss
    };
  const lmp::WORD msgLength = lmp::msg::getLength(configMsg);
  unsigned char rawBuffer[msgLength];
  boost::asio::mutable_buffers_1 sendBuffer(rawBuffer, msgLength);
  typedef boost::asio::buffers_iterator<boost::asio::mutable_buffers_1>  BufOutIterType;
  BufOutIterType  gen_begin = boost::asio::buffers_begin(sendBuffer);
  BufOutIterType gen_last = boost::asio::buffers_end(sendBuffer);
  using boost::spirit::karma::generate;
  lmp::msg::generate::message_type_grammar<BufOutIterType,
                                           lmp::msg::MsgType::Config>  configMsgGenerateGrammar;
  BOOST_CHECK(generate(gen_begin,
                       configMsgGenerateGrammar,
                       configMsg));

  lmpSocket.send(remote_endpoint, sendBuffer);
}

BOOST_AUTO_TEST_SUITE_END()



BOOST_AUTO_TEST_SUITE( lmp_ipcc_active )

BOOST_AUTO_TEST_CASE( activeIPCC_CCDown )
{
  lmp::cc::IpccImpl  activeIPCC(123, 7001, true);
  lmp::cc::appl::TestIpccObserver  ipccObserver(activeIPCC);
  activeIPCC.enable();
  {
    lmp::cc::appl::TestIpccObserver::TransistionSequence expectedTransitions;
    expectedTransitions.push_back(lmp::cc::appl::TestIpccObserver::TransRecord(lmp::cc::appl::State::Down,
                                                                               lmp::cc::appl::Event::EvBringUp,
                                                                               lmp::cc::appl::State::ConfSnd,
                                                                               lmp::cc::appl::Action::ActionSendConfig));
    BOOST_CHECK_EQUAL(ipccObserver.getTransistions(), expectedTransitions);
    ipccObserver.reset();
    const boost::optional<const lmp::cc::appl::State&>& activeState = activeIPCC.getActiveState();
    BOOST_CHECK(activeState);
    if (activeState)
    {
      BOOST_CHECK_EQUAL(*activeState, lmp::cc::appl::ConfSnd());
    }
  }
  activeIPCC.evtCCDown();
  {
    lmp::cc::appl::TestIpccObserver::TransistionSequence expectedTransitions;
    expectedTransitions.push_back(lmp::cc::appl::TestIpccObserver::TransRecord(lmp::cc::appl::State::ConfSnd,
                                                                               lmp::cc::appl::Event::EvCCDn,
                                                                               lmp::cc::appl::State::Down,
                                                                               lmp::cc::appl::Action::ActionStopSendConfig));
    BOOST_CHECK_EQUAL(ipccObserver.getTransistions(), expectedTransitions);
    const boost::optional<const lmp::cc::appl::State&>& activeState = activeIPCC.getActiveState();
    BOOST_CHECK(activeState);
    if (activeState)
    {
      BOOST_CHECK_EQUAL(*activeState, lmp::cc::appl::Down());
    }
  }
}

BOOST_AUTO_TEST_CASE( activeIPCC_AdminDown )
{
  lmp::cc::IpccImpl  activeIPCC(123, 7001, true);
  lmp::cc::appl::TestIpccObserver  ipccObserver(activeIPCC);
  activeIPCC.enable();
  {
    const boost::optional<const lmp::cc::appl::State&>& activeState = activeIPCC.getActiveState();
    BOOST_CHECK(activeState);
    if (activeState)
    {
      BOOST_CHECK_EQUAL(*activeState, lmp::cc::appl::ConfSnd());
    }
  }
  activeIPCC.disable();
  {
    const boost::optional<const lmp::cc::appl::State&>& activeState = activeIPCC.getActiveState();
    BOOST_CHECK(activeState);
    if (activeState)
    {
      BOOST_CHECK_EQUAL(*activeState, lmp::cc::appl::Down());
    }
  }
}

BOOST_AUTO_TEST_CASE( activeIPCC_ConfigErr )
{
  lmp::cc::IpccImpl  activeIPCC(123, 7001, true);
  boost::asio::ip::address_v4  loAddrV4 = boost::asio::ip::address_v4::from_string("127.0.0.1");
  unsigned short node1_port = 9701;
  boost::asio::ip::udp::endpoint node1_endpoint(loAddrV4, node1_port);
  lmp::cc::appl::TestIpccObserver  ipccObserver(activeIPCC);
  activeIPCC.enable();
  {
    lmp::cc::appl::TestIpccObserver::TransistionSequence expectedTransitions;
    expectedTransitions.push_back(lmp::cc::appl::TestIpccObserver::TransRecord(lmp::cc::appl::State::Down,
                                                                               lmp::cc::appl::Event::EvBringUp,
                                                                               lmp::cc::appl::State::ConfSnd,
                                                                               lmp::cc::appl::Action::ActionSendConfig));
    BOOST_CHECK_EQUAL(ipccObserver.getTransistions(), expectedTransitions);
    ipccObserver.reset();
    const boost::optional<const lmp::cc::appl::State&>& activeState = activeIPCC.getActiveState();
    BOOST_CHECK(activeState);
    if (activeState)
    {
      BOOST_CHECK_EQUAL(*activeState, lmp::cc::appl::ConfSnd());
    }
  }
  lmp::msg::ConfigNackMsg configNackMsg =
    { false,
      false,
      { { false, { 2 } },        // localCCId
	{ false, { 115 } },      // localNodeId
        { false, { 7 } },        // remoteCCId
        { false, { 34 } },       // messageId
        { false, { 117 } },      // remoteNodeId
        { true, { 100, 450 } } } // helloConfig
    };
  activeIPCC.processReceivedMessage(node1_endpoint, configNackMsg);
  {
    const boost::optional<const lmp::cc::appl::State&>& activeState = activeIPCC.getActiveState();
    BOOST_CHECK(activeState);
    if (activeState)
    {
      BOOST_CHECK_EQUAL(*activeState, lmp::cc::appl::ConfSnd());
    }
  }
  activeIPCC.disable();
  {
    const boost::optional<const lmp::cc::appl::State&>& activeState = activeIPCC.getActiveState();
    BOOST_CHECK(activeState);
    if (activeState)
    {
      BOOST_CHECK_EQUAL(*activeState, lmp::cc::appl::Down());
    }
  }
}

BOOST_AUTO_TEST_CASE( activeIPCC_ContenWin )
{
  lmp::cc::IpccImpl  activeIPCC(123, 7001, true);
  boost::asio::ip::address_v4  loAddrV4 = boost::asio::ip::address_v4::from_string("127.0.0.1");
  unsigned short node1_port = 9701;
  boost::asio::ip::udp::endpoint node1_endpoint(loAddrV4, node1_port);
  lmp::cc::appl::TestIpccObserver  ipccObserver(activeIPCC);
  activeIPCC.enable();
  {
    lmp::cc::appl::TestIpccObserver::TransistionSequence expectedTransitions;
    expectedTransitions.push_back(lmp::cc::appl::TestIpccObserver::TransRecord(lmp::cc::appl::State::Down,
                                                                               lmp::cc::appl::Event::EvBringUp,
                                                                               lmp::cc::appl::State::ConfSnd,
                                                                               lmp::cc::appl::Action::ActionSendConfig));
    BOOST_CHECK_EQUAL(ipccObserver.getTransistions(), expectedTransitions);
    ipccObserver.reset();
    const boost::optional<const lmp::cc::appl::State&>& activeState = activeIPCC.getActiveState();
    BOOST_CHECK(activeState);
    if (activeState)
    {
      BOOST_CHECK_EQUAL(*activeState, lmp::cc::appl::ConfSnd());
    }
  }
  lmp::obj::config::ConfigObjectSequence  configObjectSequence;
  {
    lmp::obj::config::HelloConfigData  helloConfig = { true, { 100, 450 } };// helloConfig
    configObjectSequence.push_back(lmp::obj::config::ConfigCTypes(helloConfig));
  }
  lmp::msg::ConfigMsg  configMsg =
    { false,
      false,
      { { false, { 2 } },      // localCCId
        { false, { 34 } },     // messageId
        { false, { 115 } },    // localNodeId
        configObjectSequence } // configObjects
    };

  activeIPCC.processReceivedMessage(node1_endpoint, configMsg);
  {
    const boost::optional<const lmp::cc::appl::State&>& activeState = activeIPCC.getActiveState();
    BOOST_CHECK(activeState);
    if (activeState)
    {
      BOOST_CHECK_EQUAL(*activeState, lmp::cc::appl::ConfSnd());
    }
  }
  activeIPCC.disable();
  {
    const boost::optional<const lmp::cc::appl::State&>& activeState = activeIPCC.getActiveState();
    BOOST_CHECK(activeState);
    if (activeState)
    {
      BOOST_CHECK_EQUAL(*activeState, lmp::cc::appl::Down());
    }
  }
}

BOOST_AUTO_TEST_CASE( activeIPCC_Reconfig )
{
  lmp::cc::IpccImpl  activeIPCC(123, 7001, true);
  lmp::cc::appl::TestIpccObserver  ipccObserver(activeIPCC);
  activeIPCC.enable();
  {
    lmp::cc::appl::TestIpccObserver::TransistionSequence expectedTransitions;
    expectedTransitions.push_back(lmp::cc::appl::TestIpccObserver::TransRecord(lmp::cc::appl::State::Down,
                                                                               lmp::cc::appl::Event::EvBringUp,
                                                                               lmp::cc::appl::State::ConfSnd,
                                                                               lmp::cc::appl::Action::ActionSendConfig));
    BOOST_CHECK_EQUAL(ipccObserver.getTransistions(), expectedTransitions);
    ipccObserver.reset();
    const boost::optional<const lmp::cc::appl::State&>& activeState = activeIPCC.getActiveState();
    BOOST_CHECK(activeState);
    if (activeState)
    {
      BOOST_CHECK_EQUAL(*activeState, lmp::cc::appl::ConfSnd());
    }
  }
  lmp::obj::config::HelloConfigBody  helloConfig = { 150, 600 };
  activeIPCC.reconfigure(helloConfig);
  {
    const boost::optional<const lmp::cc::appl::State&>& activeState = activeIPCC.getActiveState();
    BOOST_CHECK(activeState);
    if (activeState)
    {
      BOOST_CHECK_EQUAL(*activeState, lmp::cc::appl::ConfSnd());
    }
  }
  activeIPCC.disable();
}

BOOST_AUTO_TEST_CASE( activeIPCC_ConfRet )
{
  lmp::cc::IpccImpl  activeIPCC(123, 7001, true);
  lmp::cc::appl::TestIpccObserver  ipccObserver(activeIPCC);
  activeIPCC.enable();
  {
    lmp::cc::appl::TestIpccObserver::TransistionSequence expectedTransitions;
    expectedTransitions.push_back(lmp::cc::appl::TestIpccObserver::TransRecord(lmp::cc::appl::State::Down,
                                                                               lmp::cc::appl::Event::EvBringUp,
                                                                               lmp::cc::appl::State::ConfSnd,
                                                                               lmp::cc::appl::Action::ActionSendConfig));
    BOOST_CHECK_EQUAL(ipccObserver.getTransistions(), expectedTransitions);
    ipccObserver.reset();
    const boost::optional<const lmp::cc::appl::State&>& activeState = activeIPCC.getActiveState();
    BOOST_CHECK(activeState);
    if (activeState)
    {
      BOOST_CHECK_EQUAL(*activeState, lmp::cc::appl::ConfSnd());
    }
  }
  activeIPCC.evtConfRet();
  {
    const boost::optional<const lmp::cc::appl::State&>& activeState = activeIPCC.getActiveState();
    BOOST_CHECK(activeState);
    if (activeState)
    {
      BOOST_CHECK_EQUAL(*activeState, lmp::cc::appl::ConfSnd());
    }
  }
  activeIPCC.disable();
}

BOOST_AUTO_TEST_CASE( activeIPCC_ContenLost_NotAcceptConf )
{
  lmp::cc::IpccImpl  activeIPCC(123, 7001, true);
  boost::asio::ip::address_v4  loAddrV4 = boost::asio::ip::address_v4::from_string("127.0.0.1");
  unsigned short node1_port = 9701;
  boost::asio::ip::udp::endpoint node1_endpoint(loAddrV4, node1_port);
  lmp::cc::appl::TestIpccObserver  ipccObserver(activeIPCC);
  activeIPCC.enable();
  {
    lmp::cc::appl::TestIpccObserver::TransistionSequence expectedTransitions;
    expectedTransitions.push_back(lmp::cc::appl::TestIpccObserver::TransRecord(lmp::cc::appl::State::Down,
                                                                               lmp::cc::appl::Event::EvBringUp,
                                                                               lmp::cc::appl::State::ConfSnd,
                                                                               lmp::cc::appl::Action::ActionSendConfig));
    BOOST_CHECK_EQUAL(ipccObserver.getTransistions(), expectedTransitions);
    ipccObserver.reset();
    const boost::optional<const lmp::cc::appl::State&>& activeState = activeIPCC.getActiveState();
    BOOST_CHECK(activeState);
    if (activeState)
    {
      BOOST_CHECK_EQUAL(*activeState, lmp::cc::appl::ConfSnd());
    }
  }
  lmp::obj::config::ConfigObjectSequence  configObjectSequence;
  {
    lmp::obj::config::HelloConfigData  helloConfig = { true, { 450, 450 } };// helloConfig
    configObjectSequence.push_back(lmp::obj::config::ConfigCTypes(helloConfig));
  }
  lmp::msg::ConfigMsg  configMsg =
    { false,
      false,
      { { false, { 2 } },      // localCCId
        { false, { 34 } },     // messageId
        { false, { 128 } },    // localNodeId
        configObjectSequence } // configObjectss
    };
  activeIPCC.processReceivedMessage(node1_endpoint, configMsg);
  // BOOST_TEST_MESSAGE("getActiveState");
  {
    const boost::optional<const lmp::cc::appl::State&>& activeState = activeIPCC.getActiveState();
    BOOST_CHECK(activeState);
    if (activeState)
    {
      BOOST_CHECK_EQUAL(*activeState, lmp::cc::appl::ConfRcv());
    }
  }
  activeIPCC.disable();
  {
    const boost::optional<const lmp::cc::appl::State&>& activeState = activeIPCC.getActiveState();
    BOOST_CHECK(activeState);
    if (activeState)
    {
      BOOST_CHECK_EQUAL(*activeState, lmp::cc::appl::Down());
    }
  }
}

BOOST_AUTO_TEST_CASE( activeIPCC_ConfDone_HelloRcvd )
{
  lmp::cc::IpccImpl  activeIPCC(123, 7001, true);
  boost::asio::ip::address_v4  loAddrV4 = boost::asio::ip::address_v4::from_string("127.0.0.1");
  unsigned short node1_port = 9701;
  boost::asio::ip::udp::endpoint node1_endpoint(loAddrV4, node1_port);
  lmp::cc::appl::TestIpccObserver  ipccObserver(activeIPCC);
  activeIPCC.enable();
  {
    lmp::cc::appl::TestIpccObserver::TransistionSequence expectedTransitions;
    expectedTransitions.push_back(lmp::cc::appl::TestIpccObserver::TransRecord(lmp::cc::appl::State::Down,
                                                                               lmp::cc::appl::Event::EvBringUp,
                                                                               lmp::cc::appl::State::ConfSnd,
                                                                               lmp::cc::appl::Action::ActionSendConfig));
    BOOST_CHECK_EQUAL(ipccObserver.getTransistions(), expectedTransitions);
    ipccObserver.reset();
    const boost::optional<const lmp::cc::appl::State&>& activeState = activeIPCC.getActiveState();
    BOOST_CHECK(activeState);
    if (activeState)
    {
      BOOST_CHECK_EQUAL(*activeState, lmp::cc::appl::ConfSnd());
    }
  }
  lmp::msg::ConfigAckMsg configAckMsg =
    { false,
      false,
      { { false, { 2 } },      // localCCId
        { false, { 115 } },    // localNodeId
        { false, { 7 } },      // remoteCCId
        { false, { 34 } },     // messageId
        { false, { 117 } } }   // remoteNodeId
    };
  activeIPCC.processReceivedMessage(node1_endpoint, configAckMsg);
  {
    lmp::cc::appl::TestIpccObserver::TransistionSequence expectedTransitions;
    expectedTransitions.push_back(lmp::cc::appl::TestIpccObserver::TransRecord(lmp::cc::appl::State::ConfSnd,
                                                                               lmp::cc::appl::Event::EvConfDone,
                                                                               lmp::cc::appl::State::Active,
                                                                               lmp::cc::appl::Action::ActionStopSendConfig));
    expectedTransitions.push_back(lmp::cc::appl::TestIpccObserver::TransRecord(lmp::cc::appl::State::ConfSnd,
                                                                               lmp::cc::appl::Event::EvConfDone,
                                                                               lmp::cc::appl::State::Active,
                                                                               lmp::cc::appl::Action::ActionSendHello));
    BOOST_CHECK_EQUAL(ipccObserver.getTransistions(), expectedTransitions);
    ipccObserver.reset();
    const boost::optional<const lmp::cc::appl::State&>& activeState = activeIPCC.getActiveState();
    BOOST_CHECK(activeState);
    if (activeState)
    {
      BOOST_CHECK_EQUAL(*activeState, lmp::cc::appl::Active());
    }
  }
  {
    lmp::msg::HelloMsg  helloMsg =
      { false,
        false,
        { { false, { 1, 0 } } }    // hello
      };
    activeIPCC.processReceivedMessage(node1_endpoint, helloMsg);
    {
      lmp::cc::appl::TestIpccObserver::TransistionSequence expectedTransitions;
      expectedTransitions.push_back(lmp::cc::appl::TestIpccObserver::TransRecord(lmp::cc::appl::State::Active,
                                                                                 lmp::cc::appl::Event::EvSeqNumErr,
                                                                                 lmp::cc::appl::State::Active,
                                                                                 lmp::cc::appl::Action::ActionNoAction));
      BOOST_CHECK_EQUAL(ipccObserver.getTransistions(), expectedTransitions);
      ipccObserver.reset();
      const boost::optional<const lmp::cc::appl::State&>& activeState = activeIPCC.getActiveState();
      BOOST_CHECK(activeState);
      if (activeState)
      {
        BOOST_CHECK_EQUAL(*activeState, lmp::cc::appl::Active());
      }
    }
  }
  {
    lmp::msg::HelloMsg  helloMsg =
      { false,
        false,
        { { false, { 1, 1 } } }     // hello
      };
    activeIPCC.processReceivedMessage(node1_endpoint, helloMsg);
    {
      lmp::cc::appl::TestIpccObserver::TransistionSequence expectedTransitions;
      expectedTransitions.push_back(lmp::cc::appl::TestIpccObserver::TransRecord(lmp::cc::appl::State::Active,
                                                                                 lmp::cc::appl::Event::EvHelloRcvd,
                                                                                 lmp::cc::appl::State::Up,
                                                                                 lmp::cc::appl::Action::ActionNoAction));
      BOOST_CHECK_EQUAL(ipccObserver.getTransistions(), expectedTransitions);
      ipccObserver.reset();
      const boost::optional<const lmp::cc::appl::State&>& activeState = activeIPCC.getActiveState();
      BOOST_CHECK(activeState);
      if (activeState)
      {
        BOOST_CHECK_EQUAL(*activeState, lmp::cc::appl::Up());
      }
    }
  }
  activeIPCC.evtHelloRet();
  {
    lmp::cc::appl::TestIpccObserver::TransistionSequence expectedTransitions;
    expectedTransitions.push_back(lmp::cc::appl::TestIpccObserver::TransRecord(lmp::cc::appl::State::Up,
                                                                               lmp::cc::appl::Event::EvHelloRet,
                                                                               lmp::cc::appl::State::Up,
                                                                               lmp::cc::appl::Action::ActionSendHello));
    BOOST_CHECK_EQUAL(ipccObserver.getTransistions(), expectedTransitions);
    ipccObserver.reset();
    const boost::optional<const lmp::cc::appl::State&>& activeState = activeIPCC.getActiveState();
    BOOST_CHECK(activeState);
    if (activeState)
    {
      BOOST_CHECK_EQUAL(*activeState, lmp::cc::appl::Up());
    }
  }
  {
    lmp::msg::HelloMsg  helloMsg =
      { false,
        false,
        { { false, { 2, 2 } } }   // hello
      };
    activeIPCC.processReceivedMessage(node1_endpoint, helloMsg);
    {
      lmp::cc::appl::TestIpccObserver::TransistionSequence expectedTransitions;
      expectedTransitions.push_back(lmp::cc::appl::TestIpccObserver::TransRecord(lmp::cc::appl::State::Up,
                                                                                 lmp::cc::appl::Event::EvHelloRcvd,
                                                                                 lmp::cc::appl::State::Up,
                                                                                 lmp::cc::appl::Action::ActionNoAction));
      BOOST_CHECK_EQUAL(ipccObserver.getTransistions(), expectedTransitions);
      ipccObserver.reset();
      const boost::optional<const lmp::cc::appl::State&>& activeState = activeIPCC.getActiveState();
      BOOST_CHECK(activeState);
      if (activeState)
      {
        BOOST_CHECK_EQUAL(*activeState, lmp::cc::appl::Up());
      }
    }
  }
  activeIPCC.disable();
  {
    lmp::cc::appl::TestIpccObserver::TransistionSequence expectedTransitions;
    expectedTransitions.push_back(lmp::cc::appl::TestIpccObserver::TransRecord(lmp::cc::appl::State::Up,
                                                                               lmp::cc::appl::Event::EvAdminDown,
                                                                               lmp::cc::appl::State::GoingDown,
                                                                               lmp::cc::appl::Action::ActionSetCCDownFlag));
    BOOST_CHECK_EQUAL(ipccObserver.getTransistions(), expectedTransitions);
    ipccObserver.reset();
    const boost::optional<const lmp::cc::appl::State&>& activeState = activeIPCC.getActiveState();
    BOOST_CHECK(activeState);
    if (activeState)
    {
      BOOST_CHECK_EQUAL(*activeState, lmp::cc::appl::GoingDown());
    }
  }
  activeIPCC.evtDownTimer();
  {
    lmp::cc::appl::TestIpccObserver::TransistionSequence expectedTransitions;
    expectedTransitions.push_back(lmp::cc::appl::TestIpccObserver::TransRecord(lmp::cc::appl::State::GoingDown,
                                                                               lmp::cc::appl::Event::EvDownTimer,
                                                                               lmp::cc::appl::State::Down,
                                                                               lmp::cc::appl::Action::ActionStopSendHello));
    BOOST_CHECK_EQUAL(ipccObserver.getTransistions(), expectedTransitions);
    ipccObserver.reset();
    const boost::optional<const lmp::cc::appl::State&>& activeState = activeIPCC.getActiveState();
    BOOST_CHECK(activeState);
    if (activeState)
    {
      BOOST_CHECK_EQUAL(*activeState, lmp::cc::appl::Down());
    }
  }
}


BOOST_AUTO_TEST_CASE( activeIPCC_ContenLost_AcceptConf )
{
  lmp::cc::IpccImpl  activeIPCC(123, 7001, true);
  boost::asio::ip::address_v4  loAddrV4 = boost::asio::ip::address_v4::from_string("127.0.0.1");
  unsigned short node1_port = 9701;
  boost::asio::ip::udp::endpoint node1_endpoint(loAddrV4, node1_port);
  lmp::cc::appl::TestIpccObserver  ipccObserver(activeIPCC);
  activeIPCC.enable();
  {
    const boost::optional<const lmp::cc::appl::State&>& activeState = activeIPCC.getActiveState();
    BOOST_CHECK(activeState);
    if (activeState)
    {
      BOOST_CHECK_EQUAL(*activeState, lmp::cc::appl::ConfSnd());
    }
  }
  lmp::obj::config::ConfigObjectSequence  configObjectSequence;
  {
    lmp::obj::config::HelloConfigData  helloConfig = { true, { 100, 450 } };// helloConfig
    configObjectSequence.push_back(lmp::obj::config::ConfigCTypes(helloConfig));
  }
  lmp::msg::ConfigMsg  configMsg =
    { false,
      false,
      { { false, { 2 } },      // localCCId
        { false, { 32 } },     // messageId
        { false, { 128 } },    // localNodeId
        configObjectSequence } // configObjectss
    };
  activeIPCC.processReceivedMessage(node1_endpoint, configMsg);
  // BOOST_TEST_MESSAGE("getActiveState");
  {
    const boost::optional<const lmp::cc::appl::State&>& activeState = activeIPCC.getActiveState();
    BOOST_CHECK(activeState);
    if (activeState)
    {
      BOOST_CHECK_EQUAL(*activeState, lmp::cc::appl::Active());
    }
  }
  activeIPCC.disable();
  {
    const boost::optional<const lmp::cc::appl::State&>& activeState = activeIPCC.getActiveState();
    BOOST_CHECK(activeState);
    if (activeState)
    {
      BOOST_CHECK_EQUAL(*activeState, lmp::cc::appl::GoingDown());
    }
  }
  activeIPCC.evtDownTimer();
  {
    const boost::optional<const lmp::cc::appl::State&>& activeState = activeIPCC.getActiveState();
    BOOST_CHECK(activeState);
    if (activeState)
    {
      BOOST_CHECK_EQUAL(*activeState, lmp::cc::appl::Down());
    }
  }
}


BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE( lmp_ipcc_passive )

BOOST_AUTO_TEST_CASE( passiveIPCC )
{
  lmp::cc::IpccImpl  passiveIPCC(123, 7001, false);
  boost::asio::ip::address_v4  loAddrV4 = boost::asio::ip::address_v4::from_string("127.0.0.1");
  unsigned short node1_port = 9701;
  boost::asio::ip::udp::endpoint node1_endpoint(loAddrV4, node1_port);
  lmp::cc::appl::TestIpccObserver  ipccObserver(passiveIPCC);
  passiveIPCC.enable();
  {
    const boost::optional<const lmp::cc::appl::State&>& activeState = passiveIPCC.getActiveState();
    BOOST_CHECK(activeState);
    if (activeState)
    {
      BOOST_CHECK_EQUAL(*activeState, lmp::cc::appl::ConfRcv());
    }
  }
  lmp::obj::config::ConfigObjectSequence  configObjectSequence;
  {
    lmp::obj::config::HelloConfigData  helloConfig = { true, { 100, 450 } };// helloConfig
    configObjectSequence.push_back(lmp::obj::config::ConfigCTypes(helloConfig));
  }
  lmp::msg::ConfigMsg  configMsg =
    { false,
      false,
      { { false, { 2 } },      // localCCId
        { false, { 38 } },     // messageId
        { false, { 128 } },    // localNodeId
        configObjectSequence } // configObjectss
    };
  passiveIPCC.processReceivedMessage(node1_endpoint, configMsg);
  {
    const boost::optional<const lmp::cc::appl::State&>& activeState = passiveIPCC.getActiveState();
    BOOST_CHECK(activeState);
    if (activeState)
    {
      BOOST_CHECK_EQUAL(*activeState, lmp::cc::appl::Active());
    }
  }
  passiveIPCC.disable();
}

BOOST_AUTO_TEST_SUITE_END()
