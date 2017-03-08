#ifndef LIBS_IPCC_OBSERVERIF_HPP_
#define LIBS_IPCC_OBSERVERIF_HPP_
/*
 * IPCC_ObserverIF.hpp
 *
 *  Created on: 11.03.2015
 *      Author: tom
 */

namespace lmp
{
  namespace cc
  {
    class IpccApplicationIF;

    namespace appl
    {
      class State;
      class Event;
      class Action;
      class IpccObserverIF
      {
      public:
        inline void notifyTransition(
          const IpccApplicationIF&  ipcc,
          const appl::State&        sourceState,
          const appl::Event&        event,
          const appl::State&        targetState,
          const appl::Action&       action)
        {  do_notifyTransition(ipcc, sourceState, event, targetState, action); }
        virtual ~IpccObserverIF(){}
      private:
        virtual void do_notifyTransition(
          const IpccApplicationIF&  ipcc,
          const appl::State&        sourceState,
          const appl::Event&        event,
          const appl::State&        targetState,
          const appl::Action&       action) = 0;
      };
      class IpccObserverProxyIF : public IpccObserverIF
      {
      public:
        inline bool operator==(
          const IpccObserverProxyIF& other) const
          { return is_equal(other); }
        IpccObserverProxyIF* clone() const
        { return do_clone(); }
        virtual ~IpccObserverProxyIF(){}
      private:
        virtual bool is_equal(
          const IpccObserverProxyIF& other) const = 0;
        virtual IpccObserverProxyIF* do_clone() const = 0;
      };
      inline IpccObserverProxyIF* new_clone(
        const IpccObserverProxyIF& observer)
      {
        return observer.clone();
      }
    } // namespace appl
  } // namespace cc
} // namespace lmp


#endif /* LIBS_IPCC_OBSERVERIF_HPP_ */
