#ifndef LMP_OBJ_MESSAGE_ID_CLASS_HPP_
#define LMP_OBJ_MESSAGE_ID_CLASS_HPP_
/*
 * MessageIdClass.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "base/ProtocolTypes.hpp"
#include "obj/ObjectClass.hpp"
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/karma.hpp>
#include <iostream>

namespace lmp
{
  namespace obj
  {
    namespace msgid
    {
      enum class ClassType : lmp::BYTE
      {
        MessageId = 1,
        MessageIdAck
      };
      std::ostream& operator<<(
        std::ostream&     os,
        const ClassType&  cType);
      struct MessageIdBody
      {
        lmp::DWORD  m_messageId;
      };
      std::ostream& operator<<(
        std::ostream&         os,
        const MessageIdBody&  messageIdBody);
      struct IsEqualFtor
      {
        bool operator()(
          const MessageIdBody& first,
          const MessageIdBody& second) const;
      };
      struct GetLengthFtor
      {
        lmp::WORD operator()(
          const MessageIdBody&  messageIdBody) const;
        static const lmp::WORD c_length;
      };
      namespace parse
      {
        namespace qi = boost::spirit::qi;
        template <typename Iterator>
        struct message_id_body_grammar : qi::grammar<Iterator, MessageIdBody(lmp::WORD)>
        {
          message_id_body_grammar();

          qi::rule<Iterator, MessageIdBody(lmp::WORD)>  message_id_body_rule;
        };
      }
      namespace generate
      {
        namespace karma = boost::spirit::karma;
        template <typename OutputIterator>
        struct message_id_body_grammar : karma::grammar<OutputIterator, MessageIdBody()>
        {
          message_id_body_grammar();

          karma::rule<OutputIterator, MessageIdBody()>                  message_id_body_rule;
        };
      }
    }
    template <>
    struct ObjectClassTypeConst<msgid::ClassType>
    {
      static const ObjectClass  obj_class = ObjectClass::MessageID;
    };
  } // namespace obj
} // namespace lmp

#endif /* LMP_OBJ_MESSAGE_ID_CLASS_HPP_ */
