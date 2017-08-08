#ifndef LMP_OBJ_MESSAGE_ID_CTYPES_HPP_
#define LMP_OBJ_MESSAGE_ID_CTYPES_HPP_
/*
 * MessageIdCTypes.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "obj/MessageId.hpp"
#include "obj/MessageIdAck.hpp"
#include "obj/UnknownMessageIdCType.hpp"

#include <boost/variant.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/karma.hpp>

namespace lmp
{
  namespace obj
  {
    namespace msgid
    {
      typedef boost::variant<lmp::obj::msgid::MessageIdData,
                             lmp::obj::msgid::MessageIdAckData,
                             lmp::obj::msgid::UnknownMessageIdCTypeData>   MessageIdCTypes;
      lmp::DWORD getLength(
        const MessageIdCTypes&  messageIdCTypes);
      std::ostream& operator<<(
        std::ostream&           os,
        const MessageIdCTypes&  messageIdCTypes);
      namespace parse
      {
        namespace qi = boost::spirit::qi;
        template <typename Iterator>
        struct message_id_ctypes_grammar : qi::grammar<Iterator, MessageIdCTypes()>
        {
          message_id_ctypes_grammar();

          lmp::obj::parse::object_class_grammar<Iterator,
                                                lmp::obj::msgid::ClassType,
                                                lmp::obj::msgid::ClassType::MessageId>           message_id;
          lmp::obj::parse::object_class_grammar<Iterator,
                                                lmp::obj::msgid::ClassType,
                                                lmp::obj::msgid::ClassType::MessageIdAck>        message_id_ack;
          lmp::obj::parse::object_class_unknown_ctype_grammar<Iterator,
                                                              lmp::obj::ObjectClass::MessageID>  unknown_msgid_ctype;
          qi::rule<Iterator, MessageIdCTypes()>                                                  message_id_ctypes_rule;
        };
      }
      namespace generate
      {
        namespace karma = boost::spirit::karma;
        template <typename OutputIterator>
        struct message_id_ctypes_grammar : karma::grammar<OutputIterator, MessageIdCTypes()>
        {
          message_id_ctypes_grammar();

          lmp::obj::generate::object_class_grammar<OutputIterator,
                                                   lmp::obj::msgid::ClassType,
                                                   lmp::obj::msgid::ClassType::MessageId>           message_id;
          lmp::obj::generate::object_class_grammar<OutputIterator,
                                                   lmp::obj::msgid::ClassType,
                                                   lmp::obj::msgid::ClassType::MessageIdAck>        message_id_ack;
          lmp::obj::generate::object_class_unknown_ctype_grammar<OutputIterator,
                                                                 lmp::obj::ObjectClass::MessageID>  unknown_msgid_ctype;
          karma::rule<OutputIterator, MessageIdCTypes()>                                            message_id_ctypes_rule;
        };
      }
    }
  } // namespace obj
} // namespace lmp

#endif /* LMP_OBJ_MESSAGE_ID_CTYPES_HPP_ */
