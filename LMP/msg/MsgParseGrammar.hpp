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
#include "CommonHeader.hpp"
#include "Config.hpp"
#include "ConfigAck.hpp"
#include "ConfigNack.hpp"
#include "UnknownMessage.hpp"

namespace lmp
{
  namespace msg
  {
	  namespace parse
	  {
		typedef
		  boost::variant<ConfigMsgData,
						 ConfigAckMsgData,
						 ConfigNackMsgData,
						 UnknownMessage>     MsgVariants;
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
      struct message_grammar : qi::grammar<Iterator, MsgVariants(), qi::locals<lmp::msg::parse::CommonHeaderOutput>>
      {
        message_grammar();

//        lmp::obj::parse::byte_sequence_grammar<Iterator>  byte_sequence;
//        lmp::obj::ccid::parse::local_control_channel_id_grammar<Iterator>    local_ccid;
//        lmp::obj::ccid::parse::remote_control_channel_id_grammar<Iterator>   remote_ccid;
//        lmp::obj::ccid::parse::control_channel_id_ctypes_grammar<Iterator>   control_channel_id_object;
//        lmp::obj::nodeid::parse::local_node_id_grammar<Iterator>             local_node_id;
//        lmp::obj::nodeid::parse::remote_node_id_grammar<Iterator>            remote_node_id;
//        lmp::obj::msgid::parse::message_id_grammar<Iterator>                 message_id;
//        lmp::obj::msgid::parse::message_id_ack_grammar<Iterator>             message_id_ack;
//        lmp::obj::config::parse::hello_config_grammar<Iterator>              hello_config;
//        lmp::obj::hello::parse::hello_grammar<Iterator>                      hello;
//        lmp::obj::parse::object_sequence_grammar<Iterator>                   object_sequence;
        lmp::msg::parse::common_header_grammar<Iterator>                     common_header;
        lmp::msg::parse::config_grammar<Iterator>                            config_msg;
        lmp::msg::parse::config_ack_grammar<Iterator>                        config_ack_msg;
        lmp::msg::parse::config_nack_grammar<Iterator>                       config_nack_msg;
        lmp::msg::parse::unknown_message_grammar<Iterator>                   unknown_msg;
        qi::rule<Iterator, MsgVariants(), qi::locals<lmp::msg::parse::CommonHeaderOutput>>  message;
      };
    } // namespace parse
  } // namespace msg
} // namespace lmp

#endif /* MSG_PARSE_GRAMMAR_HPP_ */
