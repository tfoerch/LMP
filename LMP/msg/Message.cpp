/*
 * Message.cpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "msg/Message.hpp"
#include <iomanip>

namespace lmp
{
  namespace msg
  {
	  namespace parse
	  {
		std::ostream& operator<<(
		  std::ostream&          os,
		  const ConfigMsgData& config)
		{
		  std::cout << "ConfigMsg(" << config.m_localCCId
					<< ", " << config.m_messageId
					<< ", " << config.m_localNodeId
					<< ", " << config.m_helloConfig
					<< ")";
		  return os;
		}
		std::ostream& operator<<(
		  std::ostream&             os,
		  const ConfigAckMsgData& configAck)
		{
		  std::cout << "ConfigAckMsg(" << configAck.m_localCCId
					<< ", " << configAck.m_localNodeId
					<< ", " << configAck.m_remoteCCId
					<< ", " << configAck.m_messageId
					<< ", " << configAck.m_remoteNodeId
					<< ")";
		  return os;
		}
		std::ostream& operator<<(
		  std::ostream&          os,
		  const ConfigNackMsgData& configNack)
		{
		  std::cout << "ConfigNackMsg(" << configNack.m_localCCId
					<< ", " << configNack.m_localNodeId
					<< ", " << configNack.m_remoteCCId
					<< ", " << configNack.m_messageId
					<< ", " << configNack.m_remoteNodeId
					<< ", " << configNack.m_helloConfig
					<< ")";
		  return os;
		}
		std::ostream& operator<<(
		  std::ostream&          os,
		  const UnknownMessage&  unknownMessage)
		{
		  std::cout << "UnknownMessage(" << static_cast<lmp::WORD>(unknownMessage.m_type)
					<< ", " << unknownMessage.m_length
					<< ", " << unknownMessage.m_objects
					<< ")";
		  return os;
		}
		typedef
		  boost::variant<ConfigMsgData,
						 ConfigAckMsgData,
						 ConfigNackMsgData,
						 UnknownMessage>     MsgVariants;
		struct msg_variants_printer : boost::static_visitor<std::ostream&>
		{
		  msg_variants_printer(std::ostream& os)
		  : m_os(os)
		  {}
		  std::ostream& operator()(const ConfigMsgData& config) const
		  {
			m_os << config << std::endl;
			return m_os;
		  }
		  std::ostream& operator()(const ConfigAckMsgData& configAck) const
		  {
			m_os << configAck << std::endl;
			return m_os;
		  }
		  std::ostream& operator()(const ConfigNackMsgData& configNack) const
		  {
			m_os << configNack << std::endl;
			return m_os;
		  }
		  std::ostream& operator()(const UnknownMessage& unknownMessage) const
		  {
			m_os << unknownMessage << std::endl;
			return m_os;
		  }
		  std::ostream&   m_os;
		};
		std::ostream& operator<<(
		  std::ostream&      os,
		  const MsgData&     msgData)
		{
		  boost::apply_visitor(msg_variants_printer(os), msgData.m_message);
		  return os;
		}
	  }
  } // namespace msg
} // namespace lmp
