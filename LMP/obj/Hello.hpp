#ifndef LMP_OBJ_HELLO_HPP_
#define LMP_OBJ_HELLO_HPP_
/*
 * Hello.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "obj/HelloClass.hpp"
#include "obj/ObjectClassTypeTraits.hpp"
#include "obj/ObjectClassType.hpp"
#include "obj/HelloTypeTraits.hpp"
#include "obj/HelloIF.hpp"
#include "obj/HelloData.hpp"

namespace lmp
{
  namespace obj
  {
    typedef ObjectClassType<hello::ClassType, hello::ClassType::Hello>  Hello;
	namespace hello
	{
	  struct HelloData
	  {
	    bool         m_negotiable;
		lmp::DWORD   m_txSeqNum;
		lmp::DWORD   m_rcvSeqNum;
	  };
	  std::ostream& operator<<(
	    std::ostream&            os,
		const HelloData&         hello);
	  const lmp::WORD helloLength = objHeaderLength + 4 + 4;
	  namespace parse
	  {
	    namespace qi = boost::spirit::qi;
        template <typename Iterator>
        struct hello_grammar : qi::grammar<Iterator, HelloData()>
        {
      	  hello_grammar();

      	  lmp::obj::parse::ObjectHeaderFixLengthInput                   object_header_input;
		  lmp::obj::parse::object_header_fix_length_grammar<Iterator>   object_header;
      	  qi::rule<Iterator, HelloData()>                               hello_rule;
        };
	  }
	}
  } // namespace obj
} // namespace lmp

#endif /* LMP_OBJ_HELLO_HPP_ */
