/*
 * RemoteNodeId.cpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "obj/RemoteNodeId_def.hpp"

#include <boost/asio/buffer.hpp>
#include <boost/asio/buffers_iterator.hpp>

typedef boost::asio::buffers_iterator<boost::asio::const_buffers_1>  BufIterType;
template struct lmp::obj::nodeid::parse::remote_node_id_grammar<BufIterType>;

std::ostream& lmp::obj::nodeid::operator<<(
  std::ostream&                              os,
  const lmp::obj::nodeid::RemoteNodeIdData&  remoteNodeId)
{
  os << (remoteNodeId.m_negotiable ? "negotiable" : "not negotiable") << ", "
	 << remoteNodeId.m_nodeId;
  return os;
}
