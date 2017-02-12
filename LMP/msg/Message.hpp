#ifndef LMP_MSG_MESSAGE_HPP_
#define LMP_MSG_MESSAGE_HPP_
/*
 * Message.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "base/ProtocolTypes.hpp"
#include "CommonHeader.hpp"
#include "Config.hpp"
#include "ConfigAck.hpp"
#include "ConfigNack.hpp"
#include "Hello.hpp"
#include "UnknownMessage.hpp"

#include <boost/variant.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/karma.hpp>
#include <iostream>

namespace lmp
{
  namespace msg
  {
    typedef
      boost::variant<ConfigMsg,
                     ConfigAckMsg,
                     ConfigNackMsg,
                     HelloMsg,
                     UnknownMessage>     Message;
    std::ostream& operator<<(
      std::ostream&    os,
      const Message&   message);
    lmp::DWORD getLength(
      const Message&  message);
    namespace parse
    {
      namespace fusion = boost::fusion;
      namespace phoenix = boost::phoenix;
      namespace qi = boost::spirit::qi;

      template <typename Iterator>
      struct message_grammar : qi::grammar<Iterator, Message(), qi::locals<lmp::msg::CommonHeader>>
      {
        message_grammar();

        lmp::msg::parse::common_header_grammar<Iterator>                      common_header;
        lmp::msg::parse::message_type_grammar<Iterator,
                                              lmp::msg::MsgType::Config>      config_msg;
        lmp::msg::parse::message_type_grammar<Iterator,
                                              lmp::msg::MsgType::ConfigAck>   config_ack_msg;
        lmp::msg::parse::message_type_grammar<Iterator,
                                              lmp::msg::MsgType::ConfigNack>  config_nack_msg;
        lmp::msg::parse::message_type_grammar<Iterator,
                                              lmp::msg::MsgType::Hello>       hello_msg;
        lmp::msg::parse::unknown_message_grammar<Iterator>                    unknown_msg;
        qi::rule<Iterator, Message(), qi::locals<lmp::msg::CommonHeader>>     message_rule;
      };
    }
    namespace generate
    {
      namespace karma = boost::spirit::karma;
      template <typename OutputIterator>
      struct message_grammar : karma::grammar<OutputIterator, Message()>
      {
        message_grammar();

        lmp::msg::generate::message_type_grammar<OutputIterator,
                                                 lmp::msg::MsgType::Config>      config_msg;
        lmp::msg::generate::message_type_grammar<OutputIterator,
                                                 lmp::msg::MsgType::ConfigAck>   config_ack_msg;
        lmp::msg::generate::message_type_grammar<OutputIterator,
                                                 lmp::msg::MsgType::ConfigNack>  config_nack_msg;
        lmp::msg::generate::message_type_grammar<OutputIterator,
                                                 lmp::msg::MsgType::Hello>       hello_msg;
        lmp::msg::generate::unknown_message_grammar<OutputIterator>              unknown_msg;
        karma::rule<OutputIterator, Message()>                                   message_rule;
      };
    }
  } // namespace msg
} // namespace lmp

#endif /* LMP_MSG_MESSAGE_HPP_ */
