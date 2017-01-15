/*
 * ConfigNack.cpp
 *
 *  Created on: 20.02.2015
 *      Author: tom
 */

#include "ConfigNack_def.hpp"
#include <boost/asio/buffer.hpp>
#include <boost/asio/buffers_iterator.hpp>
#include <iostream>

typedef boost::asio::buffers_iterator<boost::asio::const_buffers_1>  BufIterType;
template struct lmp::msg::parse::config_nack_grammar<BufIterType>;

namespace lmp
{
  namespace msg
  {
    lmp::DWORD getLength(
      const ConfigNackMsg&  configNack)
    {
      lmp::DWORD length =
        ( lmp::msg::c_headerLength +
          lmp::obj::getLength(configNack.m_localCCId) +
          lmp::obj::getLength(configNack.m_localNodeId) +
          lmp::obj::getLength(configNack.m_remoteCCId) +
          lmp::obj::getLength(configNack.m_messageId) +
          lmp::obj::getLength(configNack.m_remoteNodeId) +
          lmp::obj::getLength(configNack.m_helloConfig) );
      return length;
    }
    bool operator==(
      const ConfigNackMsg&  first,
      const ConfigNackMsg&  second)
    {
      return
        ( first.m_flags == second.m_flags &&
          first.m_localCCId == second.m_localCCId &&
          first.m_localNodeId == second.m_localNodeId &&
          first.m_remoteCCId == second.m_remoteCCId &&
          first.m_messageId == second.m_messageId &&
          first.m_remoteNodeId == second.m_remoteNodeId &&
          first.m_helloConfig == second.m_helloConfig );
    }
    std::ostream& operator<<(
	  std::ostream&          os,
	  const ConfigNackMsg& configNack)
    {
      std::cout << "ConfigNackMsg(" << static_cast<lmp::WORD>(configNack.m_flags)
	  		    << ", " << configNack.m_localCCId
				<< ", " << configNack.m_localNodeId
				<< ", " << configNack.m_remoteCCId
				<< ", " << configNack.m_messageId
				<< ", " << configNack.m_remoteNodeId
				<< ", " << configNack.m_helloConfig
				<< ")";
      return os;
    }
  } // namespace msg
} // namespace lmp
