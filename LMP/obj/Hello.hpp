#ifndef LMP_OBJ_HELLO_HPP_
#define LMP_OBJ_HELLO_HPP_
/*
 * ConfigClass.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "obj/HelloClass.hpp"
#include "obj/ObjectClassTypeTraits.hpp"
#include "obj/ObjectClassType.hpp"
#include "obj/HelloTypeTraits.hpp"
#include "obj/HelloIF.hpp"
#include "obj/HelloData.hpp"

namespace lmp
{
  namespace obj
  {
    typedef ObjectClassType<hello::ClassType, hello::Hello>  Hello;
  } // namespace obj
} // namespace lmp

#endif /* LMP_OBJ_HELLOCONFIG_HPP_ */
