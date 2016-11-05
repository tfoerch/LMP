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
		struct CCId_Variants_Printer : boost::static_visitor<std::ostream&>
		{
		  CCId_Variants_Printer(std::ostream& os)
		  : m_os(os)
		  {}
		  std::ostream& operator()(const lmp::obj::ccid::LocalCCIdData& localCCId) const
		  {
			m_os << localCCId;
			return m_os;
		  }
		  std::ostream& operator()(const lmp::obj::ccid::RemoteCCIdData& remoteCCId) const
		  {
			m_os << remoteCCId;
			return m_os;
		  }
		  std::ostream& operator()(const lmp::obj::ccid::UnknownCCIdCTypeData& unknownCCId) const
		  {
			m_os << unknownCCId;
			return m_os;
		  }
		  std::ostream&   m_os;
		};
		struct MessageId_Variants_Printer : boost::static_visitor<std::ostream&>
		{
		  MessageId_Variants_Printer(std::ostream& os)
		  : m_os(os)
		  {}
		  std::ostream& operator()(const lmp::obj::msgid::MessageIdData& messageId) const
		  {
			m_os << messageId;
			return m_os;
		  }
		  std::ostream& operator()(const lmp::obj::msgid::MessageIdAckData& messageAckId) const
		  {
			m_os << messageAckId;
			return m_os;
		  }
		  std::ostream& operator()(const lmp::obj::msgid::UnknownMessageIdCTypeData& unknownMessageId) const
		  {
			m_os << unknownMessageId;
			return m_os;
		  }
		  std::ostream&   m_os;
		};
		struct NodeId_Variants_Printer : boost::static_visitor<std::ostream&>
		{
		  NodeId_Variants_Printer(std::ostream& os)
		  : m_os(os)
		  {}
		  std::ostream& operator()(const lmp::obj::nodeid::LocalNodeIdData& nodeId) const
		  {
			m_os << nodeId;
			return m_os;
		  }
		  std::ostream& operator()(const lmp::obj::nodeid::RemoteNodeIdData& nodeId) const
		  {
			m_os << nodeId;
			return m_os;
		  }
		  std::ostream& operator()(const lmp::obj::nodeid::UnknownNodeIdCTypeData& unknownNodeId) const
		  {
			m_os << unknownNodeId;
			return m_os;
		  }
		  std::ostream&   m_os;
		};
		struct Config_Variants_Printer : boost::static_visitor<std::ostream&>
		{
		  Config_Variants_Printer(std::ostream& os)
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
		struct Hello_Variants_Printer : boost::static_visitor<std::ostream&>
		{
		  Hello_Variants_Printer(std::ostream& os)
		  : m_os(os)
		  {}
		  std::ostream& operator()(const lmp::obj::hello::HelloData& hello) const
		  {
			m_os << hello;
			return m_os;
		  }
		  std::ostream& operator()(const lmp::obj::hello::UnknownHelloCTypeData& unknownHello) const
		  {
			m_os << unknownHello;
			return m_os;
		  }
		  std::ostream&   m_os;
		};
		std::ostream& operator<<(std::ostream& os, const UnknownObject& unknownObject)
		{
		  os << static_cast<lmp::WORD>(unknownObject.m_class_type)
			 << ", " << static_cast<lmp::WORD>(unknownObject.m_object_class)
			 << ", " << unknownObject.m_length
			 << ", '" << std::hex;
		  for (std::vector<lmp::BYTE>::const_iterator iter = unknownObject.m_data.begin();
			   iter != unknownObject.m_data.end();
			   ++iter)
		  {
			if (iter != unknownObject.m_data.begin())
			{
			  os << " ";
			}
			os << std::setw(2) << std::setfill('0') << static_cast<lmp::WORD>(*iter);
		  }
		  os << "'" << std::dec;
		  return os;
		}
		typedef
		  boost::variant<ControlChannelIdVariants,
						 MessageIdVariants,
						 NodeIdVariants,
						 ConfigVariants,
						 HelloVariants,
						 UnknownObject>          ObjectVariants;
		struct obj_variants_printer : boost::static_visitor<std::ostream&>
		{
		  obj_variants_printer(std::ostream& os)
		  : m_os(os)
		  {}
		  std::ostream& operator()(const ControlChannelIdVariants& controlChannelId) const
		  {
			m_os << controlChannelId;
			return m_os;
		  }
		  std::ostream& operator()(const MessageIdVariants& messageId) const
		  {
			m_os << messageId;
			return m_os;
		  }
		  std::ostream& operator()(const NodeIdVariants& nodeId) const
		  {
			m_os << nodeId;
			return m_os;
		  }
		  std::ostream& operator()(const ConfigVariants& config) const
		  {
			m_os << config;
			return m_os;
		  }
		  std::ostream& operator()(const HelloVariants& hello) const
		  {
			m_os << hello;
			return m_os;
		  }
		  std::ostream& operator()(const UnknownObject& unknownObject) const
		  {
			m_os << unknownObject;
			return m_os;
		  }
		  std::ostream&   m_os;
		};
		std::ostream& operator<<(
		  std::ostream&          os,
		  const ObjectSequence&  objectSequence)
		{
		  for (std::vector<ObjectVariants>::const_iterator iter = objectSequence.m_objects.begin();
			   iter != objectSequence.m_objects.end();
			   ++iter)
		  {
			if (iter != objectSequence.m_objects.begin())
			{
			  os << ", ";
			}
			boost::apply_visitor(obj_variants_printer(os), *iter);
		  }
		  return os;
		}
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
