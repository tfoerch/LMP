#ifndef LMP_OBJ_HELLO_TYPE_TRAITS_HPP_
#define LMP_OBJ_HELLO_TYPE_TRAITS_HPP_
/*
 * HelloTypeTraits.hpp
 *
 *  Created on: 16.02.2015
 *      Author: tom
 */

#include "obj/HelloClass.hpp"
#include "obj/ObjectClassTypeTraits.hpp"

namespace lmp
{
  namespace obj
  {
    class HelloData;
    class HelloIF;
    template <>
    struct ObjectClassBaseTraits<hello::ClassType>
    {
      static const otype::ObjectClass  c_object_class = otype::Hello;
    };
    template <>
    struct ObjectClassCTypeTraits<hello::ClassType, hello::Hello>
    {
      typedef HelloIF    object_ctype_if_type;
      typedef HelloData  data_type;
      static bool isNegotiable(const data_type&) { return false; }
    };
  } // namespace obj
} // namespace lmp

#endif /* LMP_OBJ_HELLO_TYPE_TRAITS_HPP_ */
