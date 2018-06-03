#ifndef LMP_OBJ_CONFIG_CTYPES_HPP_
#define LMP_OBJ_CONFIG_CTYPES_HPP_
/*
 * ConfigCTypesAst.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "obj/HelloConfigAst.hpp"
#include "obj/UnknownConfigCTypeAst.hpp"

#include <boost/variant.hpp>

namespace lmp
{
  namespace obj
  {
    namespace config
    {
      namespace ast
      {
         typedef boost::variant<lmp::obj::config::ast::HelloConfig,
                                lmp::obj::config::ast::UnknownConfigCType>   ConfigCTypes;
      }
    }
  } // namespace obj
} // namespace lmp

#endif /* LMP_OBJ_CONFIG_CTYPES_HPP_ */
