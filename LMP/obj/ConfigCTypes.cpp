/*
 * ConfigCTypes.cpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "obj/ConfigCTypes_def.hpp"

#include <boost/asio/buffer.hpp>
#include <boost/asio/buffers_iterator.hpp>

typedef boost::asio::buffers_iterator<boost::asio::const_buffers_1>  BufIterType;
template struct lmp::obj::config::parse::config_ctypes_grammar<BufIterType>;

namespace
{
  struct ConfigCTypes_Printer : boost::static_visitor<std::ostream&>
  {
    ConfigCTypes_Printer(std::ostream& os)
    : m_os(os)
    {}
    std::ostream& operator()(const lmp::obj::config::HelloConfigData& helloConfig) const
    {
	  m_os << helloConfig;
	  return m_os;
    }
    std::ostream& operator()(const lmp::obj::config::UnknownConfigCTypeData& unknownConfig) const
    {
	  m_os << unknownConfig;
	  return m_os;
    }
    std::ostream&   m_os;
  };
}

std::ostream& lmp::obj::config::operator<<(
  std::ostream&                                  os,
  const lmp::obj::config::ConfigCTypes&          configCTypes)
{
  boost::apply_visitor(ConfigCTypes_Printer(os), configCTypes);
  return os;
}
