#ifndef MSG_PARSE_GRAMMAR_HPP_
#define MSG_PARSE_GRAMMAR_HPP_
/*
 * ObjectClassTypeTraits.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "msg/MsgType.hpp"
#include "obj/ObjectClass.hpp"
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/qi_binary.hpp>
#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/spirit/include/phoenix_fusion.hpp>
#include <boost/spirit/include/phoenix_stl.hpp>
#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/phoenix/object/static_cast.hpp>

#include <type_traits>
#include <iomanip>

namespace lmp
{
  namespace msg
  {
	  namespace parse
	  {
		struct LocalCCIdData
		{
		  bool        m_negotiatable;
		  lmp::DWORD  m_CCId;
		};
		std::ostream& operator<<(std::ostream& os, const LocalCCIdData& localCCId)
		{
		  os << localCCId.m_CCId;
		  return os;
		}
		struct RemoteCCIdData
		{
		  bool        m_negotiatable;
		  lmp::DWORD  m_CCId;
		};
		std::ostream& operator<<(std::ostream& os, const RemoteCCIdData& remoteCCId)
		{
		  os << remoteCCId.m_CCId;
		  return os;
		}
		struct UnknownCCIdCTypeData
		{
		  bool                    m_negotiatable;
		  lmp::BYTE               m_class_type;
		  lmp::WORD               m_length;
		  std::vector<lmp::BYTE>  m_data;
		};
		std::ostream& operator<<(std::ostream& os, const UnknownCCIdCTypeData& unknownCCId)
		{
		  os << static_cast<lmp::WORD>(unknownCCId.m_class_type)
			 << ", " << unknownCCId.m_length
			 << ", '" << std::hex;
		  for (std::vector<lmp::BYTE>::const_iterator iter = unknownCCId.m_data.begin();
			   iter != unknownCCId.m_data.end();
			   ++iter)
		  {
			if (iter != unknownCCId.m_data.begin())
			{
			  os << " ";
			}
			os << std::setw(2) << std::setfill('0') << static_cast<lmp::WORD>(*iter);
		  }
		  os << "'" << std::dec;
		  return os;
		}
		typedef
		  boost::variant<LocalCCIdData,
						 RemoteCCIdData,
						 UnknownCCIdCTypeData>          ControlChannelIdVariants;
		struct CCId_Variants_Printer : boost::static_visitor<std::ostream&>
		{
		  CCId_Variants_Printer(std::ostream& os)
		  : m_os(os)
		  {}
		  std::ostream& operator()(const LocalCCIdData& localCCId) const
		  {
			m_os << localCCId;
			return m_os;
		  }
		  std::ostream& operator()(const RemoteCCIdData& remoteCCId) const
		  {
			m_os << remoteCCId;
			return m_os;
		  }
		  std::ostream& operator()(const UnknownCCIdCTypeData& unknownCCId) const
		  {
			m_os << unknownCCId;
			return m_os;
		  }
		  std::ostream&   m_os;
		};
		struct MessageIdData
		{
		  bool        m_negotiatable;
		  lmp::DWORD  m_messageId;
		};
		std::ostream& operator<<(std::ostream& os, const MessageIdData& messageId)
		{
		  os << messageId.m_messageId;
		  return os;
		}
		struct MessageIdAckData
		{
		  bool        m_negotiatable;
		  lmp::DWORD  m_messageId;
		};
		std::ostream& operator<<(std::ostream& os, const MessageIdAckData& messageAckId)
		{
		  os << messageAckId.m_messageId;
		  return os;
		}
		struct LocalNodeIdData
		{
		   bool        m_negotiatable;
		   lmp::DWORD  m_nodeId;
		};
		std::ostream& operator<<(std::ostream& os, const LocalNodeIdData& nodeId)
		{
		  os << nodeId.m_nodeId;
		  return os;
		}
		struct RemoteNodeIdData
		{
		   bool        m_negotiatable;
		   lmp::DWORD  m_nodeId;
		};
		std::ostream& operator<<(std::ostream& os, const RemoteNodeIdData& nodeId)
		{
		  os << nodeId.m_nodeId;
		  return os;
		}
		struct HelloConfig
		{
		   bool        m_negotiatable;
		   lmp::WORD   m_helloIntv;
		   lmp::WORD   m_helloDeadIntv;
		};
		std::ostream& operator<<(std::ostream& os, const HelloConfig& helloConfig)
		{
		  os << helloConfig.m_helloIntv << ", " << helloConfig.m_helloDeadIntv;
		  return os;
		}
		struct UnknownObject
		{
		  bool                    m_negotiatable;
		  lmp::BYTE               m_class_type;
		  lmp::BYTE               m_object_class;
		  lmp::WORD               m_length;
		  std::vector<lmp::BYTE>  m_data;
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
						 MessageIdData,
						 MessageIdAckData,
						 LocalNodeIdData,
						 RemoteNodeIdData,
						 HelloConfig,
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
		  std::ostream& operator()(const MessageIdData& messageId) const
		  {
			m_os << messageId;
			return m_os;
		  }
		  std::ostream& operator()(const MessageIdAckData& messageId) const
		  {
			m_os << messageId;
			return m_os;
		  }
		  std::ostream& operator()(const LocalNodeIdData& localNodeId) const
		  {
			m_os << localNodeId;
			return m_os;
		  }
		  std::ostream& operator()(const RemoteNodeIdData& remoteNodeId) const
		  {
			m_os << remoteNodeId;
			return m_os;
		  }
		  std::ostream& operator()(const HelloConfig& helloConfig) const
		  {
			m_os << helloConfig;
			return m_os;
		  }
		  std::ostream& operator()(const UnknownObject& unknownObject) const
		  {
			m_os << unknownObject;
			return m_os;
		  }
		  std::ostream&   m_os;
		};
		struct ObjectSequence
		{
		  std::vector<ObjectVariants>   m_objects;
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
		struct ConfigMsgData
		{
		  LocalCCIdData    m_localCCId;
		  MessageIdData    m_messageId;
		  LocalNodeIdData  m_localNodeId;
		  HelloConfig      m_helloConfig;
		};
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
		struct ConfigAckMsgData
		{
		  LocalCCIdData     m_localCCId;
		  LocalNodeIdData   m_localNodeId;
		  RemoteCCIdData    m_remoteCCId;
		  MessageIdAckData  m_messageId;
		  RemoteNodeIdData  m_remoteNodeId;
		};
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
		struct ConfigNackMsgData
		{
		  LocalCCIdData     m_localCCId;
		  LocalNodeIdData   m_localNodeId;
		  RemoteCCIdData    m_remoteCCId;
		  MessageIdAckData  m_messageId;
		  RemoteNodeIdData  m_remoteNodeId;
		  HelloConfig       m_helloConfig;
		};
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
		struct UnknownMessage
		{
		  lmp::BYTE               m_type;
		  lmp::WORD               m_length;
		  ObjectSequence          m_objects;
		};
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
		struct MsgData
		{
		  lmp::BYTE             m_flags;
		  MsgVariants           m_message;
		};
		std::ostream& operator<<(
		  std::ostream&      os,
		  const MsgData&     msgData)
		{
		  boost::apply_visitor(msg_variants_printer(os), msgData.m_message);
		  return os;
		}
	  }
  }
}

BOOST_FUSION_ADAPT_STRUCT(
  lmp::msg::parse::LocalCCIdData,
  (bool,       m_negotiatable)
  (lmp::DWORD, m_CCId)
)

BOOST_FUSION_ADAPT_STRUCT(
  lmp::msg::parse::RemoteCCIdData,
  (bool,       m_negotiatable)
  (lmp::DWORD, m_CCId)
)

BOOST_FUSION_ADAPT_STRUCT(
  lmp::msg::parse::UnknownCCIdCTypeData,
  (bool,                    m_negotiatable)
  (lmp::BYTE,               m_class_type)
  (lmp::WORD,               m_length)
  (std::vector<lmp::BYTE>,  m_data)
)

BOOST_FUSION_ADAPT_STRUCT(
  lmp::msg::parse::MessageIdData,
  (bool,       m_negotiatable)
  (lmp::DWORD, m_messageId)
)

BOOST_FUSION_ADAPT_STRUCT(
  lmp::msg::parse::MessageIdAckData,
  (bool,       m_negotiatable)
  (lmp::DWORD, m_messageId)
)

BOOST_FUSION_ADAPT_STRUCT(
  lmp::msg::parse::LocalNodeIdData,
  (bool,       m_negotiatable)
  (lmp::DWORD, m_nodeId)
)

BOOST_FUSION_ADAPT_STRUCT(
  lmp::msg::parse::RemoteNodeIdData,
  (bool,       m_negotiatable)
  (lmp::DWORD, m_nodeId)
)

BOOST_FUSION_ADAPT_STRUCT(
  lmp::msg::parse::HelloConfig,
  (bool,       m_negotiatable)
  (lmp::WORD,  m_helloIntv)
  (lmp::WORD,  m_helloDeadIntv)
)

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
  (lmp::msg::parse::LocalCCIdData,       m_localCCId)
  (lmp::msg::parse::MessageIdData,       m_messageId)
  (lmp::msg::parse::LocalNodeIdData,     m_localNodeId)
  (lmp::msg::parse::HelloConfig,         m_helloConfig)
)

BOOST_FUSION_ADAPT_STRUCT(
  lmp::msg::parse::ConfigAckMsgData,
  (lmp::msg::parse::LocalCCIdData,       m_localCCId)
  (lmp::msg::parse::LocalNodeIdData,     m_localNodeId)
  (lmp::msg::parse::RemoteCCIdData,      m_remoteCCId)
  (lmp::msg::parse::MessageIdAckData,    m_messageId)
  (lmp::msg::parse::RemoteNodeIdData,    m_remoteNodeId)
)

BOOST_FUSION_ADAPT_STRUCT(
  lmp::msg::parse::ConfigNackMsgData,
  (lmp::msg::parse::LocalCCIdData,       m_localCCId)
  (lmp::msg::parse::LocalNodeIdData,     m_localNodeId)
  (lmp::msg::parse::RemoteCCIdData,      m_remoteCCId)
  (lmp::msg::parse::MessageIdAckData,    m_messageId)
  (lmp::msg::parse::RemoteNodeIdData,    m_remoteNodeId)
  (lmp::msg::parse::HelloConfig,         m_helloConfig)
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

namespace lmp
{
  namespace msg
  {
    namespace parse
    {
      namespace fusion = boost::fusion;
      namespace phoenix = boost::phoenix;
      namespace qi = boost::spirit::qi;

      template <typename Iterator>
      struct message_grammar : qi::grammar<Iterator, MsgData()>
      {
        message_grammar() : message_grammar::base_type(message, "message")
        {
          using qi::big_word;
          using qi::big_dword;
          using qi::byte_;
          using qi::repeat;
          using qi::eps;
          using qi::lazy;
          using qi::_a;
          using qi::_1;
          using phoenix::at_c;
          using phoenix::push_back;
          using namespace qi::labels;

          vers_flags =
    			   byte_(0x10)       // version
	    		>> byte_ [_val = _1] // flags
	            >> byte_;            // reserved

          msg_length =
				   big_word [_val = _1] // length
				>> big_word;            // reserved

          control_channel_object_class =
  				byte_(static_cast<std::underlying_type<lmp::obj::ObjectClass>::type>(lmp::obj::ObjectClass::ControlChannelID));

          unknown_ccid_ctype =
				byte_  [ at_c<1>(_val) = _1 ] // c-type
				>> control_channel_object_class
				>> big_word [ at_c<2>(_val) = _1 ] // length
				>> byte_sequence( at_c<2>(_val) - 4 ) [ at_c<3>(_val) = _1 ];

          local_ccid =
				( byte_(0x01) [ at_c<0>(_val) = false ] |
				  byte_(0x81) [ at_c<0>(_val) = true  ] ) // c-type
				>> control_channel_object_class
				>> big_word   // length
		        >> big_dword [ at_c<1>(_val) = _1 ];

          remote_ccid =
				( byte_(0x02) [ at_c<0>(_val) = false ] |
				  byte_(0x82) [ at_c<0>(_val) = true  ] ) // c-type
				>> control_channel_object_class
				>> big_word // length
		        >> big_dword [ at_c<1>(_val) = _1 ];

          control_channel_id %=
      			local_ccid |
  				remote_ccid |
				unknown_ccid_ctype;

          message_id =
				( byte_(0x01) [ at_c<0>(_val) = false ] |
				  byte_(0x81) [ at_c<0>(_val) = true  ] ) // c-type
				>> byte_(static_cast<std::underlying_type<lmp::obj::ObjectClass>::type>(lmp::obj::ObjectClass::MessageID)) // class
				>> big_word // length
				>> big_dword [ at_c<1>(_val) = _1 ];

          message_id_ack =
				( byte_(0x02) [ at_c<0>(_val) = false ] |
				  byte_(0x82) [ at_c<0>(_val) = true  ] ) // c-type
				>> byte_(static_cast<std::underlying_type<lmp::obj::ObjectClass>::type>(lmp::obj::ObjectClass::MessageID)) // class
				>> big_word // length
				>> big_dword [ at_c<1>(_val) = _1 ];

          local_node_id =
				( byte_(0x01) [ at_c<0>(_val) = false ] |
				  byte_(0x81) [ at_c<0>(_val) = true  ] ) // c-type
				>> byte_(static_cast<std::underlying_type<lmp::obj::ObjectClass>::type>(lmp::obj::ObjectClass::NodeID)) // class
				>> big_word // length
				>> big_dword [ at_c<1>(_val) = _1 ];

          remote_node_id =
				( byte_(0x02) [ at_c<0>(_val) = false ] |
				  byte_(0x82) [ at_c<0>(_val) = true  ] ) // c-type
				>> byte_(static_cast<std::underlying_type<lmp::obj::ObjectClass>::type>(lmp::obj::ObjectClass::NodeID)) // class
				>> big_word // length
				>> big_dword [ at_c<1>(_val) = _1 ];

          hello_config =
				( byte_(0x01) [ at_c<0>(_val) = false ] |
				  byte_(0x81) [ at_c<0>(_val) = true  ] ) // c-type
				>> byte_(static_cast<std::underlying_type<lmp::obj::ObjectClass>::type>(lmp::obj::ObjectClass::Config)) // class
				>> big_word // length
				>> big_word [ at_c<1>(_val) = _1 ]
				>> big_word [ at_c<2>(_val) = _1 ];

          byte_sequence =
				( eps(_r1 > 1)
				  >> byte_sequence(_r1 - 1) [ _val = _1 ]
				  >> byte_ [ push_back(_val, _1) ] ) |
				byte_ [ push_back(_val, _1) ];

          unknown_object =
				byte_  [ at_c<1>(_val) = _1 ] // c-type
				>> byte_ [ at_c<2>(_val) = _1 ] // object class
				>> big_word [ at_c<3>(_val) = _1 ] // length
				>> byte_sequence( at_c<3>(_val) - 4 ) [ at_c<4>(_val) = _1 ];
				// >> repeat(4)[byte_] [ at_c<4>(_val) = _1 ]; //[ push_back(at_c<4>(_val), phoenix::static_cast_<lmp::BYTE>(_1)) ]; // [ Sniffer() ];

          objects %=
    			control_channel_id |
				message_id |
				message_id_ack |
				local_node_id |
				remote_node_id |
				hello_config |
				unknown_object;

          config_body %=
   	    		local_ccid
				>> message_id
				>> local_node_id
				>> hello_config;

          config_ack_body %=
   	    		local_ccid
				>> local_node_id
				>> remote_ccid
				>> message_id_ack
				>> remote_node_id;

          config_nack_body %=
   	    		local_ccid
				>> local_node_id
				>> remote_ccid
    			>> message_id_ack
				>> remote_node_id
				>> hello_config;


          object_sequence =
    		    +objects [push_back(at_c<0>(_val), _1)];

          config_msg =
    			byte_(static_cast<std::underlying_type<MsgType>::type>(MsgType::Config))
				>> msg_length [_a = _1]
				>> config_body(_a) [ _val = _1 ]; //[ std::cout << _1 << std::endl ];

          config_ack_msg =
    			byte_(static_cast<std::underlying_type<MsgType>::type>(MsgType::ConfigAck))
				>> msg_length [_a = _1]
			    >> config_ack_body(_a) [ _val = _1 ];

          config_nack_msg =
    			byte_(static_cast<std::underlying_type<MsgType>::type>(MsgType::ConfigNack))
				>> msg_length [_a = _1]
			    >> config_nack_body(_a) [ _val = _1 ];

          unknown_msg %=
    			byte_ // type
				>> msg_length //length
				>> object_sequence(at_c<1>(_val));

          msg_type_and_bodies %=
	    	    config_msg |
	    	    config_ack_msg |
				config_nack_msg |
				unknown_msg;

          message %=
        		vers_flags
				>> msg_type_and_bodies;

          message.name("message");
          msg_type_and_bodies.name("message_type_and_bodies");
          config_msg.name("config_message");
          config_ack_msg.name("config_ack_message");
          config_nack_msg.name("config_nack_message");
          config_body.name("config_message_body");
          config_ack_body.name("config_ack_message_body");
          config_nack_body.name("config_nack_message_body");
          local_ccid.name("local_ccid_object");
          remote_ccid.name("remote_ccid_object");
          message_id.name("message_id_object");
          message_id_ack.name("message_id_ack_object");
          local_node_id.name("local_node_id_object");
          remote_node_id.name("remote_node_id_object");
          hello_config.name("hello_config_object");
          vers_flags.name("procol_version_and_message_flags");
          msg_length.name("message_length");
        }

        qi::rule<Iterator, lmp::BYTE()> vers_flags;
        qi::rule<Iterator, lmp::WORD()> msg_length;
        qi::rule<Iterator> control_channel_object_class;
        qi::rule<Iterator, LocalCCIdData()>             local_ccid;
        qi::rule<Iterator, RemoteCCIdData()>            remote_ccid;
        qi::rule<Iterator, UnknownCCIdCTypeData()>      unknown_ccid_ctype;
        qi::rule<Iterator, ControlChannelIdVariants()>  control_channel_id;
        qi::rule<Iterator, MessageIdData()>     message_id;
        qi::rule<Iterator, MessageIdAckData()>  message_id_ack;
        qi::rule<Iterator, LocalNodeIdData()>   local_node_id;
        qi::rule<Iterator, RemoteNodeIdData()>  remote_node_id;
        qi::rule<Iterator, HelloConfig()>       hello_config;
        qi::rule<Iterator, std::vector<lmp::BYTE>(lmp::WORD)>  byte_sequence;
        qi::rule<Iterator, UnknownObject()>     unknown_object;
        qi::rule<Iterator, ObjectVariants()>    objects;
        qi::rule<Iterator, ConfigMsgData(lmp::WORD)>      config_body;
        qi::rule<Iterator, ConfigAckMsgData(lmp::WORD)>   config_ack_body;
        qi::rule<Iterator, ConfigNackMsgData(lmp::WORD)>  config_nack_body;
        qi::rule<Iterator, ObjectSequence(lmp::WORD)>              object_sequence;
        qi::rule<Iterator, ConfigMsgData(),     qi::locals<lmp::WORD>>  config_msg;
        qi::rule<Iterator, ConfigAckMsgData(),  qi::locals<lmp::WORD>>  config_ack_msg;
        qi::rule<Iterator, ConfigNackMsgData(), qi::locals<lmp::WORD>>  config_nack_msg;
        qi::rule<Iterator, UnknownMessage()>                            unknown_msg;
        qi::rule<Iterator, MsgVariants()>   msg_type_and_bodies;
        qi::rule<Iterator, MsgData()>       message;
      };
    } // namespace parse
  } // namespace msg
} // namespace lmp

#endif /* MSG_PARSE_GRAMMAR_HPP_ */
