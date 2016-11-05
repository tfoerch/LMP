/*
 * LocalNodeId.cpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "obj/LocalNodeId_def.hpp"

#include <boost/asio/buffer.hpp>
#include <boost/asio/buffers_iterator.hpp>

typedef boost::asio::buffers_iterator<boost::asio::const_buffers_1>  BufIterType;
template struct lmp::obj::nodeid::parse::local_node_id_grammar<BufIterType>;

std::ostream& lmp::obj::nodeid::operator<<(
  std::ostream&                         os,
  const lmp::obj::nodeid::LocalNodeIdData&  localNodeId)
{
  os << (localNodeId.m_negotiable ? "negotiable" : "not negotiable") << ", "
	 << localNodeId.m_nodeId;
  return os;
}
