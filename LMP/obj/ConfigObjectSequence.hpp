#ifndef LMP_OBJ_CONFIG_OBJECT_SEQUENCE_HPP_
#define LMP_OBJ_CONFIG_OBJECT_SEQUENCE_HPP_
/*
 * ConfigObjectSequence.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "obj/ConfigCTypes.hpp"

#include <boost/variant.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/karma.hpp>

namespace lmp
{
  namespace obj
  {
    namespace config
    {
      typedef std::vector<lmp::obj::config::ConfigCTypes>  ConfigObjectSequence;
      std::ostream& operator<<(
        std::ostream&                os,
        const ConfigObjectSequence&  configObjectSequence);
      lmp::DWORD getLength(
        const ConfigObjectSequence&  configObjectSequence);
      namespace parse
      {
        namespace qi = boost::spirit::qi;
        template <typename Iterator>
        struct config_object_sequence_grammar : qi::grammar<Iterator,
                                                            ConfigObjectSequence(lmp::WORD),
                                                            qi::locals<lmp::WORD>>
        {
          config_object_sequence_grammar();

          boost::phoenix::function<GetLength>                                  phx_getLength;
          lmp::obj::config::parse::config_ctypes_grammar<Iterator>             config_object;
          qi::rule<Iterator,
                   ConfigObjectSequence(lmp::WORD),
                   qi::locals<lmp::WORD>>                                      config_object_sequence;
          qi::rule<Iterator,
                   void(ConfigObjectSequence&, lmp::WORD),
                   qi::locals<lmp::WORD>>                                      recursive_cfg_obj_seq;
        };
      }
      namespace generate
      {
        namespace karma = boost::spirit::karma;
        template <typename OutputIterator>
        struct config_object_sequence_grammar : karma::grammar<OutputIterator, ConfigObjectSequence()>
        {
          config_object_sequence_grammar();

          lmp::obj::config::generate::config_ctypes_grammar<OutputIterator>     config_object;
          karma::rule<OutputIterator, ConfigObjectSequence()>                   config_object_sequence;
        };
      }
    }
  } // namespace obj
} // namespace lmp

#endif /* LMP_OBJ_CONFIG_OBJECT_SEQUENCE_HPP_ */
