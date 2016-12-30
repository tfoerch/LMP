#ifndef LMP_OBJ_UNKNOWN_MESSAGE_ID_HPP_
#define LMP_OBJ_UNKNOWN_MESSAGE_ID_HPP_
/*
 * UnknownMessageIdCType.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "obj/ObjectClass.hpp"

namespace lmp
{
  namespace obj
  {
	namespace msgid
	{
	  typedef ObjectClassUnknownCTypeData<ObjectClassTraits<ObjectClass::MessageID>>  UnknownMessageIdCTypeData;
	}
  } // namespace obj
} // namespace lmp

#endif /* LMP_OBJ_UNKNOWN_MESSAGE_ID_HPP_ */
