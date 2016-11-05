#ifndef MSG_PARSE_GRAMMAR_HPP_
#define MSG_PARSE_GRAMMAR_HPP_
/*
 * MsgParseGrammar.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include <boost/spirit/include/qi.hpp>
#include "base/ProtocolTypes.hpp"
#include "obj/ObjectClass.hpp"
#include "obj/ByteSequence.hpp"
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
		struct UnknownObject;
		typedef
		  boost::variant<ControlChannelIdVariants,
		                 MessageIdVariants,
						 NodeIdVariants,
						 ConfigVariants,
						 HelloVariants,
						 UnknownObject>          ObjectVariants;
		struct ObjectSequence;
		struct ConfigMsgData;
		struct ConfigAckMsgData;
		struct ConfigNackMsgData;
		struct UnknownMessage;
		typedef
		  boost::variant<ConfigMsgData,
						 ConfigAckMsgData,
						 ConfigNackMsgData,
						 UnknownMessage>     MsgVariants;
		struct MsgData;
	  }
  }
}


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
        message_grammar();

        lmp::obj::parse::byte_sequence_grammar<Iterator>  byte_sequence;
        lmp::obj::ccid::parse::local_control_channel_id_grammar<Iterator>    local_ccid;
        lmp::obj::ccid::parse::remote_control_channel_id_grammar<Iterator>   remote_ccid;
        lmp::obj::ccid::parse::unknown_control_channel_id_grammar<Iterator>  unknown_ccid_ctype;
        lmp::obj::nodeid::parse::local_node_id_grammar<Iterator>             local_node_id;
        lmp::obj::nodeid::parse::remote_node_id_grammar<Iterator>            remote_node_id;
        lmp::obj::nodeid::parse::unknown_node_id_grammar<Iterator>           unknown_node_id_ctype;
        lmp::obj::msgid::parse::message_id_grammar<Iterator>                 message_id;
        lmp::obj::msgid::parse::message_id_ack_grammar<Iterator>             message_id_ack;
        lmp::obj::msgid::parse::unknown_message_id_grammar<Iterator>         unknown_message_id_ctype;
        lmp::obj::config::parse::hello_config_grammar<Iterator>              hello_config;
        lmp::obj::config::parse::unknown_config_grammar<Iterator>            unknown_config_ctype;
        lmp::obj::hello::parse::hello_grammar<Iterator>                      hello;
        lmp::obj::hello::parse::unknown_hello_grammar<Iterator>              unknown_hello_ctype;
        qi::rule<Iterator, lmp::BYTE()> vers_flags;
        qi::rule<Iterator, lmp::WORD()> msg_length;
        qi::rule<Iterator, ControlChannelIdVariants()>  control_channel_id_object;
        qi::rule<Iterator, MessageIdVariants()>          message_id_object;
        qi::rule<Iterator, NodeIdVariants()>          node_id_object;
        qi::rule<Iterator, ConfigVariants()>          config_object;
        qi::rule<Iterator, HelloVariants()>          hello_object;
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
