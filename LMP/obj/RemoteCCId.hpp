#ifndef LMP_OBJ_REMOTE_CC_ID_HPP_
#define LMP_OBJ_REMOTE_CC_ID_HPP_
/*
 * LocalCCId.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include <ControlChannelIdClass.hpp>
#include <ObjectClassTypeTraits.hpp>
#include <ObjectClassType.hpp>
#include <ControlChannelIdTypeTraits.hpp>
#include <ControlChannelIdIF.hpp>
#include <ControlChannelIdData.hpp>

namespace lmp
{
  namespace obj
  {
    typedef ObjectClassType<ccid::ClassType, ccid::RemoteCCId>  RemoteCCId;
  } // namespace obj
} // namespace lmp

#endif /* LMP_OBJ_REMOTE_CC_ID_HPP_ */
