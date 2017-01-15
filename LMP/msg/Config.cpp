/*
 * Config.cpp
 *
 *  Created on: 20.02.2015
 *      Author: tom
 */

#include "Config_def.hpp"
#include <boost/asio/buffer.hpp>
#include <boost/asio/buffers_iterator.hpp>
#include <iostream>

typedef boost::asio::buffers_iterator<boost::asio::const_buffers_1>  BufIterType;
template struct lmp::msg::parse::config_grammar<BufIterType>;
typedef boost::asio::buffers_iterator<boost::asio::mutable_buffers_1>  BufOutIterType;
template struct lmp::msg::generate::config_grammar<BufOutIterType>;

namespace lmp
{
  namespace msg
  {
    lmp::DWORD getLength(
      const ConfigMsg&  config)
    {
      lmp::DWORD length =
        ( lmp::msg::c_headerLength +
          lmp::obj::getLength(config.m_localCCId) +
          lmp::obj::getLength(config.m_messageId) +
          lmp::obj::getLength(config.m_localNodeId) +
          lmp::obj::config::getLength(config.m_configObjects) );
      return length;
    }
    bool operator==(
      const ConfigMsg&  first,
      const ConfigMsg&  second)
    {
      return
        ( first.m_flags == second.m_flags &&
          first.m_localCCId == second.m_localCCId &&
          first.m_messageId == second.m_messageId &&
          first.m_localNodeId == second.m_localNodeId &&
          first.m_configObjects == second.m_configObjects );
    }
    std::ostream& operator<<(
      std::ostream&     os,
      const ConfigMsg&  config)
    {
      std::cout << "ConfigMsg(" << static_cast<lmp::WORD>(config.m_flags)
		<< ", " << config.m_localCCId
		<< ", " << config.m_messageId
		<< ", " << config.m_localNodeId
		<< ", " << config.m_configObjects
		<< ")";
      return os;
    }
  } // namespace msg
} // namespace lmp
