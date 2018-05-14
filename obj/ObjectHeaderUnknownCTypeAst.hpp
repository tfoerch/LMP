#ifndef LMP_OBJ_OBJECTHEADER_UNKNOWN_CTYPE_AST_HPP_
#define LMP_OBJ_OBJECTHEADER_UNKNOWN_CTYPE_AST_HPP_
/*
 * ObjectHeaderUnknownCTypeAst.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "obj/ObjectClassAst.hpp"

#include <boost/spirit/home/x3/support/ast/position_tagged.hpp>

#include <vector>

namespace lmp
{
  namespace obj
  {
    namespace ast
    {
      namespace x3 = boost::spirit::x3;

      template <typename  ObjClassTraits>
      class ObjectHeaderUnknownCType : x3::position_tagged
      {
      public:
        typedef typename ObjClassTraits::obj_class_type  obj_class_type;
        static const  obj_class_type                     obj_class;
        lmp::BYTE                                        m_class_type;
        bool                                             m_negotiable;
      };
    }
  } // namespace obj
} // namespace lmp

#endif /* LMP_OBJ_OBJECTHEADER_UNKNOWN_CTYPE_AST_HPP_ */
