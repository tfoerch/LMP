#ifndef LMP_OBJ_CONFIG_TYPE_TRAITS_HPP_
#define LMP_OBJ_CONFIG_TYPE_TRAITS_HPP_
/*
 * ConfigTypeTraits.hpp
 *
 *  Created on: 16.02.2015
 *      Author: tom
 */

#include "obj/ConfigClass.hpp"
#include "obj/ObjectClassTypeTraits.hpp"
#include "obj/HelloConfigData.hpp"

namespace lmp
{
  namespace obj
  {
    class HelloConfigIF;
    template <>
    struct ObjectClassBaseTraits<config::ClassType>
    {
      static const otype::ObjectClass  c_object_class = otype::Config;
      static boost::optional<config::ClassType> classType_cast(
        lmp::BYTE                     classTypeByte)
	  {
    	boost::optional<config::ClassType>  result;
        const config::ClassType cType = static_cast<config::ClassType>(classTypeByte);
        switch(cType)
        {
          case config::HelloConfig:
        	result = cType;
        	break;
          default:
        	break;
        }
        return result;
	  }
    };
    template <>
    struct ObjectClassCTypeTraits<config::ClassType, config::HelloConfig>
    {
      typedef HelloConfigIF    object_ctype_if_type;
      typedef HelloConfigData  data_type;
      static bool isNegotiable(const data_type& data) { return data.isNegotiable(); }
    };
  } // namespace obj
} // namespace lmp

#endif /* LMP_OBJ_CONFIG_TYPE_TRAITS_HPP_ */
