#ifndef LMP_OBJ_CONFIG_CLASS_HPP_
#define LMP_OBJ_CONFIG_CLASS_HPP_
/*
 * ConfigClass.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "base/ProtocolTypes.hpp"
#include "obj/ObjectClass.hpp"

#include <iostream>

namespace lmp
{
  namespace obj
  {
    namespace config
    {
      enum class ClassType : lmp::BYTE
      {
        HelloConfig = 1
      };
      std::ostream& operator<<(
        std::ostream&     os,
        const ClassType&  cType);
    }
    template <>
    struct ObjectClassTypeConst<config::ClassType>
    {
      static const ObjectClass  obj_class = ObjectClass::Config;
    };
  } // namespace obj
} // namespace lmp

#endif /* LMP_OBJ_CONFIG_CLASS_HPP_ */
