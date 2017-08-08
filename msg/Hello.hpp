#ifndef LMP_MSG_HELLO_HPP_
#define LMP_MSG_HELLO_HPP_
/*
 * Hello.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "MessageType.hpp"
#include "obj/Hello.hpp"
#include "base/ProtocolTypes.hpp"                  // for DWORD
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/karma.hpp>

namespace lmp
{
  namespace msg
  {
    namespace hello
    {
      struct HelloBody
      {
        lmp::obj::hello::HelloData         m_hello;
      };
      std::ostream& operator<<(
        std::ostream&        os,
        const HelloBody&     helloBody);
      struct IsEqualFtor
      {
        bool operator()(
          const HelloBody&  first,
          const HelloBody&  second) const;
      };
      struct GetLengthFtor
      {
        lmp::WORD operator()(
          const HelloBody&  helloBody) const;
      };
      namespace parse
      {
        namespace qi = boost::spirit::qi;
        template <typename Iterator>
        struct hello_body_grammar : qi::grammar<Iterator, HelloBody(lmp::WORD)>
        {
          hello_body_grammar();

          lmp::obj::parse::object_class_grammar<Iterator,
                                                lmp::obj::hello::ClassType,
                                                lmp::obj::hello::ClassType::Hello>   hello;
          qi::rule<Iterator, HelloBody(lmp::WORD)>                                   hello_body_rule;
        };
      }
      namespace generate
      {
        namespace karma = boost::spirit::karma;
        template <typename OutputIterator>
        struct hello_body_grammar : karma::grammar<OutputIterator, HelloBody()>
        {
          hello_body_grammar();

          lmp::obj::generate::object_class_grammar<OutputIterator,
                                                   lmp::obj::hello::ClassType,
                                                   lmp::obj::hello::ClassType::Hello>   hello;
          karma::rule<OutputIterator, HelloBody()>                                      hello_body_rule;
        };
      }
    }
    template <>
    struct MessageTypeTraits<MsgType::Hello>
    {
      typedef MsgType                message_type;
      typedef hello::HelloBody       data_type;
      typedef hello::IsEqualFtor     equal_ftor_type;
      typedef hello::GetLengthFtor   get_length_ftor_type;
      static const message_type      msg_type_value; // = MsgType::Hello;
    };
    template <typename Iterator>
    struct MessageTypeParseTraits<Iterator, MsgType::Hello>
    {
      typedef hello::parse::hello_body_grammar<Iterator>  grammar_type;
    };
    template <typename OutputIterator>
    struct MessageTypeGenerateTraits<OutputIterator, MsgType::Hello>
    {
      typedef hello::generate::hello_body_grammar<OutputIterator>  grammar_type;
    };
    typedef MessageTypeData<MessageTypeTraits<MsgType::Hello>>  HelloMsg;
  } // namespace msg
} // namespace lmp

#endif /* LMP_MSG_HELLO_HPP_ */
