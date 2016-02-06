#ifndef LMP_OBJ_OBJECT_CLASS_IF_HPP_
#define LMP_OBJ_OBJECT_CLASS_IF_HPP_
/*
 * ObjectClassIF.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "obj/LMPObjectIF.hpp"
#include "obj/ObjectClassTypeTraits.hpp"

namespace lmp
{
  namespace obj
  {
    template <typename ClassType>
    class ObjectClassIF : public LMPObjectIF
	{
	public:
      typedef ObjectClassBaseTraits<ClassType>  obj_class_traits_type;
      typedef boost::optional<ClassType>        OptClassType;
      virtual ~ObjectClassIF(){}
      inline ClassType getClassType() const { return do_getClassType(); }
      static OptClassType classType_cast(
    	lmp::BYTE                     classTypeByte)
      { return obj_class_traits_type::classType_cast(classTypeByte); }
    private:
      virtual lmp::BYTE do_getClassTypeByteValue() const { return do_getClassType(); }
      virtual const otype::ObjectClass do_getObjectClass() const
      { return obj_class_traits_type::c_object_class; }
      virtual ClassType do_getClassType() const = 0;
	};
  } // namespace obj
} // namespace lmp

#endif /* LMP_OBJ_OBJECT_CLASS_IF_HPP_ */
