#ifndef LMP_MSG_UNKNOWN_MESSAGE_DEF_HPP_
#define LMP_MSG_UNKNOWN_MESSAGE_DEF_HPP_
/*
 * UnknownMessage_def.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "UnknownMessage.hpp"
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


BOOST_FUSION_ADAPT_STRUCT(
  lmp::msg::UnknownMessage,
  (lmp::msg::CommonHeader,    m_header)
  (lmp::obj::ObjectSequence,  m_objects)
)

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
      unknown_message_grammar<Iterator>::unknown_message_grammar()
      : unknown_message_grammar<Iterator>::base_type(unknown_message_rule, "unknown_message")
      {
        using qi::byte_;
        using qi::big_word;
        using qi::_a;
        using qi::_1;
        using qi::attr;
        using phoenix::at_c;
        using namespace qi::labels;

        unknown_message_rule %=
            attr(_r1)
            >> object_sequence(at_c<2>(_r1))
            ;

        unknown_message_rule.name("unknown_message");
      }
    } // namespace parse
  } // namespace msg
} // namespace lmp

#endif /* LMP_MSG_UNKNOWN_MESSAGE_DEF_HPP_ */
