#ifndef LMP_OBJ_MESSAGE_ID_ACK_PARSER_HPP_
#define LMP_OBJ_MESSAGE_ID_ACK_PARSER_HPP_
/*
 * MessageIdAckParser.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "obj/MessageIdAckAst.hpp"

#include <boost/spirit/home/x3/support/traits/is_variant.hpp>
#include <boost/spirit/home/x3/support/traits/tuple_traits.hpp>
#include <boost/spirit/home/x3/nonterminal/rule.hpp>
//#include <boost/spirit/home/x3.hpp>

namespace lmp
{
  namespace obj
  {
    namespace parser
    {
      namespace x3 = boost::spirit::x3;

      struct message_id_ack_class;
      typedef
        x3::rule<message_id_ack_class, msgid::ast::MessageIdAck>  message_id_ack_type;
      BOOST_SPIRIT_DECLARE(message_id_ack_type);
    }
    parser::message_id_ack_type const& message_id_ack();
  } // namespace obj
} // namespace lmp

#endif /* LMP_OBJ_MESSAGE_ID_ACK_PARSER_HPP_ */
