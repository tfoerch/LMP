#ifndef LMP_OBJ_UNKNOWN_OBJECT_CLASS_DEF_HPP_
#define LMP_OBJ_UNKNOWN_OBJECT_CLASS_DEF_HPP_
/*
 * UnknownObjectClass_def.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "obj/UnknownObjectClass.hpp"
#include "obj/ObjectHeader.hpp"
#include "obj/ControlChannelIdClass.hpp"
#include <boost/spirit/include/qi_binary.hpp>
#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/spirit/include/phoenix_fusion.hpp>
#include <boost/spirit/include/phoenix_stl.hpp>
#include <boost/phoenix/object/static_cast.hpp>

#include <type_traits>

BOOST_FUSION_ADAPT_STRUCT(
  lmp::obj::UnknownObjectClassData,
  (lmp::BYTE,               m_object_class)
  (lmp::BYTE,               m_class_type)
  (bool,                    m_negotiable)
  (lmp::WORD,               m_length)
  (lmp::obj::ByteSequence,  m_data)
)

namespace lmp
{
  namespace obj
  {
    namespace parse
	{
      namespace fusion = boost::fusion;
      namespace phoenix = boost::phoenix;
      namespace qi = boost::spirit::qi;

      template <typename Iterator>
      unknown_object_class_grammar<Iterator>::unknown_object_class_grammar()
	  : unknown_object_class_grammar::base_type(unknown_object_class_rule,
			                                    "unknown_object_class")
      {
        using qi::byte_;
    	using qi::big_word;
    	using qi::_1;
    	using phoenix::at_c;
    	using namespace qi::labels;

    	unknown_object_class_rule =
    	    byte_ [at_c<1>(_val) = (_1 & lmp::obj::ObjectHeader::c_classTypeMask), at_c<2>(_val) = (_1 & lmp::obj::ObjectHeader::c_negotiableMask) ]  // class type
    		>> byte_  [at_c<0>(_val) = _1 ] // object class
    		>> big_word  [ at_c<3>(_val) = _1 ] // length
			>> byte_sequence( at_c<3>(_val) - 4 ) [ at_c<4>(_val) = _1 ]
			;

    	unknown_object_class_rule.name("unknown_object_class");
      }

	} // namespace parse
  } // namespace obj
} // namespace lmp

#endif /* LMP_OBJ_UNKNOWN_OBJECT_CLASS_DEF_HPP_ */
