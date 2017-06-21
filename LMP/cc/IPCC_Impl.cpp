/*
 * IPCC_Impl.cpp
 *
 *  Created on: 20.02.2015
 *      Author: tom
 */

#include "IPCC_Impl.hpp"
#include "node/NodeApplicationIF.hpp"
#include "NetworkIFSocketIF.hpp"
#include "IPCC_ObserverIF.hpp"
#include "IPCC_State.hpp"
#include "IPCC_Action.hpp"
#include "neighbor/NeighborAdjacencyObserverIF.hpp"
#include "msg/Config.hpp"
#include "msg/ConfigAck.hpp"
#include "msg/ConfigNack.hpp"
#include "msg/Hello.hpp"

#include <boost/core/explicit_operator_bool.hpp>
#include <boost/ptr_container/detail/reversible_ptr_container.hpp>
#include <boost/ptr_container/detail/void_ptr_iterator.hpp>
#include <deque>
#include <limits>
#include <ostream>

namespace
{
  struct ConfigCTypes_IsAcceptableVisitor : boost::static_visitor<bool>
  {
    bool operator()(const lmp::obj::config::HelloConfigData& helloConfig) const
    {
      return
        ( (3 * helloConfig.m_data.m_helloIntv ) < helloConfig.m_data.m_helloDeadIntv );
    }
    bool operator()(const lmp::obj::config::UnknownConfigCTypeData& unknownConfig) const
    {
      return false;
    }
  };
}

