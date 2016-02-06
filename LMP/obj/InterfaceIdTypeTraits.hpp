#ifndef LMP_OBJ_INTERFACE_ID_TYPE_TRAITS_HPP_
#define LMP_OBJ_INTERFACE_ID_TYPE_TRAITS_HPP_
/*
 * InterfaceIdTraits.hpp
 *
 *  Created on: 16.02.2015
 *      Author: tom
 */

#include <InterfaceIdClass.hpp>
#include <ObjectClassTypeTraits.hpp>

namespace lmp
{
  namespace obj
  {
    class InterfaceIdDWordData;
    class InterfaceIdIPv6Data;
    class InterfaceIdDWordIF;
    class InterfaceIdIPv6IF;
    template <>
    struct ObjectClassBaseTraits<ifid::ClassType>
    {
      static const otype::ObjectClass  c_object_class = otype::InterfaceID;
    };
    template <>
    struct ObjectClassCTypeTraits<ifid::ClassType, ifid::IPv4LocalInterfaceId>
    {
      typedef InterfaceIdDWordIF    object_ctype_if_type;
      typedef InterfaceIdDWordData  data_type;
      static bool isNegotiable(const data_type&) { return false; }
    };
    template <>
    struct ObjectClassCTypeTraits<ifid::ClassType, ifid::IPv4RemoteInterfaceId>
    {
      typedef InterfaceIdDWordIF    object_ctype_if_type;
      typedef InterfaceIdDWordData  data_type;
      static bool isNegotiable(const data_type&) { return false; }
    };
    template <>
    struct ObjectClassCTypeTraits<ifid::ClassType, ifid::IPv6LocalInterfaceId>
    {
      typedef InterfaceIdIPv6IF    object_ctype_if_type;
      typedef InterfaceIdIPv6Data  data_type;
      static bool isNegotiable(const data_type&) { return false; }
    };
    template <>
    struct ObjectClassCTypeTraits<ifid::ClassType, ifid::IPv6RemoteInterfaceId>
    {
      typedef InterfaceIdIPv6IF    object_ctype_if_type;
      typedef InterfaceIdIPv6Data  data_type;
      static bool isNegotiable(const data_type&) { return false; }
    };
    template <>
    struct ObjectClassCTypeTraits<ifid::ClassType, ifid::UnnumberedLocalInterfaceId>
    {
      typedef InterfaceIdDWordIF    object_ctype_if_type;
      typedef InterfaceIdDWordData  data_type;
      static bool isNegotiable(const data_type&) { return false; }
    };
    template <>
    struct ObjectClassCTypeTraits<ifid::ClassType, ifid::UnnumberedRemoteInterfaceId>
    {
      typedef InterfaceIdDWordIF    object_ctype_if_type;
      typedef InterfaceIdDWordData  data_type;
      static bool isNegotiable(const data_type&) { return false; }
    };
  } // namespace obj
} // namespace lmp

#endif /* LMP_OBJ_INTERFACE_ID_TYPE_TRAITS_HPP_ */
