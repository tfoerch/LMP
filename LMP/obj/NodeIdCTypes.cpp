/*
 * NodeIdCTypes.cpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "obj/NodeIdCTypes_def.hpp"

#include <boost/asio/buffer.hpp>
#include <boost/asio/buffers_iterator.hpp>

typedef boost::asio::buffers_iterator<boost::asio::const_buffers_1>  BufIterType;
template struct lmp::obj::nodeid::parse::node_id_ctypes_grammar<BufIterType>;

namespace
{
  struct NodeIdCTypes_Printer : boost::static_visitor<std::ostream&>
  {
    NodeIdCTypes_Printer(std::ostream& os)
    : m_os(os)
    {}
    std::ostream& operator()(const lmp::obj::nodeid::LocalNodeIdData& nodeId) const
    {
	  m_os << nodeId;
	  return m_os;
    }
    std::ostream& operator()(const lmp::obj::nodeid::RemoteNodeIdData& nodeId) const
    {
	  m_os << nodeId;
	  return m_os;
    }
    std::ostream& operator()(const lmp::obj::nodeid::UnknownNodeIdCTypeData& unknownNodeId) const
    {
	  m_os << unknownNodeId;
	  return m_os;
    }
    std::ostream&   m_os;
  };
}


std::ostream& lmp::obj::nodeid::operator<<(
  std::ostream&                                  os,
  const lmp::obj::nodeid::NodeIdCTypes&          nodeIdCTypes)
{
  boost::apply_visitor(NodeIdCTypes_Printer(os), nodeIdCTypes);
  return os;
}
