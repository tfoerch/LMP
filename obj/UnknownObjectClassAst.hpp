#ifndef LMP_OBJ_UNKNOWN_OBJECT_CLASS_AST_HPP_
#define LMP_OBJ_UNKNOWN_OBJECT_CLASS_AST_HPP_
/*
 * UnknownObjectClassAst.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "obj/ObjectHeaderUnknownObjectClassAst.hpp"

#include <boost/spirit/home/x3/support/ast/position_tagged.hpp>

#include <vector>

namespace lmp
{
  namespace obj
  {
    namespace ast
    {
      namespace x3 = boost::spirit::x3;

      typedef std::vector<lmp::BYTE>  ByteSequence;

      struct UnknownObjectClass : x3::position_tagged
      {
        ObjectHeaderUnknownObjectClass  m_header;
        ByteSequence                    m_data;
      };
    } // namespace ast
  } // namespace obj
} // namespace lmp

#endif /* LMP_OBJ_UNKNOWN_OBJECT_CLASS__AST_HPP_ */
