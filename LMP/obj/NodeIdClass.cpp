/*
 * NodeIdClass.cpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "obj/NodeIdClass_def.hpp"

#include <boost/asio/buffer.hpp>
#include <boost/asio/buffers_iterator.hpp>

typedef boost::asio::buffers_iterator<boost::asio::const_buffers_1>  BufIterType;
template struct lmp::obj::nodeid::parse::node_id_body_grammar<BufIterType>;
typedef boost::asio::buffers_iterator<boost::asio::mutable_buffers_1>  BufOutIterType;
template struct lmp::obj::nodeid::generate::node_id_body_grammar<BufOutIterType>;

std::ostream& lmp::obj::nodeid::operator<<(
  std::ostream&     os,
  const ClassType&  cType)
{
  switch(cType)
  {
    case ClassType::LocalNodeId:
      os << "LocalNodeId";
      break;
    case ClassType::RemoteNodeId:
      os << "RemoteNodeId";
      break;
  }
  return os;
}

bool lmp::obj::nodeid::IsEqualFtor::operator()(
  const  NodeIdBody& first,
  const  NodeIdBody& second) const
{
  return ( first.m_nodeId == second.m_nodeId );
}

const lmp::WORD lmp::obj::nodeid::GetLengthFtor::c_length = 4;

lmp::WORD lmp::obj::nodeid::GetLengthFtor::operator()(
  const NodeIdBody& nodeIdBody) const
{
  return c_length;
}

std::ostream& lmp::obj::nodeid::operator<<(
  std::ostream&                        os,
  const lmp::obj::nodeid::NodeIdBody&  nodeIdBody)
{
  os << nodeIdBody.m_nodeId;
  return os;
}

