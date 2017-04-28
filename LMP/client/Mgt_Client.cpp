// eg3_clt.cc - This is the source code of example 3 used in Chapter 2
//              "The Basics" of the omniORB user guide.
//
//              This is the client. It uses the COSS naming service
//              to obtain the object reference.
//
// Usage: eg3_clt
//
//
//        On startup, the client lookup the object reference from the
//        COS naming service.
//
//        The name which the object is bound to is as follows:
//              root  [context]
//               |
//              text  [context] kind [my_context]
//               |
//              Echo  [object]  kind [Object]
//
#include <Mgt_ClientFixture.hpp>
#include <Mgt_NodeRegistry.hpp>
#include <Mgt_IPCCObserver.hpp>
#include <Mgt_NeighborAdjacencyObserver.hpp>
#include <lmp_mgtif_node.hpp>
#include "lmp_mgtif_netif.hpp"               // for NetworkIF_var, IPCC_ptr

#define BOOST_TEST_MODULE LMPClient
#include <boost/test/included/unit_test.hpp>

#include <iostream>

struct MyConfig {
  MyConfig()   { std::cout << "global setup\n"; }
  ~MyConfig()  { std::cout << "global teardown\n"; }
};


BOOST_GLOBAL_FIXTURE( MyConfig );

BOOST_AUTO_TEST_SUITE( LMPClient )

BOOST_FIXTURE_TEST_CASE ( test_case1, LaunchServer )
{
  std::cout << "running test case 1\n";
  BOOST_CHECK(theNodeRegistry->isNodeRegistered(theNodeId));
  ::lmp_node::Node_ptr node = theNodeRegistry->getNode(theNodeId);
  BOOST_CHECK(!CORBA::is_nil(node));
  if (!CORBA::is_nil(node))
  {
    std::cout << "test case 1 node retrieved\n";
    ::lmp_netif::NetworkIF_ptr netif = node->createNetIF(7011, 2130706433, 7011);
    BOOST_CHECK(!CORBA::is_nil(netif));
    if (theOrb &&
        !CORBA::is_nil(netif))
    {
      CORBA::ORB_var orb = *theOrb;
      CORBA::Object_var obj = orb->resolve_initial_references("RootPOA");
      PortableServer::POA_var poa = PortableServer::POA::_narrow(obj);
      lmp_neighbor_adjacency_observer::NeighborAdjacencyObserver_i* neighborAdjacencyObserver =
        new lmp_neighbor_adjacency_observer::NeighborAdjacencyObserver_i(orb, poa);
      poa->activate_object(neighborAdjacencyObserver);
      lmp_neighbor_adjacency_observer::NeighborAdjacencyObserver_ptr neighborAdjacencyObserverPtr = neighborAdjacencyObserver->_this();
      std::cout << "before register observer" << std::endl;
      node->registerNeighborAdjacencyObserver(neighborAdjacencyObserverPtr);
      std::cout << "before enable" << std::endl;
      netif->enable();
      std::cout << "after enable" << std::endl;
      netif->disable();

      node->deregisterNeighborAdjacencyObserver(neighborAdjacencyObserverPtr);
      neighborAdjacencyObserverPtr->destroy();
//    ::lmp_ipcc::IPCC_ptr ipcc = node->createIPCC(7011, 2130706433, 2130706433, 7011, 7012);
//    BOOST_CHECK(!CORBA::is_nil(ipcc));
//    if (theOrb &&
//        !CORBA::is_nil(ipcc))
//    {
//      CORBA::ORB_var orb = *theOrb;
//      CORBA::Object_var obj = orb->resolve_initial_references("RootPOA");
//      PortableServer::POA_var poa = PortableServer::POA::_narrow(obj);

//      lmp_ipcc_observer::IPCCObserver_i* ipccObserver =
//          new lmp_ipcc_observer::IPCCObserver_i(orb, poa);
//      poa->activate_object(ipccObserver);
//      lmp_ipcc_observer::IPCCObserver_ptr ipccObserverPtr = ipccObserver->_this();
//      std::cout << "before register observer" << std::endl;
//      ipcc->registerObserver(ipccObserverPtr);
//      std::cout << "before enable" << std::endl;
//      ipcc->enable();
//      std::cout << "after enable" << std::endl;
//      ipcc->disable();
//
//      ipcc->deregisterObserver(ipccObserverPtr);
//      ipccObserverPtr->destroy();
    }
  }
}

BOOST_AUTO_TEST_SUITE_END()

