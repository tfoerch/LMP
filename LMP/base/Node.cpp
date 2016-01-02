/*
 * Node.cpp
 *
 *  Created on: 20.02.2015
 *      Author: tom
 */

#include "Node.hpp"

namespace lmp
{
  namespace node
  {
    Node::Node(
      lmp::DWORD                       nodeId,
	  const boost::asio::ip::address&  loopbackAddress)
      : m_nodeId(nodeId),
		m_loopbackAddress(loopbackAddress)
    {
    }
    Node::~Node()
    {
    }
    void Node::enable()
    {
    }
    void Node::disable()
    {
    }
    lmp::DWORD  Node::getNodeId() const
    {
      return m_nodeId;
    }
  } // namespace node
} // namespace lmp
