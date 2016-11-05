#ifndef LMP_OBJ_HELLO_DEF_HPP_
#define LMP_OBJ_HELLO_DEF_HPP_
/*
 * Hello_def.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "obj/Hello.hpp"
#include "obj/ObjectHeader_def.hpp"
#include "obj/ControlChannelIdClass.hpp"
#include <boost/spirit/include/qi_binary.hpp>
#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/spirit/include/phoenix_fusion.hpp>
#include <boost/spirit/include/phoenix_stl.hpp>
#include <boost/phoenix/object/static_cast.hpp>

#include <type_traits>

BOOST_FUSION_ADAPT_STRUCT(
  lmp::obj::hello::HelloData,
  (bool,            m_negotiable)
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
        hello_grammar<Iterator>::hello_grammar()
		: hello_grammar::base_type(hello_rule,
				                   "hello"),
	      object_header_input(static_cast<std::underlying_type<ObjectClass>::type>(ObjectClass::Hello),
	    		              static_cast<std::underlying_type<lmp::obj::hello::ClassType>::type>(lmp::obj::hello::ClassType::Hello),
							  helloLength)
        {
     	  using qi::big_word;
     	  using qi::big_dword;
          using qi::_1;
          using phoenix::at_c;
          using namespace qi::labels;

          hello_rule =
        		object_header(phoenix::cref(object_header_input))  [ at_c<0>(_val) = _1 ]
				>> big_dword [ at_c<1>(_val) = _1 ]
				>> big_dword [ at_c<2>(_val) = _1 ]
				;

          hello_rule.name("hello");
        }

	  } // namespace parse
	} // namespace hello
  } // namespace obj
} // namespace lmp

#endif /* LMP_OBJ_HELLO_DEF_HPP_ */
