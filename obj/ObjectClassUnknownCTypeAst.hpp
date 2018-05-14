#ifndef LMP_OBJ_OBJECTCLASS_UNKNOWN_CTYPE_AST_HPP_
#define LMP_OBJ_OBJECTCLASS_UNKNOWN_CTYPE_AST_HPP_
/*
 * ObjectClassUnknownCTypeAst.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "obj/ObjectHeaderUnknownCTypeAst.hpp"

//#include <boost/spirit/home/x3/support/ast/position_tagged.hpp>

#include <vector>

namespace lmp
{
  namespace obj
  {
    namespace ast
    {
      // namespace x3 = boost::spirit::x3;

      typedef std::vector<lmp::BYTE>  ByteSequence;

      template <typename  ObjClassTraits>
      class ObjectClassUnknownCType // : x3::position_tagged
      {
      public:
        ObjectHeaderUnknownCType<ObjClassTraits>  m_header;
        ByteSequence                              m_data;
      };
    }
  } // namespace obj
} // namespace lmp

#endif /* LMP_OBJ_OBJECTCLASS_UNKNOWN_CTYPE_AST_HPP_ */
