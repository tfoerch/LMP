#ifndef LMP_OBJ_HELLOCONFIG_HPP_
#define LMP_OBJ_HELLOCONFIG_HPP_
/*
 * HelloConfig.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "obj/ConfigClass.hpp"
#include "obj/ObjectClassTypeTraits.hpp"
#include "obj/ObjectClassType.hpp"
#include "obj/ConfigTypeTraits.hpp"
#include "obj/HelloConfigIF.hpp"
#include "obj/HelloConfigData.hpp"

namespace lmp
{
  namespace obj
  {
    typedef ObjectClassType<config::ClassType, config::HelloConfig>  HelloConfig;
  } // namespace obj
} // namespace lmp

#endif /* LMP_OBJ_HELLOCONFIG_HPP_ */
