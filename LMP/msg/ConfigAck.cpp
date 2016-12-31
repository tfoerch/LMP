/*
 * ConfigAck.cpp
 *
 *  Created on: 20.02.2015
 *      Author: tom
 */

#include "ConfigAck_def.hpp"
#include <boost/asio/buffer.hpp>
#include <boost/asio/buffers_iterator.hpp>
#include <iostream>

typedef boost::asio::buffers_iterator<boost::asio::const_buffers_1>  BufIterType;
template struct lmp::msg::parse::config_ack_grammar<BufIterType>;

namespace lmp
{
  namespace msg
  {
    std::ostream& operator<<(
      std::ostream&             os,
	  const ConfigAckMsg& configAck)
    {
      std::cout << "ConfigAckMsg(" << static_cast<lmp::WORD>(configAck.m_flags)
	            << ", " << configAck.m_localCCId
				<< ", " << configAck.m_localNodeId
				<< ", " << configAck.m_remoteCCId
				<< ", " << configAck.m_messageId
				<< ", " << configAck.m_remoteNodeId
				<< ")";
      return os;
    }
  } // namespace msg
} // namespace lmp
