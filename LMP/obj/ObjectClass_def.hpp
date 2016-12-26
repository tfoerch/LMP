#ifndef LMP_OBJ_OBJECTCLASS_DEF_HPP_
#define LMP_OBJ_OBJECTCLASS_DEF_HPP_
/*
 * ObjectClass_def.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "obj/ObjectClass.hpp"
#include "obj/ObjectHeader.hpp"
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


namespace lmp
{
  namespace obj
  {
    template <typename   PODType>
    std::ostream& operator<<(
      std::ostream&                        os,
      const ObjectClassTypeData<PODType>&  objClassCTypeData)
    {
      os << (objClassCTypeData.m_negotiable ? "negotiable" : "not negotiable") << ", "
         << objClassCTypeData.m_data;
      return os;
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
		    ( byte_(static_cast<typename std::underlying_type<ClassType>::type>(ctype))                                        [ at_c<0>(_val) = false ] |
		      byte_(static_cast<typename std::underlying_type<ClassType>::type>(ctype) + lmp::obj::parse::negotiableFlagValue) [ at_c<0>(_val) = true  ] ) // class type
			>> byte_(static_cast<typename std::underlying_type<ObjectClass>::type>(ObjectClassTypeConst<ClassType>::obj_class))    // object class
			>> big_word(objHeaderLength + sizeof(typename ObjectClassTypeTraits<ClassType, ctype>::data_type)) // length
			>> object_body [ at_c<1>(_val) = _1 ]
//			>> big_dword [ at_c<1>(_val) = _1 ]
			;

		object_class_rule.name("object_class");
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
            (  eps(at_c<0>(_val)) << byte_ [ _1 = ( static_cast<typename std::underlying_type<ClassType>::type>(ctype) | lmp::obj::ObjectHeader::c_negotiableMask ) ] |
               byte_ [ _1 = static_cast<typename std::underlying_type<ClassType>::type>(ctype) ] ) // class type
    		<< byte_ [ _1 = static_cast<typename std::underlying_type<ObjectClass>::type>(ObjectClassTypeConst<ClassType>::obj_class) ] // object class
			<< big_word [ _1 = (objHeaderLength + sizeof(typename ObjectClassTypeTraits<ClassType, ctype>::data_type)) ] // length
		    << object_body [ _1 = at_c<1>(_val) ]
//            << big_dword [ _1 = at_c<1>(_val) ]
			;

    	object_class_rule.name("object_class");
      }
	}
  } // namespace obj
} // namespace lmp

#endif /* LMP_OBJ_OBJECTCLASS_DEF_HPP_ */
