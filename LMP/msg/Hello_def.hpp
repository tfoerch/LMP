#ifndef LMP_MSG_HELLO_DEF_HPP_
#define LMP_MSG_HELLO_DEF_HPP_
/*
 * Hello_def.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "Hello.hpp"
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
  lmp::msg::HelloMsg,
  (lmp::BYTE,                          m_flags)
  (lmp::obj::hello::HelloData,         m_hello)
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
      hello_grammar<Iterator>::hello_grammar()
	  : hello_grammar<Iterator>::base_type(hello_rule, "hello")
	  {
        using qi::byte_;
        using qi::big_word;
        using qi::_a;
        using qi::_1;
        using qi::attr;
        using phoenix::at_c;
        using namespace qi::labels;

        hello_rule %=
        		attr(at_c<0>(_r1))
 	    		>> hello
				;

        hello_rule.name("hello");
	  }
	} // namespace parse
  } // namespace msg
} // namespace lmp

#endif /* LMP_MSG_HELLO_DEF_HPP_ */
