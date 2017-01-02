#ifndef LMP_OBJ_UNKNOWN_CONFIG_HPP_
#define LMP_OBJ_UNKNOWN_CONFIG_HPP_
/*
 * UnknownConfigCType.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "obj/ObjectClass.hpp"

namespace lmp
{
  namespace obj
  {
    namespace config
    {
      typedef ObjectClassUnknownCTypeData<ObjectClassTraits<ObjectClass::Config>>  UnknownConfigCTypeData;
    }
  } // namespace obj
} // namespace lmp

#endif /* LMP_OBJ_UNKNOWN_CONFIG_HPP_ */
