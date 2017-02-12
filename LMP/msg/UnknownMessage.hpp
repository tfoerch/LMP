#ifndef LMP_MSG_UNKNOWN_MESSAGE_HPP_
#define LMP_MSG_UNKNOWN_MESSAGE_HPP_
/*
 * UnknownMessage.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "obj/ObjectSequence.hpp"
#include "CommonHeader.hpp"
#include "base/ProtocolTypes.hpp"
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/karma.hpp>

namespace lmp
{
  namespace msg
  {
    struct UnknownMessage
    {
      lmp::msg::CommonHeader     m_header;
      lmp::obj::ObjectSequence   m_objects;
    };
    std::ostream& operator<<(
      std::ostream&          os,
      const UnknownMessage&  unknownMessage);
    bool operator==(
      const UnknownMessage&  first,
      const UnknownMessage&  second);
    lmp::DWORD getLength(
      const UnknownMessage&  unknownMessage);
    namespace parse
    {
      namespace qi = boost::spirit::qi;
      template <typename Iterator>
      struct unknown_message_grammar : qi::grammar<Iterator, UnknownMessage(CommonHeader)>
      {
    	unknown_message_grammar();

        lmp::obj::parse::object_sequence_grammar<Iterator>      object_sequence;
    	qi::rule<Iterator, UnknownMessage(CommonHeader)>        unknown_message_rule;
      };
    }
    namespace generate
    {
      namespace karma = boost::spirit::karma;
      template <typename OutputIterator>
      struct unknown_message_grammar : karma::grammar<OutputIterator, UnknownMessage()>
      {
        unknown_message_grammar();

        lmp::msg::generate::common_header_grammar<OutputIterator>    common_header;
        lmp::obj::generate::object_sequence_grammar<OutputIterator>  object_sequence;
        karma::rule<OutputIterator, UnknownMessage()>                unknown_message_rule;
      };
    }
  } // namespace msg
} // namespace lmp

#endif /* LMP_MSG_UNKNOWN_MESSAGE_HPP_ */
