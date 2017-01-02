#ifndef LMP_OBJ_CONTROL_CHANNEL_ID_CLASS_DEF_HPP_
#define LMP_OBJ_CONTROL_CHANNEL_ID_CLASS_DEF_HPP_
/*
 * ControlChannelIdClass_def.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "obj/ControlChannelIdClass.hpp"
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
  lmp::obj::ccid::ControlChannelIdBody,
  (lmp::DWORD,       m_CCId)
)

namespace lmp
{
  namespace obj
  {
    namespace ccid
    {
      namespace parse
      {
        namespace fusion = boost::fusion;
        namespace phoenix = boost::phoenix;
        namespace qi = boost::spirit::qi;

        template <typename Iterator>
        control_channel_id_body_grammar<Iterator>::control_channel_id_body_grammar()
        : control_channel_id_body_grammar::base_type(control_channel_id_body_rule,
                                                     "control_channel_id")
        {
          using qi::big_dword;
          using qi::_1;
          using phoenix::at_c;
          using namespace qi::labels;

          control_channel_id_body_rule =
              big_dword [ at_c<0>(_val) = _1 ]
              ;

          control_channel_id_body_rule.name("control_channel_id");
        }
      } // namespace parse
      namespace generate
      {
        namespace fusion = boost::fusion;
        namespace phoenix = boost::phoenix;
        namespace qi = boost::spirit::qi;

        template <typename OutputIterator>
        control_channel_id_body_grammar<OutputIterator>::control_channel_id_body_grammar()
		: control_channel_id_body_grammar::base_type(control_channel_id_body_rule, "control_channel_id_body")
        {
          using qi::byte_;
          using qi::big_dword;
          using qi::eps;
          using phoenix::at_c;
          using namespace qi::labels;

          control_channel_id_body_rule =
              big_dword [ _1 = at_c<0>(_val) ]
	      ;

          control_channel_id_body_rule.name("control_channel_id_body");
        }
      }
    } // namespace ccid
  } // namespace obj
} // namespace lmp

#endif /* LMP_OBJ_CONTROL_CHANNEL_ID_CLASS_DEF_HPP_ */
