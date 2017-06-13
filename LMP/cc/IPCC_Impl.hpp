#ifndef LIBS_IPCC_IMPL_HPP_
#define LIBS_IPCC_IMPL_HPP_
/*
 * IPCC_Impl.hpp
 *
 *  Created on: 19.02.2015
 *      Author: tom
 */

#include "cc/IPCCApplicationIF.hpp"
#include "cc/IPCC_FSM.hpp"
#include "cc/IPCC_FSM_InvokeIF.hpp"
#include "cc/IPCC_Msg_ReceiveIF.hpp"
#include "obj/HelloConfig.hpp"
#include "base/ProtocolTypes.hpp"             // for DWORD

#include <boost/asio/ip/udp.hpp>
#include <boost/optional/optional.hpp>        // for optional
#include <boost/ptr_container/ptr_deque.hpp>  // for ptr_deque

namespace lmp
{
  namespace node
  {
    class NodeApplicationIF;
  }
  namespace cc
  {
    class NetworkIFSocketIF;
    namespace appl
    {
      class Action;
      class Event;
      class IpccObserverProxyIF;
      class State;
    }
    class IpccImpl : public IpccApplicationIF,
                     public IpccFsmInvokeIF,
                     public IpccMsgReceiveIF
    {
    public:
      IpccImpl(
        node::NodeApplicationIF&               node,
        NetworkIFSocketIF&                     networkIFSocket,
        const boost::asio::ip::udp::endpoint&  remote_endpoint,
        bool                                   isActiveSetup);
      virtual ~IpccImpl();
      void reconfigure(
        const obj::config::HelloConfigBody&  helloConfig);
      void evtCCDown();
      void evtConfRet();
      void evtHelloRet();
      void evtDownTimer();
      boost::optional<const lmp::cc::appl::State&> getActiveState() const;
    private:
      typedef boost::ptr_deque<appl::IpccObserverProxyIF>       IPCCObservers;
      typedef std::set<neighbor::NeighborAdjacencyObserverIF*>  NeighborAdjacencyObservers;
      // implement IpccApplicationIF
      virtual void do_enable();
      virtual void do_disable();
      virtual lmp::DWORD do_getLocalNodeId() const;
      virtual lmp::DWORD do_getRemoteNodeId() const;
      virtual lmp::DWORD do_getLocalCCId() const;
      virtual lmp::DWORD do_getRemoteCCId() const;
      virtual const boost::asio::ip::udp::endpoint& do_getRemoteEndpoint() const;
      virtual void do_registerObserver(
        appl::IpccObserverProxyIF&  observer);
      virtual void do_deregisterObserver(
        appl::IpccObserverProxyIF&  observer);
      virtual void do_registerObserver(
        neighbor::NeighborAdjacencyObserverIF&  observer);
      virtual void do_deregisterObserver(
        neighbor::NeighborAdjacencyObserverIF&  observer);
      // implement IpccFsmConnectIF
      virtual bool do_hasActiveSetupRole() const;
      virtual bool do_isConntentionWinning(
        lmp::DWORD  remoteNodeId) const;
      virtual bool do_isConfigAcceptable(
        const msg::ConfigMsg&  configMsg) const;
      virtual void do_sendConfigAck(
        const msg::ConfigMsg&  configMsg);
      virtual void do_sendConfigNack(
        const msg::ConfigMsg&  configMsg);
      virtual void do_reportTransition(
    	const appl::State&   sourceState,
    	const appl::Event&   event,
    	const appl::State&   targetState,
    	const appl::Action&  action);
      virtual void do_sendHelloMsg();
      // implement IpccMsgReceiveIF
      virtual void do_processReceivedMessage(
    	const msg::ConfigMsg&                  configMsg);
      virtual void do_processReceivedMessage(
    	const msg::ConfigAckMsg&               configAckMsg);
      virtual void do_processReceivedMessage(
    	const msg::ConfigNackMsg&              configNackMsg);
      virtual void do_processReceivedMessage(
    	const msg::HelloMsg&                   helloMsg);
      virtual void do_processReceivedMessage(
        const msg::UnknownMessage&             unknownMessage);
      // internal
      bool canAcceptNewConfig() const;
      bool isConntentionWinning(
    	const msg::ConfigMsg&  configMsg) const;
      void updateConfig(
        const msg::ConfigMsg&  configMsg);

      node::NodeApplicationIF&                          m_node;
      NetworkIFSocketIF&                                m_networkIFSocket;
      boost::asio::ip::udp::endpoint                    m_remote_endpoint;
      lmp::DWORD                                        m_remoteNodeId;
      lmp::DWORD                                        m_remoteCCId;
      bool                                              theIsActiveSetup;
      FSM_IPCC                                          theFSM;
      lmp::DWORD                                        theTxSeqNum;
      lmp::DWORD                                        theRcvSeqNum;
      IPCCObservers                                     theObservers;
      NeighborAdjacencyObservers                        m_neighborAdjacencyObservers;
    };
  } // namespace cc
} // namespace lmp

#endif /* LIBS_IPCC_IMPL_HPP_ */
