#ifndef LMP_OBJ_OBJECTCLASS_DEF_HPP_
#define LMP_OBJ_OBJECTCLASS_DEF_HPP_
/*
 * ObjectClass_def.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "obj/ObjectClass.hpp"
#include <boost/spirit/include/qi_binary.hpp>
#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/spirit/include/phoenix_fusion.hpp>
#include <boost/spirit/include/phoenix_stl.hpp>
#include <boost/phoenix/object/static_cast.hpp>
#include <boost/fusion/adapted/struct/adapt_struct.hpp>
#include <boost/fusion/include/adapt_struct.hpp>

#include <type_traits>

BOOST_FUSION_ADAPT_TPL_STRUCT(
  (ObjCTypeTraits),
  (lmp::obj::ObjectClassTypeData)(ObjCTypeTraits),
//  (static const typename ObjCTypeTraits::ctype_type,  ctype)
  (bool,                                              m_negotiable)
  (typename ObjCTypeTraits::data_type,                m_data))

BOOST_FUSION_ADAPT_TPL_STRUCT(
  (ObjClassTraits),
  (lmp::obj::ObjectClassUnknownCTypeData)(ObjClassTraits),
  (lmp::BYTE,               m_class_type)
  (bool,                    m_negotiable)
  (lmp::obj::ByteSequence,  m_data)
)

namespace lmp
{
  namespace obj
  {
    template <typename   ObjCTypeTraits>
    std::ostream& operator<<(
      std::ostream&                               os,
      const ObjectClassTypeData<ObjCTypeTraits>&  objClassCTypeData)
    {
      os << (objClassCTypeData.m_negotiable ? "negotiable" : "not negotiable") << ", "
         << objClassCTypeData.m_data;
      return os;
    }
    template <typename   ObjCTypeTraits>
    bool operator==(
       const ObjectClassTypeData<ObjCTypeTraits>&  first,
       const ObjectClassTypeData<ObjCTypeTraits>&  second)
    {
      return
        ( first.m_negotiable == second.m_negotiable &&
          typename ObjCTypeTraits::equal_ftor_type()(first.m_data, second.m_data) );
    }
    template <typename   ObjCTypeTraits>
    lmp::DWORD getLength(
      const ObjectClassTypeData<ObjCTypeTraits>&  objClassCTypeData)
    {
      return
        ( c_objHeaderLength +
          typename ObjCTypeTraits::get_length_ftor_type()(objClassCTypeData.m_data) );
    }
    template <typename   ObjClassTraits>
    std::ostream& operator<<(
      std::ostream&                                       os,
      const ObjectClassUnknownCTypeData<ObjClassTraits>&  objClassUnknownCTypeData)
    {
      os << static_cast<lmp::WORD>(objClassUnknownCTypeData.m_class_type) << ", "
    	 << (objClassUnknownCTypeData.m_negotiable ? "negotiable" : "not negotiable") << ", ";
      {
    	using namespace hex_stream;
    	os << objClassUnknownCTypeData.m_data;
      }
      return os;
    }
    template <typename   ObjClassTraits>
    bool operator==(
      const ObjectClassUnknownCTypeData<ObjClassTraits>&  first,
      const ObjectClassUnknownCTypeData<ObjClassTraits>&  second)
    {
      return
        ( first.m_class_type == second.m_class_type &&
          first.m_negotiable == second.m_negotiable &&
          first.m_data == second.m_data  );
    }
    template <typename   ObjClassTraits>
    lmp::DWORD getLength(
      const ObjectClassUnknownCTypeData<ObjClassTraits>&  objClassUnknownCTypeData)
    {
      return
        ( c_objHeaderLength +
          objClassUnknownCTypeData.m_data.size() );
    }
    namespace parse
    {
      namespace fusion = boost::fusion;
      namespace phoenix = boost::phoenix;
      namespace qi = boost::spirit::qi;

      template <typename Iterator, typename ClassType, ClassType ctype>
      object_class_grammar<Iterator, ClassType, ctype>::object_class_grammar()
      : object_class_grammar::base_type(object_class_rule, "object_class")
      {
        using qi::byte_;
     	using qi::big_word;
     	using qi::big_dword;
     	using qi::_1;
     	using phoenix::at_c;
     	using namespace qi::labels;

     	object_class_rule =
     	    ( byte_(static_cast<typename std::underlying_type<ClassType>::type>(ctype))                              [ at_c<0>(_val) = false ] |
     	      byte_(static_cast<typename std::underlying_type<ClassType>::type>(ctype) + lmp::obj::c_negotiableMask) [ at_c<0>(_val) = true  ] ) // class type
     	    >> byte_(static_cast<typename std::underlying_type<ObjectClass>::type>(ObjectClassTypeConst<ClassType>::obj_class))    // object class
     	    >> big_word [_a = _1] // length
     	    >> object_body(_a) [ at_c<1>(_val) = _1 ]
     	    ;

     	object_class_rule.name("object_class");
      }
      template <typename Iterator, ObjectClass objClass>
      object_class_unknown_ctype_grammar<Iterator, objClass>::object_class_unknown_ctype_grammar()
      : object_class_unknown_ctype_grammar::base_type(object_class_unknown_ctype_rule, "object_class_unknown_ctype")
      {
        using qi::byte_;
        using qi::big_word;
        using qi::_1;
        using phoenix::at_c;
        using namespace qi::labels;

        object_class_unknown_ctype_rule =
            byte_ [at_c<0>(_val) = (_1 & lmp::obj::c_classTypeMask), at_c<1>(_val) = (_1 & lmp::obj::c_negotiableMask) ]  // class type
            >> byte_(static_cast<typename std::underlying_type<ObjectClass>::type>(objClass))    // object class
            >> big_word [_a = _1] // length
            >> byte_sequence(_a - lmp::obj::c_objHeaderLength) [ at_c<2>(_val) = _1 ]
            ;

        object_class_unknown_ctype_rule.name("object_class_unknown_ctype");

      }
    }
    namespace generate
    {
      namespace fusion = boost::fusion;
      namespace phoenix = boost::phoenix;
      namespace qi = boost::spirit::qi;

      template <typename OutputIterator, typename ClassType, ClassType ctype>
      object_class_grammar<OutputIterator, ClassType, ctype>::object_class_grammar()
      : object_class_grammar::base_type(object_class_rule, "object_class")
      {
        using qi::byte_;
        using qi::big_word;
        using qi::big_dword;
        using qi::eps;
        using phoenix::at_c;
        using namespace qi::labels;

        object_class_rule =
            (  eps(at_c<0>(_val)) << byte_ [ _1 = ( static_cast<typename std::underlying_type<ClassType>::type>(ctype) | lmp::obj::c_negotiableMask ) ] |
               byte_ [ _1 = static_cast<typename std::underlying_type<ClassType>::type>(ctype) ] ) // class type
            << byte_ [ _1 = static_cast<typename std::underlying_type<ObjectClass>::type>(ObjectClassTypeConst<ClassType>::obj_class) ] // object class
            << big_word [ _1 = phx_getLength(_val) ] // length
//            << big_word [ _1 = (c_objHeaderLength + sizeof(typename ObjectClassTypeTraits<ClassType, ctype>::data_type)) ] // length
            << object_body [ _1 = at_c<1>(_val) ]
            ;

        object_class_rule.name("object_class");
      }
      template <typename OutputIterator, ObjectClass objClass>
      object_class_unknown_ctype_grammar<OutputIterator, objClass>::object_class_unknown_ctype_grammar()
      : object_class_unknown_ctype_grammar::base_type(object_class_unknown_ctype_rule, "object_class_unknown_ctype")
      {
        using qi::byte_;
        using qi::big_word;
        using qi::big_dword;
        using qi::eps;
        using phoenix::at_c;
        using namespace qi::labels;

        object_class_unknown_ctype_rule =
            ( eps(at_c<1>(_val)) << byte_ [ _1 = ( at_c<0>(_val) | lmp::obj::c_negotiableMask ) ] |
              byte_ [ _1 = at_c<0>(_val) ] ) // class type
            << byte_ [ _1 = static_cast<typename std::underlying_type<ObjectClass>::type>(objClass) ] // object class
            << big_word [ _1 = phx_getLength(_val) ] // length
//            << big_word [ _1 = at_c<2>(_val) ] // length
            << byte_sequence [ _1 = at_c<2>(_val) ]
            ;

        object_class_unknown_ctype_rule.name("object_class_unknown_ctype");
      }
    }
  } // namespace obj
} // namespace lmp

#endif /* LMP_OBJ_OBJECTCLASS_DEF_HPP_ */