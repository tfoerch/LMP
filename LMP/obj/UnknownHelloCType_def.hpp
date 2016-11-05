#ifndef LMP_OBJ_UNKNOWN_HELLO_DEF_HPP_
#define LMP_OBJ_UNKNOWN_HELLO_DEF_HPP_
/*
 * UnknownHelloCType_def.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "obj/UnknownHelloCType.hpp"
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
  lmp::obj::hello::UnknownHelloCTypeData,
  (lmp::obj::parse::ObjectHeaderUnknownCTypeOutput,  m_header)
  (lmp::obj::ByteSequence,                           m_data)
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
        unknown_hello_grammar<Iterator>::unknown_hello_grammar()
		: unknown_hello_grammar::base_type(unknown_hello_rule,
				                                        "unknown_hello")
        {
     	  using qi::big_word;
          using qi::big_dword;
          using qi::_1;
          using phoenix::at_c;
          using namespace qi::labels;

          unknown_hello_rule =
        		object_header(static_cast<std::underlying_type<ObjectClass>::type>(ObjectClass::Hello)) [ at_c<0>(_val) = _1 ]
  		        >> byte_sequence( at_c<2>(at_c<0>(_val)) - 4 ) [ at_c<1>(_val) = _1 ]
				;

          unknown_hello_rule.name("unknown_hello");
        }

	  } // namespace parse
	} // namespace hello
  } // namespace obj
} // namespace lmp

#endif /* LMP_OBJ_UNKNOWN_HELLO_DEF_HPP_ */
