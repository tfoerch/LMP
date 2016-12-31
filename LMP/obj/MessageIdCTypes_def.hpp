#ifndef LMP_OBJ_MESSAGE_ID_CTYPES_DEF_HPP_
#define LMP_OBJ_MESSAGE_ID_CTYPES_DEF_HPP_
/*
 * MessageIdCTypes_def.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "obj/MessageIdCTypes.hpp"
#include "obj/ObjectHeader.hpp"
#include "obj/MessageIdClass.hpp"
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
	namespace msgid
	{
      namespace parse
	  {
        namespace fusion = boost::fusion;
        namespace phoenix = boost::phoenix;
        namespace qi = boost::spirit::qi;

        template <typename Iterator>
        message_id_ctypes_grammar<Iterator>::message_id_ctypes_grammar()
		: message_id_ctypes_grammar::base_type(message_id_ctypes_rule,
				                                      "message_id_ctypes")
        {
     	  using qi::big_word;
          using qi::big_dword;
          using qi::_1;
          using phoenix::at_c;
          using namespace qi::labels;

          message_id_ctypes_rule %=
        		local_msgid |
    			remote_msgid |
  				unknown_msgid_ctype
				;

          message_id_ctypes_rule.name("message_id_ctypes");
        }

	  } // namespace parse
	} // namespace msgid
  } // namespace obj
} // namespace lmp

#endif /* LMP_OBJ_MESSAGE_ID_CTYPES_DEF_HPP_ */
