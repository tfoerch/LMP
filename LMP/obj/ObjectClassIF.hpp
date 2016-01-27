#ifndef LMP_OBJ_OBJECT_CLASS_IF_HPP_
#define LMP_OBJ_OBJECT_CLASS_IF_HPP_
/*
 * ObjectClassIF.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include <LMPObjectIF.hpp>
#include <ObjectClassTypeTraits.hpp>

namespace lmp
{
  namespace obj
  {
    template <typename ClassType>
    class ObjectClassIF : public LMPObjectIF
	{
	public:
      typedef ObjectClassBaseTraits<ClassType>  obj_class_traits_type;
      virtual ~ObjectClassIF(){}
      inline ClassType getClassType() const { return do_getClassType(); }
    private:
      virtual lmp::BYTE do_getClassTypeByteValue() const { return do_getClassType(); }
      virtual bool do_isNegotiable() const { return true; }
      virtual const otype::ObjectClass do_getObjectClass() const
      { return obj_class_traits_type::c_object_class; }
      virtual ClassType do_getClassType() const = 0;
	};
  } // namespace obj
} // namespace lmp

#endif /* LMP_OBJ_OBJECT_CLASS_IF_HPP_ */