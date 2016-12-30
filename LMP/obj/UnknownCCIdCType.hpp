#ifndef LMP_OBJ_UNKNOWN_CC_ID_HPP_
#define LMP_OBJ_UNKNOWN_CC_ID_HPP_
/*
 * UnknownCCIdCType.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "obj/ObjectClass.hpp"

namespace lmp
{
  namespace obj
  {
	namespace ccid
	{
	  typedef ObjectClassUnknownCTypeData<ObjectClassTraits<ObjectClass::ControlChannelID>>  UnknownCCIdCTypeData;
	}
  } // namespace obj
} // namespace lmp

#endif /* LMP_OBJ_UNKNOWN_CC_ID_HPP_ */
