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

#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/karma.hpp>
#include <iostream>

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
	  namespace parse
	  {
	    namespace qi = boost::spirit::qi;
        template <typename Iterator>
        struct hello_config_body_grammar : qi::grammar<Iterator, HelloConfigBody()>
        {
      	  hello_config_body_grammar();

      	  qi::rule<Iterator, HelloConfigBody()>                         hello_config_body_rule;
        };
	  }
	  namespace generate
	  {
	    namespace karma = boost::spirit::karma;
	    template <typename OutputIterator>
	    struct hello_config_body_grammar : karma::grammar<OutputIterator, HelloConfigBody()>
	    {
	      hello_config_body_grammar();

	      karma::rule<OutputIterator, HelloConfigBody()>                hello_config_body_rule;
	    };
	  }
	}
    template <>
    struct ObjectClassTypeTraits<config::ClassType, config::ClassType::HelloConfig>
    {
      typedef config::ClassType        ctype_type;
      static const ctype_type          ctype = config::ClassType::HelloConfig;
      typedef config::HelloConfigBody  data_type;
    };
    template <typename Iterator>
    struct ObjectClassTypeParseTraits<Iterator, config::ClassType, config::ClassType::HelloConfig>
    {
      typedef config::parse::hello_config_body_grammar<Iterator>  grammar_type;
    };
    template <typename OutputIterator>
    struct ObjectClassTypeGenerateTraits<OutputIterator, config::ClassType, config::ClassType::HelloConfig>
	{
      typedef config::generate::hello_config_body_grammar<OutputIterator>  grammar_type;
	};
	namespace config
	{
	  typedef ObjectClassTypeData<ObjectClassTypeTraits<config::ClassType,
			                                            config::ClassType::HelloConfig>>  HelloConfigData;
	  const lmp::WORD helloConfigLength = objHeaderLength + 4;
	}
  } // namespace obj
} // namespace lmp

#endif /* LMP_OBJ_HELLOCONFIG_HPP_ */
