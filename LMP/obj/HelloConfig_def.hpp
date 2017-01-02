#ifndef LMP_OBJ_HELLOCONFIG_DEF_HPP_
#define LMP_OBJ_HELLOCONFIG_DEF_HPP_
/*
 * HelloConfig_def.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "obj/HelloConfig.hpp"
#include "obj/ObjectClass_def.hpp"
#include "obj/ControlChannelIdClass.hpp"
#include <boost/spirit/include/qi_binary.hpp>
#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/spirit/include/phoenix_fusion.hpp>
#include <boost/spirit/include/phoenix_stl.hpp>
#include <boost/phoenix/object/static_cast.hpp>

#include <type_traits>

BOOST_FUSION_ADAPT_STRUCT(
  lmp::obj::config::HelloConfigBody,
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
        hello_config_body_grammar<Iterator>::hello_config_body_grammar()
        : hello_config_body_grammar::base_type(hello_config_body_rule,
                                               "hello_config")
        {
          using qi::big_word;
          using qi::_1;
          using phoenix::at_c;
          using namespace qi::labels;

          hello_config_body_rule =
              big_word [ at_c<0>(_val) = _1 ]
              >> big_word [ at_c<1>(_val) = _1 ]
              ;

          hello_config_body_rule.name("hello_config");
        }
      } // namespace parse
      namespace generate
      {
        namespace fusion = boost::fusion;
        namespace phoenix = boost::phoenix;
        namespace qi = boost::spirit::qi;

        template <typename OutputIterator>
        hello_config_body_grammar<OutputIterator>::hello_config_body_grammar()
        : hello_config_body_grammar::base_type(hello_config_body_rule, "hello_config_body")
        {
          using qi::byte_;
          using qi::big_word;
          using qi::eps;
          using phoenix::at_c;
          using namespace qi::labels;

          hello_config_body_rule =
              big_word [ _1 = at_c<0>(_val) ]
              << big_word [ _1 = at_c<1>(_val) ]
              ;

          hello_config_body_rule.name("hello_config_body");
        }
      }
    } // namespace config
  } // namespace obj
} // namespace lmp

#endif /* LMP_OBJ_HELLOCONFIG_DEF_HPP_ */
