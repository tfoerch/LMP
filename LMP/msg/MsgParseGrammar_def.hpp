#ifndef MSG_PARSE_GRAMMAR_DEF_HPP_
#define MSG_PARSE_GRAMMAR_DEF_HPP_
/*
 * MsgParseGrammar_def.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "msg/MsgParseGrammar.hpp"
#include "msg/Message.hpp"
#include "msg/MsgType.hpp"
#include <boost/spirit/include/qi_binary.hpp>
#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/spirit/include/phoenix_fusion.hpp>
#include <boost/spirit/include/phoenix_stl.hpp>
#include <boost/phoenix/object/static_cast.hpp>

#include <type_traits>

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
      message_grammar<Iterator>::message_grammar()
	  : message_grammar::base_type(message, "message")
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
          vers_flags.name("procol_version_and_message_flags");
          msg_length.name("message_length");
      }
    } // namespace parse
  } // namespace msg
} // namespace lmp

#endif /* MSG_PARSE_GRAMMAR_HPP_ */
