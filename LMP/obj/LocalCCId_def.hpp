#ifndef LMP_OBJ_LOCAL_CC_ID_DEF_HPP_
#define LMP_OBJ_LOCAL_CC_ID_DEF_HPP_
/*
 * LocalCCId_def.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "obj/LocalCCId.hpp"
#include "obj/ObjectHeader_def.hpp"
#include "obj/ObjectClass_def.hpp"
#include "obj/ControlChannelIdClass_def.hpp"
#include <boost/spirit/include/qi_binary.hpp>
#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/spirit/include/phoenix_fusion.hpp>
#include <boost/spirit/include/phoenix_stl.hpp>
#include <boost/phoenix/object/static_cast.hpp>

#include <type_traits>

//BOOST_FUSION_ADAPT_STRUCT(
//  lmp::obj::ccid::LocalCCIdData,
//  (bool,            m_negotiable)
//  (lmp::DWORD,      m_CCId)
//)

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
        local_control_channel_id_grammar<Iterator>::local_control_channel_id_grammar()
		: local_control_channel_id_grammar::base_type(local_control_channel_id_rule,
				                                      "local_control_channel_id"),
	      object_header_input(static_cast<std::underlying_type<ObjectClass>::type>(ObjectClass::ControlChannelID),
	    		              static_cast<std::underlying_type<lmp::obj::ccid::ClassType>::type>(lmp::obj::ccid::ClassType::LocalCCId),
							  localCCIdLength)
        {
     	  using qi::big_word;
          using qi::big_dword;
          using qi::_1;
          using phoenix::at_c;
          using namespace qi::labels;

          local_control_channel_id_rule =
        		object_header(phoenix::cref(object_header_input))  [ at_c<0>(_val) = _1 ]
  		        >> control_channel_id_body [ at_c<1>(_val) = _1 ]
				;

          local_control_channel_id_rule.name("local_control_channel_id");
        }

	  } // namespace parse
	  namespace generate
      {
        namespace fusion = boost::fusion;
        namespace phoenix = boost::phoenix;
        namespace qi = boost::spirit::qi;

        template <typename OutputIterator>
        local_control_channel_id_grammar<OutputIterator>::local_control_channel_id_grammar()
		: local_control_channel_id_grammar::base_type(local_control_channel_id_rule, "local_control_channel_id"),
	      object_header_output{static_cast<std::underlying_type<ObjectClass>::type>(ObjectClass::ControlChannelID),
	    		               static_cast<std::underlying_type<lmp::obj::ccid::ClassType>::type>(lmp::obj::ccid::ClassType::LocalCCId),
							   true,
							   localCCIdLength}

        {
          using qi::byte_;
          using qi::big_dword;
          using qi::eps;
          using phoenix::at_c;
          using namespace qi::labels;

          local_control_channel_id_rule =
        		object_header[ at_c<2>(phoenix::ref(object_header_output)) = at_c<0>(_val), _1 = phoenix::cref(object_header_output) ]
  		        << control_channel_id_body [ _1 = at_c<1>(_val) ]
				;

          local_control_channel_id_rule.name("local_control_channel_id");
        }
      }
	} // namespace ccid
  } // namespace obj
} // namespace lmp

#endif /* LMP_OBJ_LOCAL_CC_ID_DEF_HPP_ */
