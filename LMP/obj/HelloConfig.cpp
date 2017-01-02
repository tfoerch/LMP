/*
 * HelloConfig.cpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "obj/HelloConfig_def.hpp"

#include <boost/asio/buffer.hpp>
#include <boost/asio/buffers_iterator.hpp>

typedef boost::asio::buffers_iterator<boost::asio::const_buffers_1>  BufIterType;
template struct lmp::obj::config::parse::hello_config_body_grammar<BufIterType>;
template struct lmp::obj::parse::object_class_grammar<BufIterType, lmp::obj::config::ClassType, lmp::obj::config::ClassType::HelloConfig>;
typedef boost::asio::buffers_iterator<boost::asio::mutable_buffers_1>  BufOutIterType;
template struct lmp::obj::config::generate::hello_config_body_grammar<BufOutIterType>;
template struct lmp::obj::generate::object_class_grammar<BufOutIterType, lmp::obj::config::ClassType, lmp::obj::config::ClassType::HelloConfig>;
template std::ostream& lmp::obj::operator<< <lmp::obj::ObjectClassTypeTraits<lmp::obj::config::ClassType, lmp::obj::config::ClassType::HelloConfig>>(
  std::ostream&,
  const lmp::obj::ObjectClassTypeData<lmp::obj::ObjectClassTypeTraits<lmp::obj::config::ClassType, lmp::obj::config::ClassType::HelloConfig>>&);

std::ostream& lmp::obj::config::operator<<(
  std::ostream&                             os,
  const lmp::obj::config::HelloConfigBody&  helloConfig)
{
  os << helloConfig.m_helloIntv << ", "
     << helloConfig.m_helloDeadIntv;
  return os;
}
