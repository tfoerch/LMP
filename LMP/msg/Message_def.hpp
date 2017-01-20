#ifndef LMP_MSG_MESSAGE_DEF_HPP_
#define LMP_MSG_MESSAGE_DEF_HPP_
/*
 * Message_def.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "Message.hpp"
#include "CommonHeader_def.hpp"
#include <boost/spirit/include/qi_binary.hpp>
#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/spirit/include/phoenix_fusion.hpp>
#include <boost/spirit/include/phoenix_stl.hpp>
#include <boost/spirit/include/karma_attr_cast.hpp>
#include <boost/phoenix/object/static_cast.hpp>
#include <boost/fusion/adapted/struct/adapt_struct.hpp>
#include <boost/fusion/include/adapt_struct.hpp>

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
      : message_grammar<Iterator>::base_type(message_rule, "message")
      {
        using qi::byte_;
        using qi::big_word;
        using qi::eps;
        using qi::_a;
        using qi::_1;
        using phoenix::at_c;
        using namespace qi::labels;

        message_rule =
            common_header [ _a = _1 ]
            >> ( ( eps(at_c<1>(_a) == static_cast<std::underlying_type<MsgType>::type>(MsgType::Config) )
                 >> config_msg((at_c<0>(_a) & c_controlChannelDownMask), (at_c<0>(_a) & c_lmpRestartMask), at_c<0>(_a)) ) |
                 ( eps(at_c<1>(_a) == static_cast<std::underlying_type<MsgType>::type>(MsgType::ConfigAck) )
                 >> config_ack_msg((at_c<0>(_a) & c_controlChannelDownMask), (at_c<0>(_a) & c_lmpRestartMask), at_c<0>(_a)) ) |
                 ( eps(at_c<1>(_a) == static_cast<std::underlying_type<MsgType>::type>(MsgType::ConfigNack) )
                 >>  config_nack_msg(_a) ) |
                 ( eps(at_c<1>(_a) == static_cast<std::underlying_type<MsgType>::type>(MsgType::Hello) )
                 >>  hello_msg(_a) ) |
                 unknown_msg(_a) ) [ _val = _1 ]
            ;

        message_rule.name("message");
      }
    } // namespace parse
  } // namespace msg
} // namespace lmp

#endif /* LMP_MSG_MESSAGE_DEF_HPP_ */
