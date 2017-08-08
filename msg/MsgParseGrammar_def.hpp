#ifndef MSG_PARSE_GRAMMAR_DEF_HPP_
#define MSG_PARSE_GRAMMAR_DEF_HPP_
/*
 * MsgParseGrammar_def.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "msg/MsgParseGrammar.hpp"
#include "CommonHeader_def.hpp"
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
          using boost::spirit::qi::attr;
          using phoenix::at_c;
          using phoenix::push_back;
          using namespace qi::labels;


//          unknown_msg %=
//        		attr(_r1)
//				>> object_sequence(at_c<2>(_r1))
//				;

          message =
        		common_header(CommonHeader::c_supportedVersion << 4) [ _a = _1 ]
				>> ( ( eps(at_c<1>(_a) == static_cast<std::underlying_type<MsgType>::type>(MsgType::Config) )
				       >> config_msg(_a) ) |
				     ( eps(at_c<1>(_a) == static_cast<std::underlying_type<MsgType>::type>(MsgType::ConfigAck) )
					   >> config_ack_msg(_a) ) |
				     ( eps(at_c<1>(_a) == static_cast<std::underlying_type<MsgType>::type>(MsgType::ConfigNack) )
					   >>  config_nack_msg(_a) ) |
				     unknown_msg(_a) ) [ _val = _1 ]
				   ;

          message.name("message");
      }
    } // namespace parse
  } // namespace msg
} // namespace lmp

#endif /* MSG_PARSE_GRAMMAR_HPP_ */
