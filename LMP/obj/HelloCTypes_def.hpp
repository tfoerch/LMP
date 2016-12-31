#ifndef LMP_OBJ_HELLO_CTYPES_DEF_HPP_
#define LMP_OBJ_HELLO_CTYPES_DEF_HPP_
/*
 * HelloCTypes_def.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "obj/HelloCTypes.hpp"
#include "obj/ObjectHeader.hpp"
#include "obj/HelloClass.hpp"
#include <boost/spirit/include/qi_binary.hpp>
#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/spirit/include/phoenix_fusion.hpp>
#include <boost/spirit/include/phoenix_stl.hpp>
#include <boost/phoenix/object/static_cast.hpp>


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
        hello_ctypes_grammar<Iterator>::hello_ctypes_grammar()
		: hello_ctypes_grammar::base_type(hello_ctypes_rule,
				                          "hello_ctypes")
        {
     	  using qi::big_word;
          using qi::big_dword;
          using qi::_1;
          using phoenix::at_c;
          using namespace qi::labels;

          hello_ctypes_rule %=
        		hello |
  				unknown_hello_ctype
				;

          hello_ctypes_rule.name("hello_ctypes");
        }

	  } // namespace parse
	} // namespace hello
  } // namespace obj
} // namespace lmp

#endif /* LMP_OBJ_HELLO_CTYPES_DEF_HPP_ */
