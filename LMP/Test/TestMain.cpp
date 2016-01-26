/*
 * TestMain.cpp
 *
 *  Created on: 27.02.2015
 *      Author: tom
 */

#include <IPCC_Impl.hpp>
#include <IPCC_NetIFSocket.hpp>
#include <Test_IPCC_Observer.hpp>
#include <Test_IPCC_Msg_Receiver.hpp>
#include <CommonHeader.hpp>
#include <ObjectHeader.hpp>
#include <ConfigAck.hpp>
#include <ConfigNack.hpp>
#include <Hello.hpp>
#include <Test_Wait.hpp>
#include <Node.hpp>

#include <boost/asio/io_service.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

#include <vector>

#define BOOST_TEST_MODULE LMP
#include <BoostTestTargetConfig.h>
// #include <boost/test/included/unit_test.hpp>

BOOST_AUTO_TEST_SUITE( node )

BOOST_AUTO_TEST_CASE( node_methods )
{
  lmp::node::Node  node(123, boost::asio::ip::address::from_string("192.168.2.104"));
  BOOST_CHECK_EQUAL(node.getNodeId(), 123UL);
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE( msg )

BOOST_AUTO_TEST_CASE( msg_header_decode )
{
  {
	unsigned char message[] =
      { 0x10, 0x00, 0x00, 0x01 };
	boost::asio::const_buffer messageBuffer(message,
                                            sizeof(message)/sizeof(unsigned char));
    lmp::msg::CommonHeader::DecodingResult decodingResult =
      lmp::msg::CommonHeader::decode(messageBuffer);
    BOOST_CHECK(!decodingResult.first);
    BOOST_CHECK(decodingResult.second);
    if (decodingResult.second)
    {
	  BOOST_CHECK_EQUAL(*decodingResult.second, lmp::msg::CommonHeader::invalid_length);
    }
  }
  {
	unsigned char message[] =
    { 0x20, 0x00, 0x00, 0x01,
      0x00, 0x20, 0x00, 0x00,
	  0x00, 0x00, 0x00, 0x00 };
	boost::asio::const_buffer messageBuffer(message,
                                            sizeof(message)/sizeof(unsigned char));
    lmp::msg::CommonHeader::DecodingResult decodingResult =
      lmp::msg::CommonHeader::decode(messageBuffer);
    BOOST_CHECK(!decodingResult.first);
    BOOST_CHECK(decodingResult.second);
    if (decodingResult.second)
    {
	  BOOST_CHECK_EQUAL(*decodingResult.second, lmp::msg::CommonHeader::not_supported_version);
    }
  }
  {
	unsigned char message[] =
    { 0x10, 0x00, 0x00, 0x38,
      0x00, 0x20, 0x00, 0x00,
	  0x00, 0x00, 0x00, 0x00 };
	boost::asio::const_buffer messageBuffer(message,
                                            sizeof(message)/sizeof(unsigned char));
    lmp::msg::CommonHeader::DecodingResult decodingResult =
      lmp::msg::CommonHeader::decode(messageBuffer);
    BOOST_CHECK(!decodingResult.first);
    BOOST_CHECK(decodingResult.second);
    if (decodingResult.second)
    {
	  BOOST_CHECK_EQUAL(*decodingResult.second, lmp::msg::CommonHeader::not_supported_msgType);
    }
  }
  {
	unsigned char message[] =
      { 0x10, 0x00, 0x00, 0x01,
        0x00, 0x20, 0x00, 0x00,
	    0x00, 0x00, 0x00, 0x00 };
	boost::asio::const_buffer messageBuffer(message,
                                            sizeof(message)/sizeof(unsigned char));
    lmp::msg::CommonHeader::DecodingResult decodingResult =
      lmp::msg::CommonHeader::decode(messageBuffer);
    BOOST_CHECK(decodingResult.first);
    BOOST_CHECK(!decodingResult.second);
    if (decodingResult.first)
    {
	  const lmp::msg::CommonHeader& header = *decodingResult.first;
	  BOOST_CHECK_EQUAL(header.getVersion(), static_cast<lmp::BYTE>(1));
	  BOOST_CHECK_EQUAL(header.isControlChannelDown(), false);
	  BOOST_CHECK_EQUAL(header.isLmpRestart(), false);
	  BOOST_CHECK_EQUAL(header.getMsgType(), lmp::msg::mtype::Config);
	  BOOST_CHECK_EQUAL(header.getLmpLength(), 0x20);
	  unsigned char emptySpace[lmp::msg::CommonHeader::c_headerLength];
	  boost::asio::mutable_buffer emptyBuffer(emptySpace,
	                                          sizeof(message)/sizeof(unsigned char));
	  lmp::msg::CommonHeader::OptEncError optEncError = header.encode(emptyBuffer);
	  BOOST_CHECK(!optEncError);
	  BOOST_CHECK_EQUAL_COLLECTIONS(message, message + lmp::msg::CommonHeader::c_headerLength,
			                        emptySpace, emptySpace + lmp::msg::CommonHeader::c_headerLength);
    }
  }
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE( obj )

BOOST_AUTO_TEST_CASE( obj_header_decode )
{
  {
	unsigned char message[] =
      { 0x01, 0x01, 0x00 };
	boost::asio::const_buffer messageBuffer(message,
                                            sizeof(message)/sizeof(unsigned char));
    lmp::obj::ObjectHeader::DecodingResult decodingResult =
      lmp::obj::ObjectHeader::decode(messageBuffer);
    BOOST_CHECK(!decodingResult.first);
    BOOST_CHECK(decodingResult.second);
    if (decodingResult.second)
    {
	  BOOST_CHECK_EQUAL(*decodingResult.second, lmp::obj::ObjectHeader::invalid_length);
    }
  }
  {
	unsigned char message[] =
    { 0x01, 0x27, 0x00, 0x08,
      0x01, 0x02, 0x00, 0x08 };
	boost::asio::const_buffer messageBuffer(message,
                                            sizeof(message)/sizeof(unsigned char));
    lmp::obj::ObjectHeader::DecodingResult decodingResult =
      lmp::obj::ObjectHeader::decode(messageBuffer);
    BOOST_CHECK(!decodingResult.first);
    BOOST_CHECK(decodingResult.second);
    if (decodingResult.second)
    {
	  BOOST_CHECK_EQUAL(*decodingResult.second, lmp::obj::ObjectHeader::not_supported_object_class);
    }
  }
  {
	unsigned char message[] =
      { 0x01, 0x01, 0x00, 0x08,
        0x01, 0x02, 0x00, 0x08 };
	boost::asio::const_buffer messageBuffer(message,
                                            sizeof(message)/sizeof(unsigned char));
    lmp::obj::ObjectHeader::DecodingResult decodingResult =
      lmp::obj::ObjectHeader::decode(messageBuffer);
    BOOST_CHECK(decodingResult.first);
    BOOST_CHECK(!decodingResult.second);
    if (decodingResult.first)
    {
	  const lmp::obj::ObjectHeader& header = *decodingResult.first;
	  BOOST_CHECK_EQUAL(header.isNegotiable(), false);
	  BOOST_CHECK_EQUAL(header.getObjectClass(), lmp::obj::otype::ControlChannelID);
	  BOOST_CHECK_EQUAL(header.getObjLength(), 0x08);
	  unsigned char emptySpace[lmp::obj::ObjectHeader::c_headerLength];
	  boost::asio::mutable_buffer emptyBuffer(emptySpace,
	                                          sizeof(message)/sizeof(unsigned char));
	  lmp::obj::ObjectHeader::OptEncError optEncError = header.encode(emptyBuffer);
	  BOOST_CHECK(!optEncError);
	  BOOST_CHECK_EQUAL_COLLECTIONS(message, message + lmp::obj::ObjectHeader::c_headerLength,
			                        emptySpace, emptySpace + lmp::obj::ObjectHeader::c_headerLength);
    }
  }
}

BOOST_AUTO_TEST_SUITE_END()

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
  lmp::msg::ConfigNack  configNackMsg(115, 2, lmp::obj::HelloConfig(lmp::obj::HelloConfigData(100, 450)));
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
  lmp::msg::Config  configMsg(2, 34, 115, lmp::obj::HelloConfig(lmp::obj::HelloConfigData(100, 450)));
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
  lmp::obj::HelloConfig  helloConfig(lmp::obj::HelloConfigData(150, 600));
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
  lmp::msg::Config  configMsg(2, 34, 128, lmp::obj::HelloConfig(lmp::obj::HelloConfigData(450, 450)));
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
  lmp::msg::ConfigAck  configAckMsg(115, 2, lmp::obj::HelloConfig(lmp::obj::HelloConfigData(100, 450)));
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
    lmp::msg::Hello  helloMsg(1, 0);
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
    lmp::msg::Hello  helloMsg(1, 1);
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
    lmp::msg::Hello  helloMsg(2, 2);
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
  lmp::msg::Config  configMsg(2, 32, 128, lmp::obj::HelloConfig(lmp::obj::HelloConfigData(100, 450)));
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
  lmp::msg::Config  configMsg(2, 38, 128, lmp::obj::HelloConfig(lmp::obj::HelloConfigData(100, 450)));
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

