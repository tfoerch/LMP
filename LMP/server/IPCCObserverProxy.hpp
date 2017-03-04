#ifndef TEST_IPCC_OBSERVER_HPP_
#define TEST_IPCC_OBSERVER_HPP_
/*
 * Test_IPCC_Observer.h
 *
 *  Created on: 19.02.2015
 *      Author: tom
 */

#include <IPCC_ObserverIF.hpp>
#include <lmp_mgtif_ipcc_observer.hpp>

#include <deque>
#include <iosfwd>                       // for ostream
#include <memory>                       // for allocator

namespace lmp
{
  namespace cc
  {
    class IpccImpl;
    namespace appl
    {
      class IpccObserverProxy : public IpccObserverProxyIF
      {
      public:
    	struct TransRecord
    	{
    	  TransRecord(
    	    appl::State::Type         sourceState,
    	    appl::Event::EvType       event,
    	    appl::State::Type         targetState,
    	    appl::Action::ActionType  action);
    	  bool operator==(
    	    const TransRecord&  other) const;
    	  appl::State::Type         theSourceState;
    	  appl::Event::EvType       theEvent;
    	  appl::State::Type         theTargetState;
    	  appl::Action::ActionType  theAction;
    	};
    	typedef  std::deque<TransRecord>  TransistionSequence;
    	IpccObserverProxy(
    	  IpccImpl&                              ipcc,
    	  ::lmp_ipcc_observer::IPCCObserver_ptr  observer);
    	virtual ~IpccObserverProxy();
    	const TransistionSequence& getTransistions() const;
    	void reset();
	  private:
        virtual void do_notifyTransition(
      	  const appl::State&   sourceState,
      	  const appl::Event&   event,
      	  const appl::State&   targetState,
      	  const appl::Action&  action);
        virtual bool is_equal(
          const IpccObserverProxyIF& other) const;
        virtual IpccObserverProxyIF* do_clone() const;

        IpccImpl&                            theIpcc;
        lmp_ipcc_observer::IPCCObserver_var  thePeerIPCCObserver;
        TransistionSequence                  theTransitions;
      };
      std::ostream& operator<<(
        std::ostream&                                 os,
        const IpccObserverProxy::TransistionSequence&  transitions);
      std::ostream& operator<<(
        std::ostream&                                 os,
        const IpccObserverProxy::TransRecord&          transition);
    } // namespace appl
  } // namespace cc
} // namespace lmp

#endif /* LIBS_IPCC_IMPL_HPP_ */
