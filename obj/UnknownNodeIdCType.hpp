#ifndef LMP_OBJ_UNKNOWN_NODE_ID_HPP_
#define LMP_OBJ_UNKNOWN_NODE_ID_HPP_
/*
 * UnknownNodeIdCType.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "obj/ObjectClassUnknownCType.hpp"

namespace lmp
{
  namespace obj
  {
    namespace nodeid
    {
      typedef ObjectClassUnknownCTypeData<ObjectClassTraits<ObjectClass::NodeID>>  UnknownNodeIdCTypeData;
    }
  } // namespace obj
} // namespace lmp

#endif /* LMP_OBJ_UNKNOWN_NODE_ID_HPP_ */
