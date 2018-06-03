#ifndef LMP_OBJ_HELLO_CONFIG_AST_HPP_
#define LMP_OBJ_HELLO_CONFIG_AST_HPP_
/*
 * HelloConfigAst.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "obj/ObjectHeaderAst.hpp"
#include "obj/ObjectClassAst.hpp"
#include "obj/ConfigClassAst.hpp"
#include <boost/spirit/home/x3/support/ast/position_tagged.hpp>


namespace lmp
{
  namespace obj
  {
    template <>
    struct HeaderCTypeTraits<config::ClassType, config::ClassType::HelloConfig>
    {
      typedef typename config::ClassType                ctype_type;
      static const ObjectClass                          obj_class;
      static const ctype_type                           ctype;
      static const lmp::WORD                            length;
    };
    namespace config
    {
      namespace ast
      {
        namespace x3 = boost::spirit::x3;
        struct HelloConfig : x3::position_tagged
        {
          typedef
            lmp::obj::ast::ObjectHeader<HeaderCTypeTraits<config::ClassType,
                                                          config::ClassType::HelloConfig>>  HelloConfigHeaderType;

          HelloConfigHeaderType  m_header;
          lmp::WORD              m_helloIntv;
          lmp::WORD              m_helloDeadIntv;
        };
      }
    }
  } // namespace obj
} // namespace lmp

#endif /* LMP_OBJ_HELLO_CONFIG_AST_HPP_ */
