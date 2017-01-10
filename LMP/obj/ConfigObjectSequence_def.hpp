#ifndef LMP_OBJ_CONFIG_OBJECT_SEQUENCE_DEF_HPP_
#define LMP_OBJ_CONFIG_OBJECT_SEQUENCE_DEF_HPP_
/*
 * ConfigObjectSequence_def.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "obj/ConfigObjectSequence.hpp"
#include <boost/bind.hpp>
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
        config_object_sequence_grammar<Iterator>::config_object_sequence_grammar()
        : config_object_sequence_grammar::base_type(config_object_sequence,
                                                    "config_object_sequence")
        {
          using qi::_1;
          using qi::eps;
          using phoenix::at_c;
          using phoenix::push_back;
          using namespace qi::labels;

          config_object_sequence =
              config_object [ push_back(_val, _1), _a = phx_getLength(_1) ]
              >> ( eps(_r1 >= lmp::obj::c_objHeaderLength + _a )
                   >> recursive_cfg_obj_seq(_val, _r1 - _a) ) |
                 eps(true)
              ;

          recursive_cfg_obj_seq =
              config_object [ push_back(_r1, _1), _a = phx_getLength(_1) ]
              >> ( eps(_r2 >= lmp::obj::c_objHeaderLength + _a )
                   >> recursive_cfg_obj_seq(_r1, _r2 - _a) ) |
                 eps(true)
              ;

          config_object_sequence.name("config_object_sequence");
        }
      }
    } // namespace parse
  } // namespace obj
} // namespace lmp

#endif /* LMP_OBJ_CONFIG_OBJECT_SEQUENCE_DEF_HPP_ */
