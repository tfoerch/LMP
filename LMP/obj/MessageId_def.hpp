#ifndef LMP_OBJ_MESSAGE_ID_DEF_HPP_
#define LMP_OBJ_MESSAGE_ID_DEF_HPP_
/*
 * MessageId_def.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "obj/MessageId.hpp"
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
  lmp::obj::msgid::MessageIdData,
  (bool,            m_negotiable)
  (lmp::DWORD,      m_messageId)
)

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
        message_id_grammar<Iterator>::message_id_grammar()
		: message_id_grammar::base_type(message_id_rule,
				                        "message_id"),
	      object_header_input(static_cast<std::underlying_type<ObjectClass>::type>(ObjectClass::MessageID),
	    		              static_cast<std::underlying_type<lmp::obj::msgid::ClassType>::type>(lmp::obj::msgid::ClassType::MessageId),
							  messageIdLength)
        {
     	  using qi::big_word;
          using qi::big_dword;
          using qi::_1;
          using phoenix::at_c;
          using namespace qi::labels;

          message_id_rule =
        		object_header(phoenix::cref(object_header_input))  [ at_c<0>(_val) = _1 ]
  		        >> big_dword [ at_c<1>(_val) = _1 ]
				;

          message_id_rule.name("message_id");
        }

	  } // namespace parse
	} // namespace msgid
  } // namespace obj
} // namespace lmp

#endif /* LMP_OBJ_MESSAGE_ID_DEF_HPP_ */