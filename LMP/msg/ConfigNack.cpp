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
