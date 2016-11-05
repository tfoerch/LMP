#ifndef LMP_OBJ_HELLOCONFIG_HPP_
#define LMP_OBJ_HELLOCONFIG_HPP_
/*
 * HelloConfig.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "obj/ConfigClass.hpp"
#include "obj/ObjectClassTypeTraits.hpp"
#include "obj/ObjectClassType.hpp"
#include "obj/ConfigTypeTraits.hpp"
#include "obj/HelloConfigIF.hpp"
#include "obj/HelloConfigData.hpp"

namespace lmp
{
  namespace obj
  {
    typedef ObjectClassType<config::ClassType, config::ClassType::HelloConfig>  HelloConfig;
	namespace config
	{
	  struct HelloConfigData
	  {
	    bool        m_negotiable;
		lmp::WORD   m_helloIntv;
		lmp::WORD   m_helloDeadIntv;
	  };
	  std::ostream& operator<<(
	    std::ostream&            os,
		const HelloConfigData&   helloConfig);
	  const lmp::WORD helloConfigLength = objHeaderLength + 4;
	  namespace parse
	  {
	    namespace qi = boost::spirit::qi;
        template <typename Iterator>
        struct hello_config_grammar : qi::grammar<Iterator, HelloConfigData()>
        {
      	  hello_config_grammar();

      	  lmp::obj::parse::ObjectHeaderFixLengthInput                   object_header_input;
		  lmp::obj::parse::object_header_fix_length_grammar<Iterator>   object_header;
      	  qi::rule<Iterator, HelloConfigData()>                         hello_config_rule;
        };
	  }
	}
  } // namespace obj
} // namespace lmp

#endif /* LMP_OBJ_HELLOCONFIG_HPP_ */
