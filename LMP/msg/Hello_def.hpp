#ifndef LMP_MSG_HELLO_DEF_HPP_
#define LMP_MSG_HELLO_DEF_HPP_
/*
 * Hello_def.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "Hello.hpp"
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
  lmp::msg::hello::HelloBody,
  (lmp::obj::hello::HelloData,         m_hello)
)

namespace lmp
{
  namespace msg
  {
    namespace hello
    {
      namespace parse
      {
        namespace fusion = boost::fusion;
        namespace phoenix = boost::phoenix;
        namespace qi = boost::spirit::qi;

        template <typename Iterator>
        hello_body_grammar<Iterator>::hello_body_grammar()
        : hello_body_grammar<Iterator>::base_type(hello_body_rule, "hello_body")
        {
          using qi::byte_;
          using qi::big_word;
          using qi::_a;
          using qi::_1;
          using qi::attr;
          using phoenix::at_c;
          using namespace qi::labels;

          hello_body_rule %=
              hello
              ;

          hello_body_rule.name("hello_body");
        }
      } // namespace parse
      namespace generate
      {
        namespace fusion = boost::fusion;
        namespace phoenix = boost::phoenix;
        namespace qi = boost::spirit::qi;

        template <typename OutputIterator>
        hello_body_grammar<OutputIterator>::hello_body_grammar()
        : hello_body_grammar::base_type(hello_body_rule, "hello_body")
        {
          using phoenix::at_c;
          using qi::byte_;
          using qi::big_word;
          using qi::attr;
          using namespace qi::labels;

          hello_body_rule %=
              hello
              ;

          hello_body_rule.name("hello_body");
        }
      } // namespace generate
    }
  } // namespace msg
} // namespace lmp

#endif /* LMP_MSG_HELLO_DEF_HPP_ */
