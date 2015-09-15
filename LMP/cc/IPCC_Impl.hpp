#ifndef LIBS_IPCC_IMPL_HPP_
#define LIBS_IPCC_IMPL_HPP_
/*
 * IPCC_Impl.h
 *
 *  Created on: 19.02.2015
 *      Author: tom
 */

#include <IPCC_FSM.hpp>
#include <IPCC_FSM_InvokeIF.hpp>
#include <IPCC_Msg_ReceiveIF.hpp>

#include <boost/ptr_container/ptr_deque.hpp>

namespace lmp
{
  namespace cc
  {
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
        const msg::HelloConfig&  helloConfig);
      void evtCCDown();
      void evtConfRet();
      void evtHelloRet();
      void evtDownTimer();
      boost::optional<const lmp::cc::appl::State&> getActiveState() const;
      void registerObserver(
        appl::IpccObserverIF&  observer);
      void deregisterObserver(
    	appl::IpccObserverIF&  observer);
    private:
      // implement IpccFsmConnectIF
      virtual bool do_hasActiveSetupRole() const;
      virtual bool do_isConntentionWinning(
        lmp::DWORD  remoteNodeId) const;
      virtual bool do_isConfigAcceptable(
        const msg::Config&  configMsg) const;
      virtual void do_reportTransition(
    	const appl::State&   sourceState,
		const appl::Event&   event,
		const appl::State&   targetState,
		const appl::Action&  action);
      virtual void do_sendHelloMsg();
      // implement IpccMsgReceiveIF
      virtual void do_processReceivedMessage(
    	const msg::Config&  configMsg);
      virtual void do_processReceivedMessage(
    	const msg::ConfigAck&   configAckMsg);
      virtual void do_processReceivedMessage(
    	const msg::ConfigNack&  configNackMsg);
      virtual void do_processReceivedMessage(
    	const msg::Hello&       helloMsg);
      // internal
      bool canAcceptNewConfig() const;
      bool isConntentionWinning(
    	const msg::Config&  configMsg) const;

      lmp::DWORD                              theLocalNodeId;
      lmp::DWORD                              theLocalCCId;
      bool                                    theIsActiveSetup;
      FSM_IPCC                                theFSM;
  	  lmp::DWORD                              theTxSeqNum;
  	  lmp::DWORD                              theRcvSeqNum;
  	  boost::ptr_deque<appl::IpccObserverIF>  theObservers;
    };
  } // namespace cc
} // namespace lmp

#endif /* LIBS_IPCC_IMPL_HPP_ */
