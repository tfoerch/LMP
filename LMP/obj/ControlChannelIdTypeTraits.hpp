#ifndef LMP_OBJ_CONTROL_CHANNEL_ID_TYPE_TRAITS_HPP_
#define LMP_OBJ_CONTROL_CHANNEL_ID_TYPE_TRAITS_HPP_
/*
 * ControlChannelIdTypeTraits.hpp
 *
 *  Created on: 16.02.2015
 *      Author: tom
 */

#include "obj/ControlChannelIdClass.hpp"
#include "obj/ObjectClassTypeTraits.hpp"

namespace lmp
{
  namespace obj
  {
    class ControlChannelIdData;
    class ControlChannelIdIF;
    template <>
    struct ObjectClassBaseTraits<ccid::ClassType>
    {
      static const otype::ObjectClass  c_object_class = otype::ControlChannelID;
    };
    template <>
    struct ObjectClassCTypeTraits<ccid::ClassType, ccid::LocalCCId>
    {
      typedef ControlChannelIdIF    object_ctype_if_type;
      typedef ControlChannelIdData  data_type;
    };
    template <>
    struct ObjectClassCTypeTraits<ccid::ClassType, ccid::RemoteCCId>
    {
      typedef ControlChannelIdIF    object_ctype_if_type;
      typedef ControlChannelIdData  data_type;
    };
  } // namespace obj
} // namespace lmp

#endif /* LMP_OBJ_CONTROL_CHANNEL_ID_TYPE_TRAITS_HPP_ */
