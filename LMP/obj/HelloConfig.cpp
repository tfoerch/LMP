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
template struct lmp::obj::config::parse::hello_config_grammar<BufIterType>;

std::ostream& lmp::obj::config::operator<<(
  std::ostream&                           os,
  const lmp::obj::config::HelloConfigData&  helloConfig)
{
  os << (helloConfig.m_negotiable ? "negotiable" : "not negotiable") << ", "
	 << helloConfig.m_helloIntv << ", "
	 << helloConfig.m_helloDeadIntv;
  return os;
}
