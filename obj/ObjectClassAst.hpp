#ifndef LMP_OBJ_OBJECTCLASS_AST_HPP_
#define LMP_OBJ_OBJECTCLASS_AST_HPP_
/*
 * ObjectClassAst.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "base/ProtocolTypes.hpp"

namespace lmp
{
  namespace obj
  {
    enum class ObjectClass : lmp::BYTE
    {
      ControlChannelID = 1,
      NodeID,
      LinkID,
      InterfaceID,
      MessageID,
      Config,
      Hello
    };
    template <ObjectClass objClass>
    struct ObjectClassTraits
    {
      typedef ObjectClass            obj_class_type;
      static const  obj_class_type   obj_class = objClass;
    };
    const lmp::WORD  c_objHeaderLength = 4;
    const lmp::BYTE  c_negotiableMask = 0x80;
    const lmp::BYTE  c_classTypeMask = 0x7f;
  } // namespace obj
} // namespace lmp

#endif /* LMP_OBJ_OBJECTCLASS_AST_HPP_ */
