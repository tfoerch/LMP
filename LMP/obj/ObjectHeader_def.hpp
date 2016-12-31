#ifndef LMP_OBJ_OBJECTHEADER_DEF_HPP_
#define LMP_OBJ_OBJECTHEADER_DEF_HPP_
/*
 * ObjectHeader_def.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "obj/ObjectHeader.hpp"
#include "obj/ObjectClass.hpp"
#include <boost/spirit/include/qi_binary.hpp>
#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/spirit/include/phoenix_fusion.hpp>
#include <boost/spirit/include/phoenix_stl.hpp>
#include <boost/spirit/include/karma_attr_cast.hpp>
#include <boost/phoenix/object/static_cast.hpp>
#include <boost/fusion/adapted/struct/adapt_struct.hpp>
#include <boost/fusion/include/adapt_struct.hpp>

BOOST_FUSION_ADAPT_STRUCT(
  lmp::obj::parse::ObjectHeaderVariableLengthInput,
  (lmp::BYTE,       m_object_class)
  (lmp::BYTE,       m_class_type)
)

BOOST_FUSION_ADAPT_STRUCT(
  lmp::obj::parse::ObjectHeaderVariableLengthOutput,
  (bool,            m_negotiable)
  (lmp::WORD,       m_length)
)


} // namespace lmp

#endif /* LMP_OBJ_OBJECTHEADER_DEF_HPP_ */
