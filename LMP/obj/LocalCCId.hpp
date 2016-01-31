#ifndef LMP_OBJ_LOCAL_CC_ID_HPP_
#define LMP_OBJ_LOCAL_CC_ID_HPP_
/*
 * LocalCCId.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "obj/ControlChannelIdClass.hpp"
#include "obj/ObjectClassTypeTraits.hpp"
#include "obj/ObjectClassType.hpp"
#include "obj/ControlChannelIdTypeTraits.hpp"
#include "obj/ControlChannelIdIF.hpp"
#include "obj/ControlChannelIdData.hpp"

namespace lmp
{
  namespace obj
  {
    typedef ObjectClassType<ccid::ClassType, ccid::LocalCCId>  LocalCCId;
  } // namespace obj
} // namespace lmp

#endif /* LMP_OBJ_LOCAL_CC_ID_HPP_ */
