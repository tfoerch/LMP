#ifndef LMP_OBJ_HELLO_AST_HPP_
#define LMP_OBJ_HELLO_AST_HPP_
/*
 * HelloAst.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "obj/ObjectHeaderAst.hpp"
#include "obj/ObjectClassAst.hpp"
#include "obj/HelloClassAst.hpp"
#include <boost/spirit/home/x3/support/ast/position_tagged.hpp>


namespace lmp
{
  namespace obj
  {
    template <>
    struct HeaderCTypeTraits<hello::ClassType, hello::ClassType::Hello>
    {
      typedef typename hello::ClassType                ctype_type;
      static const ObjectClass                         obj_class;
      static const ctype_type                          ctype;
      static const lmp::WORD                           length;
    };
    namespace hello
    {
      namespace ast
      {
        namespace x3 = boost::spirit::x3;
        struct Hello : x3::position_tagged
        {
          typedef
            lmp::obj::ast::ObjectHeader<HeaderCTypeTraits<hello::ClassType,
                                                          hello::ClassType::Hello>>  HelloHeaderType;

          HelloHeaderType  m_header;
          lmp::DWORD       m_txSeqNum;
          lmp::DWORD       m_rcvSeqNum;
        };
      }
    }
  } // namespace obj
} // namespace lmp

#endif /* LMP_OBJ_HELLO_AST_HPP_ */
