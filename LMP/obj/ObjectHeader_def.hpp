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
  lmp::obj::parse::ObjectHeaderFixLengthInput,
  (lmp::BYTE,       m_object_class)
  (lmp::BYTE,       m_class_type)
  (lmp::WORD,       m_length)
)

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

BOOST_FUSION_ADAPT_STRUCT(
  lmp::obj::parse::ObjectHeaderUnknownCTypeOutput,
  (lmp::BYTE,       m_class_type)
  (bool,            m_negotiable)
  (lmp::WORD,       m_length)
)

BOOST_FUSION_ADAPT_STRUCT(
  lmp::obj::parse::ObjectHeaderUnknownObjectClassOutput,
  (lmp::BYTE,       m_object_class)
  (lmp::BYTE,       m_class_type)
  (bool,            m_negotiable)
  (lmp::WORD,       m_length)
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
      object_header_fix_length_grammar<Iterator>::object_header_fix_length_grammar()
	  : object_header_fix_length_grammar<Iterator>::base_type(object_header_fix_length_rule, "object_header_fix_length")
	  {
        using qi::byte_;
        using qi::big_word;
        using phoenix::at_c;
        using namespace qi::labels;

        object_header_fix_length_rule =
          ( byte_(at_c<1>(_r1))                                        [ _val = false ] |
	        byte_(at_c<1>(_r1) + lmp::obj::parse::negotiableFlagValue) [ _val = true  ] ) // class type
		  >> byte_(at_c<0>(_r1))    // object class
		  >> big_word(at_c<2>(_r1)) // length
		  ;

        object_header_fix_length_rule.name("object_header_fix_length");
	  }
      template <typename Iterator>
      object_header_unknown_class_type_grammar<Iterator>::object_header_unknown_class_type_grammar()
	  : object_header_unknown_class_type_grammar<Iterator>::base_type(object_header_unknown_class_type_rule, "object_header_unknown_class_type")
	  {
        using qi::byte_;
        using qi::big_word;
        using phoenix::at_c;
        using namespace qi::labels;

        object_header_unknown_class_type_rule =
          byte_ [at_c<0>(_val) = (_1 & lmp::obj::ObjectHeader::c_classTypeMask), at_c<1>(_val) = (_1 & lmp::obj::ObjectHeader::c_negotiableMask) ]  // class type
		  >> byte_(_r1)    // object class
		  >> big_word  [ at_c<2>(_val) = _1 ] // length
		  ;

        object_header_unknown_class_type_rule.name("object_header_unknown_class_type");
	  }
      template <typename Iterator>
      object_header_unknown_object_class_grammar<Iterator>::object_header_unknown_object_class_grammar()
	  : object_header_unknown_object_class_grammar<Iterator>::base_type(object_header_unknown_object_class_rule, "object_header_unknown_object_class")
	  {
        using qi::byte_;
        using qi::big_word;
        using phoenix::at_c;
        using namespace qi::labels;

        object_header_unknown_object_class_rule =
          byte_ [at_c<1>(_val) = (_1 & lmp::obj::ObjectHeader::c_classTypeMask), at_c<2>(_val) = (_1 & lmp::obj::ObjectHeader::c_negotiableMask) ]  // class type
		  >> byte_  [at_c<0>(_val) = _1 ] // object class
		  >> big_word  [ at_c<3>(_val) = _1 ] // length
		  ;

        object_header_unknown_object_class_rule.name("object_header_unknown_object_class");
	  }
	} // namespace parse
  } // namespace obj
} // namespace lmp

#endif /* LMP_OBJ_OBJECTHEADER_DEF_HPP_ */
