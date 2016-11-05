#ifndef LMP_MESSAGE_HPP_
#define LMP_MESSAGE_HPP_
/*
 * Message.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "base/ProtocolTypes.hpp"                 // for DWORD
#include "obj/LocalCCId.hpp"
#include "obj/RemoteCCId.hpp"
#include "obj/UnknownCCIdCType.hpp"
#include "obj/LocalNodeId.hpp"
#include "obj/RemoteNodeId.hpp"
#include "obj/UnknownNodeIdCType.hpp"
#include "obj/MessageId.hpp"
#include "obj/MessageIdAck.hpp"
#include "obj/UnknownMessageIdCType.hpp"
#include "obj/HelloConfig.hpp"
#include "obj/UnknownConfigCType.hpp"
#include "obj/Hello.hpp"
#include "obj/UnknownHelloCType.hpp"

#include <boost/variant.hpp>
#include <boost/fusion/include/adapt_struct.hpp>
#include <iostream>
#include <vector>

namespace lmp
{
  namespace msg
  {
	  namespace parse
	  {
		typedef
		  boost::variant<lmp::obj::ccid::LocalCCIdData,
		                 lmp::obj::ccid::RemoteCCIdData,
						 lmp::obj::ccid::UnknownCCIdCTypeData>          ControlChannelIdVariants;
		typedef
		  boost::variant<lmp::obj::msgid::MessageIdData,
		                 lmp::obj::msgid::MessageIdAckData,
						 lmp::obj::msgid::UnknownMessageIdCTypeData>          MessageIdVariants;
		typedef
		  boost::variant<lmp::obj::nodeid::LocalNodeIdData,
		                 lmp::obj::nodeid::RemoteNodeIdData,
						 lmp::obj::nodeid::UnknownNodeIdCTypeData>          NodeIdVariants;
		typedef
		  boost::variant<lmp::obj::config::HelloConfigData,
		                 lmp::obj::config::UnknownConfigCTypeData>          ConfigVariants;
		typedef
		  boost::variant<lmp::obj::hello::HelloData,
		                 lmp::obj::hello::UnknownHelloCTypeData>          HelloVariants;
		struct UnknownObject
		{
		  bool                    m_negotiatable;
		  lmp::BYTE               m_class_type;
		  lmp::BYTE               m_object_class;
		  lmp::WORD               m_length;
		  std::vector<lmp::BYTE>  m_data;
		};
		std::ostream& operator<<(std::ostream& os, const UnknownObject& unknownObject);
		typedef
		  boost::variant<ControlChannelIdVariants,
						 MessageIdVariants,
						 NodeIdVariants,
						 ConfigVariants,
						 HelloVariants,
						 UnknownObject>          ObjectVariants;
		struct ObjectSequence
		{
		  std::vector<ObjectVariants>   m_objects;
		};
		std::ostream& operator<<(
		  std::ostream&          os,
		  const ObjectSequence&  objectSequence);
		struct ConfigMsgData
		{
		  lmp::obj::ccid::LocalCCIdData    m_localCCId;
		  lmp::obj::msgid::MessageIdData    m_messageId;
		  lmp::obj::nodeid::LocalNodeIdData  m_localNodeId;
		  lmp::obj::config::HelloConfigData      m_helloConfig;
		};
		std::ostream& operator<<(
		  std::ostream&          os,
		  const ConfigMsgData& config);
		struct ConfigAckMsgData
		{
		  lmp::obj::ccid::LocalCCIdData     m_localCCId;
		  lmp::obj::nodeid::LocalNodeIdData   m_localNodeId;
		  lmp::obj::ccid::RemoteCCIdData    m_remoteCCId;
		  lmp::obj::msgid::MessageIdAckData  m_messageId;
		  lmp::obj::nodeid::RemoteNodeIdData  m_remoteNodeId;
		};
		std::ostream& operator<<(
		  std::ostream&             os,
		  const ConfigAckMsgData& configAck);
		struct ConfigNackMsgData
		{
		  lmp::obj::ccid::LocalCCIdData     m_localCCId;
		  lmp::obj::nodeid::LocalNodeIdData   m_localNodeId;
		  lmp::obj::ccid::RemoteCCIdData    m_remoteCCId;
		  lmp::obj::msgid::MessageIdAckData  m_messageId;
		  lmp::obj::nodeid::RemoteNodeIdData  m_remoteNodeId;
		  lmp::obj::config::HelloConfigData       m_helloConfig;
		};
		std::ostream& operator<<(
		  std::ostream&          os,
		  const ConfigNackMsgData& configNack);
		struct UnknownMessage
		{
		  lmp::BYTE               m_type;
		  lmp::WORD               m_length;
		  ObjectSequence          m_objects;
		};
		std::ostream& operator<<(
		  std::ostream&          os,
		  const UnknownMessage&  unknownMessage);
		typedef
		  boost::variant<ConfigMsgData,
						 ConfigAckMsgData,
						 ConfigNackMsgData,
						 UnknownMessage>     MsgVariants;
		struct MsgData
		{
		  lmp::BYTE             m_flags;
		  MsgVariants           m_message;
		};
		std::ostream& operator<<(
		  std::ostream&      os,
		  const MsgData&     msgData);
	  }
  } // namespace msg
} // namespace lmp


BOOST_FUSION_ADAPT_STRUCT(
  lmp::msg::parse::UnknownObject,
  (bool,                    m_negotiatable)
  (lmp::BYTE,               m_class_type)
  (lmp::BYTE,               m_object_class)
  (lmp::WORD,               m_length)
  (std::vector<lmp::BYTE>,  m_data)
)

BOOST_FUSION_ADAPT_STRUCT(
  lmp::msg::parse::ObjectSequence,
  (std::vector<lmp::msg::parse::ObjectVariants>,  m_objects)
)

BOOST_FUSION_ADAPT_STRUCT(
  lmp::msg::parse::ConfigMsgData,
  (lmp::obj::ccid::LocalCCIdData,       m_localCCId)
  (lmp::obj::msgid::MessageIdData,       m_messageId)
  (lmp::obj::nodeid::LocalNodeIdData,     m_localNodeId)
  (lmp::obj::config::HelloConfigData,         m_helloConfig)
)

BOOST_FUSION_ADAPT_STRUCT(
  lmp::msg::parse::ConfigAckMsgData,
  (lmp::obj::ccid::LocalCCIdData,       m_localCCId)
  (lmp::obj::nodeid::LocalNodeIdData,     m_localNodeId)
  (lmp::obj::ccid::RemoteCCIdData,      m_remoteCCId)
  (lmp::obj::msgid::MessageIdAckData,    m_messageId)
  (lmp::obj::nodeid::RemoteNodeIdData,    m_remoteNodeId)
)

BOOST_FUSION_ADAPT_STRUCT(
  lmp::msg::parse::ConfigNackMsgData,
  (lmp::obj::ccid::LocalCCIdData,       m_localCCId)
  (lmp::obj::nodeid::LocalNodeIdData,     m_localNodeId)
  (lmp::obj::ccid::RemoteCCIdData,      m_remoteCCId)
  (lmp::obj::msgid::MessageIdAckData,    m_messageId)
  (lmp::obj::nodeid::RemoteNodeIdData,    m_remoteNodeId)
  (lmp::obj::config::HelloConfigData,         m_helloConfig)
)

BOOST_FUSION_ADAPT_STRUCT(
  lmp::msg::parse::UnknownMessage,
  (lmp::BYTE,                         m_type)
  (lmp::WORD,                         m_length)
  (lmp::msg::parse::ObjectSequence,        m_objects)
)

BOOST_FUSION_ADAPT_STRUCT(
  lmp::msg::parse::MsgData,
  (lmp::BYTE,                         m_flags)
  (lmp::msg::parse::MsgVariants,           m_message)
)


#endif /* LMP_MSG_CONFIG_HPP_ */
