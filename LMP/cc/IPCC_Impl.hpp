#ifndef LIBS_IPCC_IMPL_HPP_
#define LIBS_IPCC_IMPL_HPP_
/*
 * IPCC_Impl.hpp
 *
 *  Created on: 19.02.2015
 *      Author: tom
 */

#include "cc/IPCC_FSM.hpp"
#include "cc/IPCC_FSM_InvokeIF.hpp"
#include "cc/IPCC_Msg_ReceiveIF.hpp"
#include "obj/HelloConfig.hpp"
#include "base/ProtocolTypes.hpp"             // for DWORD

#include <boost/optional/optional.hpp>        // for optional
#include <boost/ptr_container/ptr_deque.hpp>  // for ptr_deque

namespace lmp
{
  namespace cc
  {
    namespace appl
    {
      class Action;
      class Event;
      class IpccObserverProxyIF;
      class State;
    }
    class IpccImpl : public IpccFsmInvokeIF,
                     public IpccMsgReceiveIF
    {
    public:
      IpccImpl(
        lmp::DWORD  localNodeId,
        lmp::DWORD  localCCId,
        bool        isActiveSetup);
      virtual ~IpccImpl();
      void enable();
      void disable();
      lmp::DWORD  getLocalNodeId() const;
      lmp::DWORD  getLocalCCId() const;
      void reconfigure(
        const obj::config::HelloConfigBody&  helloConfig);
      void evtCCDown();
      void evtConfRet();
      void evtHelloRet();
      void evtDownTimer();
      boost::optional<const lmp::cc::appl::State&> getActiveState() const;
      void registerObserver(
        appl::IpccObserverProxyIF&  observer);
      void deregisterObserver(
    	appl::IpccObserverProxyIF&  observer);
    private:
      // implement IpccFsmConnectIF
      virtual bool do_hasActiveSetupRole() const;
      virtual bool do_isConntentionWinning(
        lmp::DWORD  remoteNodeId) const;
      virtual bool do_isConfigAcceptable(
        const msg::ConfigMsg&  configMsg) const;
      virtual void do_reportTransition(
    	const appl::State&   sourceState,
    	const appl::Event&   event,
    	const appl::State&   targetState,
    	const appl::Action&  action);
      virtual void do_sendHelloMsg();
      // implement IpccMsgReceiveIF
      virtual void do_processReceivedMessage(
        const boost::asio::ip::udp::endpoint&  sender_endpoint,
    	const msg::ConfigMsg&                  configMsg);
      virtual void do_processReceivedMessage(
        const boost::asio::ip::udp::endpoint&  sender_endpoint,
    	const msg::ConfigAckMsg&               configAckMsg);
      virtual void do_processReceivedMessage(
        const boost::asio::ip::udp::endpoint&  sender_endpoint,
    	const msg::ConfigNackMsg&              configNackMsg);
      virtual void do_processReceivedMessage(
        const boost::asio::ip::udp::endpoint&  sender_endpoint,
    	const msg::HelloMsg&                   helloMsg);
      virtual void do_processReceivedMessage(
        const boost::asio::ip::udp::endpoint&  sender_endpoint,
        const msg::UnknownMessage&             unknownMessage);
      // internal
      bool canAcceptNewConfig() const;
      bool isConntentionWinning(
    	const msg::ConfigMsg&  configMsg) const;

      lmp::DWORD                                   theLocalNodeId;
      lmp::DWORD                                   theLocalCCId;
      bool                                         theIsActiveSetup;
      FSM_IPCC                                     theFSM;
      lmp::DWORD                                   theTxSeqNum;
      lmp::DWORD                                   theRcvSeqNum;
      boost::ptr_deque<appl::IpccObserverProxyIF>  theObservers;
    };
  } // namespace cc
} // namespace lmp

#endif /* LIBS_IPCC_IMPL_HPP_ */
