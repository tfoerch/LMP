#ifndef LMP_OBJ_HELLOCONFIG_DEF_HPP_
#define LMP_OBJ_HELLOCONFIG_DEF_HPP_
/*
 * HelloConfig_def.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "obj/HelloConfig.hpp"
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
  lmp::obj::config::HelloConfigData,
  (bool,            m_negotiable)
  (lmp::WORD,       m_helloIntv)
  (lmp::WORD,       m_helloDeadIntv)
)

namespace lmp
{
  namespace obj
  {
	namespace config
	{
      namespace parse
	  {
        namespace fusion = boost::fusion;
        namespace phoenix = boost::phoenix;
        namespace qi = boost::spirit::qi;

        template <typename Iterator>
        hello_config_grammar<Iterator>::hello_config_grammar()
		: hello_config_grammar::base_type(hello_config_rule,
				                          "hello_config"),
	      object_header_input(static_cast<std::underlying_type<ObjectClass>::type>(ObjectClass::Config),
	    		              static_cast<std::underlying_type<lmp::obj::config::ClassType>::type>(lmp::obj::config::ClassType::HelloConfig),
							  helloConfigLength)
        {
     	  using qi::big_word;
          using qi::big_dword;
          using qi::_1;
          using phoenix::at_c;
          using namespace qi::labels;

          hello_config_rule =
        		object_header(phoenix::cref(object_header_input))  [ at_c<0>(_val) = _1 ]
			    >> big_word [ at_c<1>(_val) = _1 ]
				>> big_word [ at_c<2>(_val) = _1 ]
				;

          hello_config_rule.name("hello_config");
        }

	  } // namespace parse
	} // namespace config
  } // namespace obj
} // namespace lmp

#endif /* LMP_OBJ_HELLOCONFIG_DEF_HPP_ */
