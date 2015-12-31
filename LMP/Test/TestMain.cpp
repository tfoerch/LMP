/*
 * TestMain.cpp
 *
 *  Created on: 27.02.2015
 *      Author: tom
 */

#include <IPCC_Impl.hpp>
#include <Test_IPCC_Observer.hpp>

#define BOOST_TEST_MODULE LMP
#include <BoostTestTargetConfig.h>
// #include <boost/test/included/unit_test.hpp>

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
  lmp::msg::ConfigNack  configNackMsg;
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
  lmp::msg::Config  configMsg(115, 2, lmp::msg::HelloConfig(100, 450));
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
  lmp::msg::HelloConfig  helloConfig(150, 600);
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
  lmp::msg::Config  configMsg(128, 2, lmp::msg::HelloConfig(450, 450));
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
  lmp::msg::ConfigAck  configAckMsg;
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
  lmp::msg::Config  configMsg(128, 2, lmp::msg::HelloConfig(100, 450));
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
  lmp::msg::Config  configMsg(128, 2, lmp::msg::HelloConfig(100, 450));
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