namespace lmp
{
  namespace cc
  {
    IpccImpl::IpccImpl(
      node::NodeApplicationIF&               node,
      NetworkIFSocketIF&                     networkIFSocket,
      boost::asio::io_service&               io_service,
      const boost::asio::ip::udp::endpoint&  remote_endpoint,
      bool                                   isActiveSetup)
      : m_node(node),
        m_networkIFSocket(networkIFSocket),
        m_io_service(io_service),
        m_remote_endpoint(remote_endpoint),
        m_remoteNodeId(0),
        m_remoteCCId(0),
        theIsActiveSetup(isActiveSetup),
        theFSM(*this),
        theTxSeqNum(0),
        theRcvSeqNum(0),
        theObservers()
    {
      std::cout << "Node(" << m_node.getNodeId() << ").IPCC(localCCId = " << m_networkIFSocket.getLocalCCId()
                << ", remoteAddress = " << m_remote_endpoint.address().to_v4().to_ulong()
                << ", remotePortNumber = " << m_remote_endpoint.port() << ") enable" << std::endl;
      theFSM.start();
      registerObserver(m_node);
    }
    IpccImpl::~IpccImpl()
    {
      theFSM.stop();
    }
    void IpccImpl::do_enable()
    {
      theFSM.start();
      theFSM.process_event(EvBringUp());
    }
    void IpccImpl::do_disable()
    {
      theFSM.process_event(EvAdminDown());
    }
    lmp::DWORD  IpccImpl::do_getLocalNodeId() const
    {
      return m_node.getNodeId();
    }
    lmp::DWORD  IpccImpl::do_getRemoteNodeId() const
    {
      return m_remoteNodeId;
    }
    lmp::DWORD  IpccImpl::do_getLocalCCId() const
    {
      return m_networkIFSocket.getLocalCCId();
    }
    lmp::DWORD  IpccImpl::do_getRemoteCCId() const
    {
      return m_remoteCCId;
    }
    const boost::asio::ip::udp::endpoint& IpccImpl::do_getRemoteEndpoint() const
    {
      return m_remote_endpoint;
    }
    void IpccImpl::reconfigure(
      const obj::config::HelloConfigBody&  helloConfig)
    {
      theFSM.process_event(EvReconfig());
    }
    void IpccImpl::evtCCDown()
    {
      theFSM.process_event(EvCCDn());
      theFSM.stop();
    }
    void IpccImpl::evtConfRet()
    {
      theFSM.process_event(EvConfRet());
    }
    void IpccImpl::evtHelloRet()
    {
      theFSM.process_event(EvHelloRet());
    }
    void IpccImpl::evtDownTimer()
    {
      theFSM.process_event(EvDownTimer());
    }
    boost::optional<const lmp::cc::appl::State&> IpccImpl::getActiveState() const
    {
      return theFSM.getActiveState();
    }
    void IpccImpl::do_registerObserver(
      appl::IpccObserverProxyIF&  observer)
    {
      theObservers.push_back(new_clone(observer));
    }
    void IpccImpl::do_deregisterObserver(
  	appl::IpccObserverProxyIF&  observer)
    {
      bool found = false;
      boost::ptr_deque<appl::IpccObserverProxyIF>::iterator  iter = theObservers.begin();
      while (!found &&
             iter != theObservers.end())
      {
        if (observer == *iter)
        {
          theObservers.erase(iter);
          found = true;
        }
        else
        {
          ++iter;
        }
      }
    }
    void IpccImpl::do_registerObserver(
      neighbor::NeighborAdjacencyObserverIF&  observer)
    {
      m_neighborAdjacencyObservers.insert(&observer);
    }
    void IpccImpl::do_deregisterObserver(
      neighbor::NeighborAdjacencyObserverIF&  observer)
    {
      m_neighborAdjacencyObservers.erase(&observer);
    }
    bool IpccImpl::do_hasActiveSetupRole() const
    {
      // std::cout << "activeSetupRole = " << (theIsActiveSetup ? "true" : "false") << std::endl;
      return theIsActiveSetup;
    }
    bool IpccImpl::do_isConntentionWinning(
      lmp::DWORD  remoteNodeId) const
    {
      return (getLocalNodeId() > remoteNodeId);
    }
    bool IpccImpl::do_isConfigAcceptable(
      const msg::ConfigMsg&  configMsg) const
    {
      // remoteNodeId, remoeCCId valid; HelloConfig in acceptable range
      bool isAcceptable = true;
      const lmp::obj::config::ConfigObjectSequence&  configObjectSequence = configMsg.m_data.m_configObjects;
      for (std::vector<lmp::obj::config::ConfigCTypes>::const_iterator iter = configObjectSequence.begin();
           iter != configObjectSequence.end() && isAcceptable;
           ++iter)
      {
        isAcceptable = boost::apply_visitor(ConfigCTypes_IsAcceptableVisitor(), *iter);
      }
      return isAcceptable;
    }
    void IpccImpl::do_sendConfigAck(
      const msg::ConfigMsg&  configMsg)
    {
      updateConfig(configMsg);
    }
    void IpccImpl::do_sendConfigNack(
      const msg::ConfigMsg&  configMsg)
    {
    }
    void IpccImpl::updateConfig(
      const msg::ConfigMsg&  configMsg)
    {
      std::cout << "IPCC[" << getLocalCCId() << "].updateConfig(" << configMsg << ")" << std::endl;
      if (m_remoteNodeId != configMsg.m_data.m_localNodeId.m_data.m_nodeId)
      {
        if (m_remoteNodeId)
        {
          for (NeighborAdjacencyObservers::iterator iter = m_neighborAdjacencyObservers.begin(),
                                                    end_iter = m_neighborAdjacencyObservers.end();
               iter != end_iter;
               ++iter)
          {
            if (*iter)
            {
              (*iter)->neighborAdjacencyRemoved(m_remoteNodeId, *this);
            }
          }
        }
        m_remoteNodeId = configMsg.m_data.m_localNodeId.m_data.m_nodeId;
        m_remoteCCId = configMsg.m_data.m_localCCId.m_data.m_CCId;
        if (m_remoteNodeId)
        {
          for (NeighborAdjacencyObservers::iterator iter = m_neighborAdjacencyObservers.begin(),
                                                    end_iter = m_neighborAdjacencyObservers.end();
               iter != end_iter;
               ++iter)
          {
            if (*iter)
            {
              (*iter)->neighborAdjacencyAdded(m_remoteNodeId, *this);
            }
          }
        }
      }
      else if (m_remoteCCId != configMsg.m_data.m_localCCId.m_data.m_CCId)
      {
        m_remoteCCId = configMsg.m_data.m_localCCId.m_data.m_CCId;
      }
      std::cout << "IPCC[" << getLocalCCId() << "].updateConfig(): remoteNodeId = " << m_remoteNodeId
                << ", remoteCCId = " << m_remoteCCId << std::endl;
    }
    void IpccImpl::do_reportTransition(
      const appl::State&   sourceState,
      const appl::Event&   event,
      const appl::State&   targetState,
      const appl::Action&  action)
    {
      for (IPCCObservers::iterator iter = theObservers.begin(),
    		                   end_iter = theObservers.end();
           iter != end_iter;
           ++iter)
      {
    	iter->notifyTransition(*this, sourceState, event, targetState, action);
      }
//      std::cout << "IPCC[" << m_localCCId << "]." << event << ": " << sourceState << " -> " << targetState
//                << " executing " << action << std::endl;
    }
    void IpccImpl::do_sendHelloMsg()
    {
      if (theTxSeqNum == std::numeric_limits<lmp::DWORD>::max())
      {
    	theTxSeqNum = 2;
      }
      else
      {
    	++theTxSeqNum;
      }
      // create an send Hello message and schedule Hello retransmit timer
    }
    void IpccImpl::do_processReceivedMessage(
      const msg::ConfigMsg&                  configMsg)
    {
      if (canAcceptNewConfig())
      {
      	if (isConfigAcceptable(configMsg))
      	{
      	  theFSM.process_event(EvNewConfOK(configMsg));
      	}
      	else
      	{
      	  theFSM.process_event(EvNewConfErr());
      	}
      }
      else
      {
        if (isConntentionWinning(configMsg))
        {
          theFSM.process_event(EvContenWin());
        }
        else
        {
          theFSM.process_event(EvContenLost(configMsg));
        }
      }
    }
    void IpccImpl::do_processReceivedMessage(
      const msg::ConfigAckMsg&               configAckMsg)
    {
        theFSM.process_event(EvConfDone());
    }
    void IpccImpl::do_processReceivedMessage(
      const msg::ConfigNackMsg&              configNackMsg)
    {
      theFSM.process_event(EvConfErr());
    }
    void IpccImpl::do_processReceivedMessage(
      const msg::HelloMsg&                   helloMsg)
    {
//      std::cout << "processReceivedMessage helloMsg.theRcvSeqNum = " << helloMsg.theRcvSeqNum
//    	        << ", theTxSeqNum = " << theTxSeqNum << std::endl;
      if (helloMsg.m_data.m_hello.m_data.m_rcvSeqNum == theTxSeqNum)
      {
        theFSM.process_event(EvHelloRcvd());
        theRcvSeqNum = helloMsg.m_data.m_hello.m_data.m_txSeqNum;
      }
      else
      {
        theFSM.process_event(EvSeqNumErr());
      }
    }
    void IpccImpl::do_processReceivedMessage(
      const msg::UnknownMessage&             unknownMessage)
    {
      // report
    }
    bool IpccImpl::canAcceptNewConfig() const
    {
      static const lmp::cc::appl::ConfRcv stateConfRcv;
      static const lmp::cc::appl::Active stateActive;
      static const lmp::cc::appl::Up stateUp;
      const boost::optional<const lmp::cc::appl::State&>& activeState = getActiveState();
      return
    	( activeState &&
    	  ( *activeState == stateConfRcv ||
    	    *activeState == stateActive ||
    	    *activeState == stateUp ) );
    }
    bool IpccImpl::isConntentionWinning(
      const msg::ConfigMsg&  configMsg) const
    {
      return do_isConntentionWinning(configMsg.m_data.m_localNodeId.m_data.m_nodeId);
    }
  } // namespace cc
} // namespace lmp
