#ifndef LMP_OBJ_CONFIG_CTYPES_HPP_
#define LMP_OBJ_CONFIG_CTYPES_HPP_
/*
 * ConfigCTypes.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "obj/HelloConfig.hpp"
#include "obj/UnknownConfigCType.hpp"

#include <boost/variant.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/karma.hpp>

namespace lmp
{
  namespace obj
  {
    namespace config
    {
      typedef boost::variant<lmp::obj::config::HelloConfigData,
                             lmp::obj::config::UnknownConfigCTypeData>   ConfigCTypes;
      std::ostream& operator<<(
        std::ostream&        os,
        const ConfigCTypes&  configCType);
      lmp::DWORD getLength(
        const ConfigCTypes&  configCType);
      struct GetLength
      {
        template<typename> struct result { typedef lmp::WORD type; };
        template<typename ConfigCTypes>
        lmp::WORD operator()(
          const ConfigCTypes& configCType) const
        {
          return getLength(configCType);
        }
      };
      namespace parse
      {
        namespace qi = boost::spirit::qi;
        template <typename Iterator>
        struct config_ctypes_grammar : qi::grammar<Iterator, ConfigCTypes()>
        {
          config_ctypes_grammar();

          lmp::obj::parse::object_class_grammar<Iterator,
                                                lmp::obj::config::ClassType,
                                                lmp::obj::config::ClassType::HelloConfig>     hello_config;
          lmp::obj::parse::object_class_unknown_ctype_grammar<Iterator,
                                                              lmp::obj::ObjectClass::Config>  unknown_config_ctype;
          qi::rule<Iterator, ConfigCTypes()>                                                  config_ctypes_rule;
        };
      }
      namespace generate
      {
        namespace karma = boost::spirit::karma;
        template <typename OutputIterator>
        struct config_ctypes_grammar : karma::grammar<OutputIterator, ConfigCTypes()>
        {
          config_ctypes_grammar();

          lmp::obj::generate::object_class_grammar<OutputIterator,
                                                   lmp::obj::config::ClassType,
                                                   lmp::obj::config::ClassType::HelloConfig>     hello_config;
          lmp::obj::generate::object_class_unknown_ctype_grammar<OutputIterator,
                                                                 lmp::obj::ObjectClass::Config>  unknown_config_ctype;
          karma::rule<OutputIterator, ConfigCTypes()>                                            config_ctypes_rule;
        };
      }
    }
  } // namespace obj
} // namespace lmp

#endif /* LMP_OBJ_CONFIG_CTYPES_HPP_ */
