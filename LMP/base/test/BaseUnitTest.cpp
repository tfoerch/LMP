/*
 * BaseUnitTest.cpp
 *
 *  Created on: 27.02.2015
 *      Author: tom
 */

#include "base/Node.hpp"

#include <boost/asio/ip/address.hpp>


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

