#ifndef LMP_OBJ_HELLOCONFIG_HPP_
#define LMP_OBJ_HELLOCONFIG_HPP_
/*
 * HelloConfig.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "obj/ConfigClass.hpp"

#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/karma.hpp>

#include <iostream>

namespace lmp
{
  namespace obj
  {
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
      struct IsEqualFtor
      {
        bool operator()(
          const HelloConfigBody& first,
          const HelloConfigBody& second) const;
      };
      struct GetLengthFtor
      {
        lmp::WORD operator()(
          const HelloConfigBody&  helloConfig) const;
        static const lmp::WORD c_length;
      };
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
      typedef typename config::ClassType        ctype_type;
      typedef typename config::HelloConfigBody  data_type;
      typedef typename config::IsEqualFtor      equal_ftor_type;
      typedef typename config::GetLengthFtor    get_length_ftor_type;
      static const ctype_type                   ctype = config::ClassType::HelloConfig;
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
      const lmp::WORD helloConfigLength = c_objHeaderLength + 4;
    }
  } // namespace obj
} // namespace lmp

#endif /* LMP_OBJ_HELLOCONFIG_HPP_ */
