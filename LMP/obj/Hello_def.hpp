#ifndef LMP_OBJ_HELLO_DEF_HPP_
#define LMP_OBJ_HELLO_DEF_HPP_
/*
 * Hello_def.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "obj/Hello.hpp"
#include "obj/ObjectHeader.hpp"
#include "obj/ObjectClass_def.hpp"
#include "obj/ControlChannelIdClass.hpp"
#include <boost/spirit/include/qi_binary.hpp>
#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/spirit/include/phoenix_fusion.hpp>
#include <boost/spirit/include/phoenix_stl.hpp>
#include <boost/phoenix/object/static_cast.hpp>

#include <type_traits>

BOOST_FUSION_ADAPT_STRUCT(
  lmp::obj::hello::HelloBody,
  (lmp::DWORD,      m_txSeqNum)
  (lmp::DWORD,      m_rcvSeqNum)
)

namespace lmp
{
  namespace obj
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
		: hello_body_grammar::base_type(hello_body_rule,
				                   "hello_body")
        {
     	  using qi::big_dword;
          using qi::_1;
          using phoenix::at_c;
          using namespace qi::labels;

          hello_body_rule =
				big_dword [ at_c<0>(_val) = _1 ]
				>> big_dword [ at_c<1>(_val) = _1 ]
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
          using qi::byte_;
          using qi::big_dword;
          using qi::eps;
          using phoenix::at_c;
          using namespace qi::labels;

          hello_body_rule =
                big_dword [ _1 = at_c<0>(_val) ]
			    << big_dword [ _1 = at_c<1>(_val) ]
				;

          hello_body_rule.name("hello_body");
        }
      }
	} // namespace hello
  } // namespace obj
} // namespace lmp

#endif /* LMP_OBJ_HELLO_DEF_HPP_ */
