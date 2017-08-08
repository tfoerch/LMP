#ifndef LMP_OBJ_MESSAGE_ID_CLASS_DEF_HPP_
#define LMP_OBJ_MESSAGE_ID_CLASS_DEF_HPP_
/*
 * MessageIdClass_def.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "obj/MessageIdClass.hpp"
//#include "obj/ClassTypeAndNegotiableFlag_def.hpp"
#include "obj/ObjectClass.hpp"
#include <boost/spirit/include/qi_binary.hpp>
#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/spirit/include/phoenix_fusion.hpp>
#include <boost/spirit/include/phoenix_stl.hpp>
#include <boost/phoenix/object/static_cast.hpp>

#include <type_traits>

BOOST_FUSION_ADAPT_STRUCT(
  lmp::obj::msgid::MessageIdBody,
  (lmp::DWORD,       m_messageId)
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
        message_id_body_grammar<Iterator>::message_id_body_grammar()
		: message_id_body_grammar::base_type(message_id_body_rule,
				                          "message_id")
        {
     	  using qi::big_dword;
          using qi::_1;
          using phoenix::at_c;
          using namespace qi::labels;

          message_id_body_rule =
        		big_dword [ at_c<0>(_val) = _1 ]
				;

          message_id_body_rule.name("message_id");
        }
	  } // namespace parse
	  namespace generate
      {
        namespace fusion = boost::fusion;
        namespace phoenix = boost::phoenix;
        namespace qi = boost::spirit::qi;

        template <typename OutputIterator>
        message_id_body_grammar<OutputIterator>::message_id_body_grammar()
        : message_id_body_grammar::base_type(message_id_body_rule, "message_id_body")
        {
          using qi::byte_;
          using qi::big_dword;
          using qi::eps;
          using phoenix::at_c;
          using namespace qi::labels;

          message_id_body_rule =
                big_dword [ _1 = at_c<0>(_val) ]
                ;

          message_id_body_rule.name("message_id_body");
        }
      }
    } // namespace msgid
  } // namespace obj
} // namespace lmp

#endif /* LMP_OBJ_MESSAGE_ID_CLASS_DEF_HPP_ */
