#ifndef LMP_OBJ_LINK_ID_TYPE_TRAITS_HPP_
#define LMP_OBJ_LINK_ID_TYPE_TRAITS_HPP_
/*
 * LinkIdTraits.hpp
 *
 *  Created on: 16.02.2015
 *      Author: tom
 */

#include <LinkIdClass.hpp>
#include <ObjectClassTypeTraits.hpp>

namespace lmp
{
  namespace obj
  {
    class LinkIdDWordData;
    class LinkIdIPv6Data;
    class LinkIdDWordIF;
    class LinkIdIPv6IF;
    template <>
    struct ObjectClassBaseTraits<linkid::ClassType>
    {
      static const otype::ObjectClass  c_object_class = otype::LinkID;
    };
    template <>
    struct ObjectClassCTypeTraits<linkid::ClassType, linkid::IPv4LocalLinkId>
    {
      typedef LinkIdDWordIF    object_ctype_if_type;
      typedef LinkIdDWordData  data_type;
    };
    template <>
    struct ObjectClassCTypeTraits<linkid::ClassType, linkid::IPv4RemoteLinkId>
    {
      typedef LinkIdDWordIF    object_ctype_if_type;
      typedef LinkIdDWordData  data_type;
    };
    template <>
    struct ObjectClassCTypeTraits<linkid::ClassType, linkid::IPv6LocalLinkId>
    {
      typedef LinkIdIPv6IF    object_ctype_if_type;
      typedef LinkIdIPv6Data  data_type;
    };
    template <>
    struct ObjectClassCTypeTraits<linkid::ClassType, linkid::IPv6RemoteLinkId>
    {
      typedef LinkIdIPv6IF    object_ctype_if_type;
      typedef LinkIdIPv6Data  data_type;
    };
    template <>
    struct ObjectClassCTypeTraits<linkid::ClassType, linkid::UnnumberedLocalLinkId>
    {
      typedef LinkIdDWordIF    object_ctype_if_type;
      typedef LinkIdDWordData  data_type;
    };
    template <>
    struct ObjectClassCTypeTraits<linkid::ClassType, linkid::UnnumberedRemoteLinkId>
    {
      typedef LinkIdDWordIF    object_ctype_if_type;
      typedef LinkIdDWordData  data_type;
    };
  } // namespace obj
} // namespace lmp

#endif /* LMP_OBJ_LINK_ID_TYPE_TRAITS_HPP_ */
