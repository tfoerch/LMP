#ifndef LMP_OBJ_HELLO_CLASS_HPP_
#define LMP_OBJ_HELLO_CLASS_HPP_
/*
 * HelloClass.hpp
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
    namespace hello
    {
      enum class ClassType : lmp::BYTE
      {
        Hello = 1
      };
      std::ostream& operator<<(
        std::ostream&     os,
        const ClassType&  cType);
    }
    template <>
    struct ObjectClassTypeConst<hello::ClassType>
    {
      static const ObjectClass  obj_class = ObjectClass::Hello;
    };
  } // namespace obj
} // namespace lmp

#endif /* LMP_OBJ_HELLO_CLASS_HPP_ */
