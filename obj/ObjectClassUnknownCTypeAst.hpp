#ifndef LMP_OBJ_OBJECTCLASS_UNKNOWN_CTYPE_AST_HPP_
#define LMP_OBJ_OBJECTCLASS_UNKNOWN_CTYPE_AST_HPP_
/*
 * ObjectClassUnknownCTypeAst.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "obj/ObjectHeaderUnknownCTypeAst.hpp"

#ifdef USE_SPIRIT_X3_PARSER
#include <boost/spirit/home/x3/support/ast/position_tagged.hpp>
#endif /* USE_SPIRIT_X3_PARSER */

#include <vector>

namespace lmp
{
  namespace obj
  {
    namespace ast
    {
#ifdef USE_SPIRIT_X3_PARSER
      namespace x3 = boost::spirit::x3;
#endif /* USE_SPIRIT_X3_PARSER */

      typedef std::vector<lmp::BYTE>  ByteSequence;

      template <typename  ObjClassTraits>
      class ObjectClassUnknownCType
#ifdef USE_SPIRIT_X3_PARSER
          : x3::position_tagged
#endif /* USE_SPIRIT_X3_PARSER */
      {
      public:
        ObjectHeaderUnknownCType<ObjClassTraits>  m_header;
        ByteSequence                              m_data;
      };
    }
    template <typename  ObjClassTraits>
    lmp::DWORD getLength(
      const ast::ObjectClassUnknownCType<ObjClassTraits>&  objectClassUnknownCType)
    {
      return
        ( c_objHeaderLength +
          objectClassUnknownCType.m_data.size() );
    }
    template<typename ObjClassTraits>
    struct GetLengthUnknownCType
    {
      template<typename> struct result { typedef lmp::WORD type; };
      lmp::WORD operator()(
        const ast::ObjectClassUnknownCType<ObjClassTraits>& objClassUnknownCType) const
      {
        return getLength(objClassUnknownCType);
      }
    };

  } // namespace obj
} // namespace lmp

#endif /* LMP_OBJ_OBJECTCLASS_UNKNOWN_CTYPE_AST_HPP_ */
