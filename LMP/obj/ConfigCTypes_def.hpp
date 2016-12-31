#ifndef LMP_OBJ_CONFIG_CTYPES_DEF_HPP_
#define LMP_OBJ_CONFIG_CTYPES_DEF_HPP_
/*
 * ConfigCTypes_def.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "obj/ConfigCTypes.hpp"
#include "obj/ObjectHeader.hpp"
#include "obj/ConfigClass.hpp"
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
	namespace config
	{
      namespace parse
	  {
        namespace fusion = boost::fusion;
        namespace phoenix = boost::phoenix;
        namespace qi = boost::spirit::qi;

        template <typename Iterator>
        config_ctypes_grammar<Iterator>::config_ctypes_grammar()
		: config_ctypes_grammar::base_type(config_ctypes_rule,
				                           "config_ctypes")
        {
     	  using qi::big_word;
          using qi::big_dword;
          using qi::_1;
          using phoenix::at_c;
          using namespace qi::labels;

          config_ctypes_rule %=
        		hello_config |
  				unknown_config_ctype
				;

          config_ctypes_rule.name("config_ctypes");
        }

	  } // namespace parse
	} // namespace config
  } // namespace obj
} // namespace lmp

#endif /* LMP_OBJ_CONFIG_CTYPES_DEF_HPP_ */
