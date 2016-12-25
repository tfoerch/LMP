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
      struct HelloConfigBody
	  {
  	    lmp::WORD  m_helloIntv;
  	    lmp::WORD  m_helloDeadIntv;
	  };
	  std::ostream& operator<<(
	    std::ostream&            os,
		const HelloConfigBody&   helloConfig);
	}
    template <>
    struct ObjectClassTypeTraits<config::ClassType, config::ClassType::HelloConfig>
    {
      typedef config::ClassType        ctype_type;
      static const ctype_type          ctype = config::ClassType::HelloConfig;
      typedef config::HelloConfigBody  data_type;
    };
	namespace config
	{
	  typedef ObjectClassTypeData<ObjectClassTypeTraits<config::ClassType,
			                                            config::ClassType::HelloConfig>>  HelloConfigData;
	  const lmp::WORD helloConfigLength = objHeaderLength + 4;
	  namespace parse
	  {
	    namespace qi = boost::spirit::qi;
        template <typename Iterator>
        struct hello_config_body_grammar : qi::grammar<Iterator, HelloConfigBody()>
        {
      	  hello_config_body_grammar();

      	  qi::rule<Iterator, HelloConfigBody()>                         hello_config_body_rule;
        };
        template <typename Iterator>
        struct hello_config_grammar : qi::grammar<Iterator, HelloConfigData()>
        {
      	  hello_config_grammar();

      	  lmp::obj::parse::ObjectHeaderFixLengthInput                   object_header_input;
		  lmp::obj::parse::object_header_fix_length_grammar<Iterator>   object_header;
		  lmp::obj::config::parse::hello_config_body_grammar<Iterator>  hello_config_body;
      	  qi::rule<Iterator, HelloConfigData()>                         hello_config_rule;
        };
	  }
	}
  } // namespace obj
} // namespace lmp

#endif /* LMP_OBJ_HELLOCONFIG_HPP_ */
