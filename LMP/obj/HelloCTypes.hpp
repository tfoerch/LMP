#ifndef LMP_OBJ_HELLO_CTYPES_HPP_
#define LMP_OBJ_HELLO_CTYPES_HPP_
/*
 * HelloCTypes.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "obj/Hello.hpp"
#include "obj/UnknownHelloCType.hpp"

#include <boost/variant.hpp>
#include <boost/spirit/include/qi.hpp>

namespace lmp
{
  namespace obj
  {
	namespace hello
	{
	typedef
	  boost::variant<lmp::obj::hello::HelloData,
					 lmp::obj::hello::UnknownHelloCTypeData>   HelloCTypes;
      std::ostream& operator<<(
        std::ostream&                  os,
  	    const HelloCTypes&             helloCTypes);
	  namespace parse
	  {
	    namespace qi = boost::spirit::qi;
	    template <typename Iterator>
        struct hello_ctypes_grammar : qi::grammar<Iterator, HelloCTypes()>
        {
      	  hello_ctypes_grammar();

          lmp::obj::hello::parse::hello_grammar<Iterator>          hello;
          lmp::obj::hello::parse::unknown_hello_grammar<Iterator>  unknown_hello_ctype;
      	  qi::rule<Iterator, HelloCTypes()>                        hello_ctypes_rule;
        };
	  }
	}
  } // namespace obj
} // namespace lmp

#endif /* LMP_OBJ_HELLO_CTYPES_HPP_ */
