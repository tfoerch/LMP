#ifndef LMP_OBJ_OBJECT_CLASS_TYPE_TRAITS_HPP_
#define LMP_OBJ_OBJECT_CLASS_TYPE_TRAITS_HPP_
/*
 * ObjectClassTypeTraits.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include <ObjectClass.hpp>

namespace lmp
{
  namespace obj
  {
    template <typename ClassType>
    struct ObjectClassBaseTraits
	{
	};
    template <typename ClassType, ClassType ctype>
    struct ObjectClassCTypeTraits
	{
	};
  } // namespace obj
} // namespace lmp

#endif /* LMP_OBJ_OBJECTCLASS_HPP_ */
