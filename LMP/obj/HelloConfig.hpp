#ifndef LMP_OBJ_HELLOCONFIG_HPP_
#define LMP_OBJ_HELLOCONFIG_HPP_
/*
 * ConfigClass.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include <ConfigClass.hpp>
#include <ObjectClassTypeTraits.hpp>
#include <ObjectClassType.hpp>
#include <ConfigTypeTraits.hpp>
#include <HelloConfigIF.hpp>
#include <HelloConfigData.hpp>

namespace lmp
{
  namespace obj
  {
    typedef ObjectClassType<config::ClassType, config::HelloConfig>  HelloConfig;
  } // namespace obj
} // namespace lmp

#endif /* LMP_OBJ_HELLOCONFIG_HPP_ */
