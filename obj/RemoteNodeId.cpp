/*
 * RemoteNodeId.cpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "obj/RemoteNodeId.hpp"
#include "obj/ObjectClass_def.hpp"

#include <boost/asio/buffer.hpp>
#include <boost/asio/buffers_iterator.hpp>

typedef boost::asio::buffers_iterator<boost::asio::const_buffers_1>  BufIterType;
template struct lmp::obj::parse::object_class_grammar<BufIterType, lmp::obj::nodeid::ClassType, lmp::obj::nodeid::ClassType::RemoteNodeId>;
typedef boost::asio::buffers_iterator<boost::asio::mutable_buffers_1>  BufOutIterType;
template struct lmp::obj::generate::object_class_grammar<BufOutIterType, lmp::obj::nodeid::ClassType, lmp::obj::nodeid::ClassType::RemoteNodeId>;
template std::ostream& lmp::obj::operator<< <lmp::obj::ObjectClassTypeTraits<lmp::obj::nodeid::ClassType, lmp::obj::nodeid::ClassType::RemoteNodeId>>(
  std::ostream&,
  const lmp::obj::ObjectClassTypeData<lmp::obj::ObjectClassTypeTraits<lmp::obj::nodeid::ClassType, lmp::obj::nodeid::ClassType::RemoteNodeId>>&);
template bool lmp::obj::operator== <lmp::obj::ObjectClassTypeTraits<lmp::obj::nodeid::ClassType, lmp::obj::nodeid::ClassType::RemoteNodeId>>(
  const lmp::obj::ObjectClassTypeData<lmp::obj::ObjectClassTypeTraits<lmp::obj::nodeid::ClassType, lmp::obj::nodeid::ClassType::RemoteNodeId>>&,
  const lmp::obj::ObjectClassTypeData<lmp::obj::ObjectClassTypeTraits<lmp::obj::nodeid::ClassType, lmp::obj::nodeid::ClassType::RemoteNodeId>>&);

