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
#include <boost/bind.hpp>
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
        m_isActiveSetup(isActiveSetup),
        m_FSM(*this),
        m_configSend_timer(m_io_service,
                           std::chrono::milliseconds(500),
                           3,
                           1,
                           boost::function<void()>(
                             boost::bind(&IpccImpl::evtConfRet,
                                         this))),
        m_hello_timer(m_io_service),
        m_helloDead_timer(m_io_service),
        m_goingDown_timer(m_io_service),
        m_TxSeqNum(0),
        m_RcvSeqNum(0),
        m_Observers()
    {
      std::cout << "Node(" << m_node.getNodeId() << ").IPCC(localCCId = " << m_networkIFSocket.getLocalCCId()
                << ", remoteAddress = " << m_remote_endpoint.address().to_v4().to_ulong()
                << ", remotePortNumber = " << m_remote_endpoint.port() << ") ctor" << std::endl;
      {
        boost::unique_lock<boost::shared_mutex> guard(m_fsm_mutex);
        m_FSM.start();
      }
      registerObserver(m_node);
    }
    IpccImpl::~IpccImpl()
    {
      boost::unique_lock<boost::shared_mutex> guard(m_fsm_mutex);
      m_FSM.stop();
    }
    void IpccImpl::do_enable()
    {
//      std::cout << "Node(" << m_node.getNodeId() << ").IPCC(localCCId = " << m_networkIFSocket.getLocalCCId()
//                << ", remoteAddress = " << m_remote_endpoint.address().to_v4().to_ulong()
//                << ", remotePortNumber = " << m_remote_endpoint.port() << ") enable" << std::endl;
      {
        boost::unique_lock<boost::shared_mutex> guard(m_fsm_mutex);
        m_FSM.start();
        m_FSM.process_event(EvBringUp());
      }
      static const lmp::cc::appl::ConfSnd stateConfSnd;
      const boost::optional<const lmp::cc::appl::State&>& activeState = getActiveState();
      if (activeState &&
          *activeState == stateConfSnd )
      {
        std::cout << "Node(" << m_node.getNodeId() << ").IPCC(localCCId = " << m_networkIFSocket.getLocalCCId()
                  << ", remoteAddress = " << m_remote_endpoint.address().to_v4().to_ulong()
                  << ", remotePortNumber = " << m_remote_endpoint.port() << ") enable changed to ConfSnd state" << std::endl;
      }
    }
    void IpccImpl::do_disable()
    {
      {
        boost::unique_lock<boost::shared_mutex> guard(m_fsm_mutex);
        m_FSM.process_event(EvAdminDown());
      }
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
      {
        boost::unique_lock<boost::shared_mutex> guard(m_fsm_mutex);
        m_FSM.process_event(EvReconfig());
      }
    }
    void IpccImpl::evtCCDown()
    {
      {
        boost::unique_lock<boost::shared_mutex> guard(m_fsm_mutex);
        m_FSM.process_event(EvCCDn());
        m_FSM.stop();
      }
    }
    void IpccImpl::evtConfRet()
    {
      {
        boost::unique_lock<boost::shared_mutex> guard(m_fsm_mutex);
        m_FSM.process_event(EvConfRet());
      }
    }
    void IpccImpl::evtHelloRet()
    {
      {
        boost::unique_lock<boost::shared_mutex> guard(m_fsm_mutex);
        m_FSM.process_event(EvHelloRet());
      }
    }
    void IpccImpl::evtDownTimer()
    {
      {
        boost::unique_lock<boost::shared_mutex> guard(m_fsm_mutex);
        m_FSM.process_event(EvDownTimer());
      }
    }
    boost::optional<const lmp::cc::appl::State&> IpccImpl::getActiveState() const
    {
      boost::shared_lock<boost::shared_mutex> guard(m_fsm_mutex);
      return m_FSM.getActiveState();
    }
    void IpccImpl::do_registerObserver(
      appl::IpccObserverProxyIF&  observer)
    {
      m_Observers.push_back(new_clone(observer));
    }
    void IpccImpl::do_deregisterObserver(
  	appl::IpccObserverProxyIF&  observer)
    {
      bool found = false;
      boost::ptr_deque<appl::IpccObserverProxyIF>::iterator  iter = m_Observers.begin();
      while (!found &&
             iter != m_Observers.end())
      {
        if (observer == *iter)
        {
          m_Observers.erase(iter);
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
      // std::cout << "activeSetupRole = " << (m_isActiveSetup ? "true" : "false") << std::endl;
      return m_isActiveSetup;
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
    void IpccImpl::do_sendConfig()
    {
      std::cout << "IPCC[" << getLocalCCId() << "].sendConfig()" << std::endl;
      // create and send Config
      m_configSend_timer.start();
    }
    void IpccImpl::do_resendConfig()
    {
      std::cout << "IPCC[" << getLocalCCId() << "].resendConfig()" << std::endl;
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
      for (IPCCObservers::iterator iter = m_Observers.begin(),
    		                   end_iter = m_Observers.end();
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
      if (m_TxSeqNum == std::numeric_limits<lmp::DWORD>::max())
      {
    	m_TxSeqNum = 2;
      }
      else
      {
    	++m_TxSeqNum;
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
          {
            boost::unique_lock<boost::shared_mutex> guard(m_fsm_mutex);
            m_FSM.process_event(EvNewConfOK(configMsg));
          }
      	}
      	else
      	{
          {
            boost::unique_lock<boost::shared_mutex> guard(m_fsm_mutex);
            m_FSM.process_event(EvNewConfErr());
          }
      	}
      }
      else
      {
        if (isConntentionWinning(configMsg))
        {
          {
            boost::unique_lock<boost::shared_mutex> guard(m_fsm_mutex);
            m_FSM.process_event(EvContenWin());
          }
        }
        else
        {
          {
            boost::unique_lock<boost::shared_mutex> guard(m_fsm_mutex);
            m_FSM.process_event(EvContenLost(configMsg));
          }
        }
      }
    }
    void IpccImpl::do_processReceivedMessage(
      const msg::ConfigAckMsg&               configAckMsg)
    {
      {
        boost::unique_lock<boost::shared_mutex> guard(m_fsm_mutex);
        m_FSM.process_event(EvConfDone());
      }
    }
    void IpccImpl::do_processReceivedMessage(
      const msg::ConfigNackMsg&              configNackMsg)
    {
      {
        boost::unique_lock<boost::shared_mutex> guard(m_fsm_mutex);
        m_FSM.process_event(EvConfErr());
      }
    }
    void IpccImpl::do_processReceivedMessage(
      const msg::HelloMsg&                   helloMsg)
    {
//      std::cout << "processReceivedMessage helloMsg.m_RcvSeqNum = " << helloMsg.m_RcvSeqNum
//    	        << ", m_TxSeqNum = " << m_TxSeqNum << std::endl;
      if (helloMsg.m_data.m_hello.m_data.m_rcvSeqNum == m_TxSeqNum)
      {
        {
          boost::unique_lock<boost::shared_mutex> guard(m_fsm_mutex);
          m_FSM.process_event(EvHelloRcvd());
        }
        m_RcvSeqNum = helloMsg.m_data.m_hello.m_data.m_txSeqNum;
      }
      else
      {
        {
          boost::unique_lock<boost::shared_mutex> guard(m_fsm_mutex);
          m_FSM.process_event(EvSeqNumErr());
        }
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
    void IpccImpl::sendConfigScheduled()
    {
      std::cout << "IPCC[" << getLocalCCId() << "].sendConfigScheduled()" << std::endl;
    }
  } // namespace cc
} // namespace lmp
