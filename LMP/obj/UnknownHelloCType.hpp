#ifndef LMP_OBJ_UNKNOWN_HELLO_HPP_
#define LMP_OBJ_UNKNOWN_HELLO_HPP_
/*
 * UnknownHelloCType.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "obj/ObjectClass.hpp"

namespace lmp
{
  namespace obj
  {
	namespace hello
	{
	  typedef ObjectClassUnknownCTypeData<ObjectClassTraits<ObjectClass::Hello>>  UnknownHelloCTypeData;
	}
  } // namespace obj
} // namespace lmp

#endif /* LMP_OBJ_UNKNOWN_HELLO_HPP_ */
