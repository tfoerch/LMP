#ifndef LMP_OBJ_OBJECTHEADER_AST_HPP_
#define LMP_OBJ_OBJECTHEADER_AST_HPP_
/*
 * ObjectHeaderAst.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "base/ProtocolTypes.hpp"
#include "obj/ObjectClassAst.hpp"

#include <boost/spirit/home/x3/support/ast/position_tagged.hpp>

namespace lmp
{
  namespace obj
  {
    template <typename ClassType>
    struct HeaderObjClassTypeTraits
    {
      static const ObjectClass  obj_class;
    };
    // specializations should provide a typedef for member data_type
    template <typename ClassType, ClassType ctype>
    struct HeaderCTypeTraits
    {
    };
    namespace ast
    {
      namespace x3 = boost::spirit::x3;

      // instantiate following with ObjectHeader<HeaderTypeTraits<ClassType, ctype>>
      template <typename   HeaderTypeTraits>
      struct ObjectHeader : x3::position_tagged
      {
        typedef typename HeaderTypeTraits::ctype_type      ctype_type;
        static const ObjectClass                           obj_class;
        static const ctype_type                            ctype;
        bool                                               m_negotiable;
      };
    }
  } // namespace obj
} // namespace lmp

#endif /* LMP_OBJ_OBJECTHEADER_AST_HPP_ */
