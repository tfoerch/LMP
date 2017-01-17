/*
 * CCUnitTest.cpp
 *
 *  Created on: 27.02.2015
 *      Author: tom
 */

#include "cc/IPCC_Impl.hpp"
#include "cc/IPCC_NetIFSocket.hpp"
#include "msg/Config.hpp"
#include "msg/ConfigAck.hpp"
#include "msg/ConfigNack.hpp"
#include "msg/Hello.hpp"
#include "Test_IPCC_Observer.hpp"
#include "Test_IPCC_Msg_Receiver.hpp"
#include "Test_Wait.hpp"

#include <boost/asio/io_service.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

#include <vector>

#define BOOST_TEST_MODULE LMP
#include <BoostTestTargetConfig.h>
// #include <boost/test/included/unit_test.hpp>

BOOST_AUTO_TEST_SUITE( lmp_socket )

BOOST_AUTO_TEST_CASE( getIfAddress )
{
  {
	std::string ifName = "virbr0";
	lmp::cc::NetworkIFSocket::OptAddresses addr = lmp::cc::NetworkIFSocket::getIfAddress(ifName);
	BOOST_CHECK(addr.first);
	if (addr.first)
	{
	  // std::cout << *addr.first << std::endl;
	  BOOST_CHECK_EQUAL(*addr.first, boost::asio::ip::address::from_string("192.168.122.1"));
	}
	BOOST_CHECK(!addr.second);
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
	unsigned short node1_port = 9701;
	boost::asio::ip::udp::endpoint node1_endpoint(*addr.first, node1_port);
	lmp::cc::TestIpccMsgReceiver node1_msgReceiver;
	lmp::cc::NetworkIFSocket  node1_lmpSocket(io_service, node1_endpoint, node1_msgReceiver);

	BOOST_CHECK(addr.first);
	unsigned short node2_port = 9702;
	boost::asio::ip::udp::endpoint node2_endpoint(*addr.first, node2_port);
	lmp::cc::TestIpccMsgReceiver node2_msgReceiver;
	lmp::cc::NetworkIFSocket  node2_lmpSocket(io_service, node2_endpoint, node2_msgReceiver);

	std::stringstream message;
	message << "test message 1" << std::ends;

	node1_lmpSocket.send(message.str().c_str(), message.str().length(), node2_endpoint);

	BOOST_CHECK(lmp::test::util::wait(node2_msgReceiver.getConfigMessageReceivedFtor(), io_service, boost::posix_time::seconds(1)));
	//io_service.run_one();
	//io_service.run_one();
  }

}

BOOST_AUTO_TEST_CASE( bind_socket_to_netif)
{
  unsigned short port = 9701;
  std::string ifName = "virbr0";

  boost::asio::io_service io_service;
  lmp::cc::IpccImpl  activeIPCC(123, port, true);
  lmp::cc::NetworkIFSocket  lmpSocket(io_service, port, ifName, activeIPCC);

  std::stringstream message;
  message << "test message 1" << std::ends;

  boost::asio::ip::udp::endpoint remote_endpoint(boost::asio::ip::address::from_string("224.0.0.1"),
		                                         port);
  lmpSocket.send(message.str().c_str(), message.str().length(), remote_endpoint);
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
    { 0x00,
      { false, { 2 } },      // localCCId
	  { false, { 115 } },    // localNodeId
      { false, { 7 } },      // remoteCCId
	  { false, { 34 } },     // messageId
	  { false, { 117 } },    // remoteNodeId
	  { true, { 100, 450 } } // helloConfig
    };
  activeIPCC.processReceivedMessage(configNackMsg);
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

  activeIPCC.processReceivedMessage(configMsg);
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
  activeIPCC.processReceivedMessage(configMsg);
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
    { 0x00,
      { false, { 2 } },      // localCCId
	  { false, { 115 } },    // localNodeId
      { false, { 7 } },      // remoteCCId
	  { false, { 34 } },     // messageId
	  { false, { 117 } }     // remoteNodeId
    };
  activeIPCC.processReceivedMessage(configAckMsg);
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
      { 0x00,
  	    { false, { 1, 0 } }     // hello
      };
    activeIPCC.processReceivedMessage(helloMsg);
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
      { 0x00,
  	    { false, { 1, 1 } }     // hello
      };
    activeIPCC.processReceivedMessage(helloMsg);
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
      { 0x00,
  	    { false, { 2, 2 } }     // hello
      };
    activeIPCC.processReceivedMessage(helloMsg);
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
  activeIPCC.processReceivedMessage(configMsg);
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
  passiveIPCC.processReceivedMessage(configMsg);
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


