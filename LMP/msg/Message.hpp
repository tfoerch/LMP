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
#include "UnknownMessage.hpp"

#include <boost/variant.hpp>
#include <boost/spirit/include/qi.hpp>
#include <iostream>

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
					   UnknownMessage>     Message;
	  std::ostream& operator<<(
		std::ostream&    os,
		const Message&   message);
      namespace fusion = boost::fusion;
      namespace phoenix = boost::phoenix;
      namespace qi = boost::spirit::qi;

      template <typename Iterator>
      struct message_grammar : qi::grammar<Iterator, Message(), qi::locals<lmp::msg::parse::CommonHeaderOutput>>
      {
        message_grammar();

        lmp::msg::parse::common_header_grammar<Iterator>                                common_header;
        lmp::msg::parse::config_grammar<Iterator>                                       config_msg;
        lmp::msg::parse::config_ack_grammar<Iterator>                                   config_ack_msg;
        lmp::msg::parse::config_nack_grammar<Iterator>                                  config_nack_msg;
        lmp::msg::parse::unknown_message_grammar<Iterator>                              unknown_msg;
        qi::rule<Iterator, Message(), qi::locals<lmp::msg::parse::CommonHeaderOutput>>  message_rule;
      };
	}
  } // namespace msg
} // namespace lmp

#endif /* LMP_MSG_MESSAGE_HPP_ */
