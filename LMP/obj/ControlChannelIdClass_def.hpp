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

#if 0
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
	    local_control_channel_id_ctype_grammar<Iterator>::local_control_channel_id_ctype_grammar()
		: local_control_channel_id_ctype_grammar::base_type(local_control_channel_id_ctype_rule, "local_control_channel_id_ctype")
	    {
	    	using qi::byte_;
	        using phoenix::at_c;
	    	using namespace qi::labels;

	    	local_control_channel_id_ctype_rule =
	    			( byte_(static_cast<std::underlying_type<ClassType>::type>(ClassType::LocalCCId))
	    			  [ at_c<1>(_val) = false ] |
	    			  byte_(static_cast<std::underlying_type<ClassType>::type>(ClassType::LocalCCId) +
	    				lmp::obj::parse::negotiableFlagValue)
					  [ at_c<1>(_val) = true  ] ) // c-type
					[ at_c<0>(_val) = ClassType::LocalCCId ]
					;

	    	local_control_channel_id_ctype_rule.name("local_control_channel_id_ctype");
	    }

	    template <typename Iterator>
	    remote_control_channel_id_ctype_grammar<Iterator>::remote_control_channel_id_ctype_grammar()
		: remote_control_channel_id_ctype_grammar::base_type(remote_control_channel_id_ctype_rule, "remote_control_channel_id_ctype")
	    {
	    	using qi::byte_;
	        using phoenix::at_c;
	    	using namespace qi::labels;

	    	remote_control_channel_id_ctype_rule =
	    			( byte_(static_cast<std::underlying_type<ClassType>::type>(ClassType::RemoteCCId))
	    			  [ at_c<1>(_val) = false ] |
	    			  byte_(static_cast<std::underlying_type<ClassType>::type>(ClassType::RemoteCCId) +
	    				lmp::obj::parse::negotiableFlagValue)
					  [ at_c<1>(_val) = true  ] ) // c-type
					[ at_c<0>(_val) = ClassType::RemoteCCId ]
					;

	    	remote_control_channel_id_ctype_rule.name("remote_control_channel_id_ctype");
	    }
	  } // namespace parse
    } // namespace ccid
  } // namespace obj
} // namespace lmp
#endif

#endif /* LMP_OBJ_CONTROL_CHANNEL_ID_CLASS_DEF_HPP_ */
