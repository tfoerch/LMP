#include <Mgt_NodeApplProxy.hpp>
#include <iostream>

namespace lmp_node
{
  NodeApplProxy::NodeApplProxy(
    lmp::node::NodeApplicationIF&   node,
    NeighborAdjacencyChangeFtorIF&  neighborAdjAddedFtor,
    NeighborAdjacencyChangeFtorIF&  neighborAdjRemovedFtor)
  : m_node(node),
    m_neighborAdjAddedFtor(neighborAdjAddedFtor),
    m_neighborAdjRemovedFtor(neighborAdjRemovedFtor)
  {
  }

  void NodeApplProxy::do_enable()
  {
    m_node.enable();
  }
  void NodeApplProxy::do_disable()
  {
    m_node.disable();
  }
  lmp::DWORD NodeApplProxy::do_getNodeId() const
  {
    return m_node.getNodeId();
  }
  lmp::neighbor::NeighborApplicationIF const* NodeApplProxy::do_getNeighbor(
    lmp::DWORD  neighborNodeId) const
  {
    return m_node.getNeighbor(neighborNodeId);
  }
  void NodeApplProxy::do_neighborAdjacencyAdded(
    lmp::DWORD                   neighborNodeId,
    lmp::cc::IpccApplicationIF&  ipcc)
  {
    m_node.neighborAdjacencyAdded(neighborNodeId, ipcc);
    m_neighborAdjAddedFtor(neighborNodeId, ipcc);
  }
  void NodeApplProxy::do_neighborAdjacencyRemoved(
    lmp::DWORD                   neighborNodeId,
    lmp::cc::IpccApplicationIF&  ipcc)
  {
    m_node.neighborAdjacencyRemoved(neighborNodeId, ipcc);
    m_neighborAdjRemovedFtor(neighborNodeId, ipcc);
  }


} // end namespace lmp_node
