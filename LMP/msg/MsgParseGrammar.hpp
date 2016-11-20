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
#include "obj/LocalCCId.hpp"
#include "obj/RemoteCCId.hpp"
#include "obj/LocalNodeId.hpp"
#include "obj/RemoteNodeId.hpp"
#include "obj/MessageId.hpp"
#include "obj/MessageIdAck.hpp"
#include "obj/HelloConfig.hpp"
#include "obj/Hello.hpp"
#include "obj/ObjectSequence.hpp"

namespace lmp
{
  namespace msg
  {
	  namespace parse
	  {
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
        lmp::obj::ccid::parse::control_channel_id_ctypes_grammar<Iterator>   control_channel_id_object;
        lmp::obj::nodeid::parse::local_node_id_grammar<Iterator>             local_node_id;
        lmp::obj::nodeid::parse::remote_node_id_grammar<Iterator>            remote_node_id;
        lmp::obj::msgid::parse::message_id_grammar<Iterator>                 message_id;
        lmp::obj::msgid::parse::message_id_ack_grammar<Iterator>             message_id_ack;
        lmp::obj::config::parse::hello_config_grammar<Iterator>              hello_config;
        lmp::obj::hello::parse::hello_grammar<Iterator>                      hello;
        lmp::obj::parse::object_sequence_grammar<Iterator>                   object_sequence;
        qi::rule<Iterator, lmp::BYTE()> vers_flags;
        qi::rule<Iterator, lmp::WORD()> msg_length;
        qi::rule<Iterator, ConfigMsgData(lmp::WORD)>      config_body;
        qi::rule<Iterator, ConfigAckMsgData(lmp::WORD)>   config_ack_body;
        qi::rule<Iterator, ConfigNackMsgData(lmp::WORD)>  config_nack_body;
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
