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

namespace lmp
{
  namespace msg
  {
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
