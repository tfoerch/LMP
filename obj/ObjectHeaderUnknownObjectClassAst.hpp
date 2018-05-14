#ifndef LMP_OBJ_OBJECTHEADER_UNKNOWN_OBJECT_CLASS_AST_HPP_
#define LMP_OBJ_OBJECTHEADER_UNKNOWN_OBJECT_CLASS_AST_HPP_
/*
 * ObjectHeaderUnknownObjectClassAst.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "base/ProtocolTypes.hpp"

#include <boost/spirit/home/x3/support/ast/position_tagged.hpp>

namespace lmp
{
  namespace obj
  {
    namespace ast
    {
      namespace x3 = boost::spirit::x3;

      struct ObjectHeaderUnknownObjectClass : x3::position_tagged
      {
        lmp::BYTE               m_object_class;
        lmp::BYTE               m_class_type;
        bool                    m_negotiable;
      };
    } // namespace ast
  } // namespace obj
} // namespace lmp

#endif /* LMP_OBJ_OBJECTHEADER_UNKNOWN_OBJECT_CLASS__AST_HPP_ */
