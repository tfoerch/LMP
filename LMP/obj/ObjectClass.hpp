#ifndef LMP_OBJ_OBJECTCLASS_HPP_
#define LMP_OBJ_OBJECTCLASS_HPP_
/*
 * ObjectClass.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "base/ProtocolTypes.hpp"
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/karma.hpp>

namespace lmp
{
  namespace obj
  {
    enum class ObjectClass : lmp::BYTE
	{
      ControlChannelID = 1,
      NodeID,
	  LinkID,
	  InterfaceID,
	  MessageID,
	  Config,
	  Hello
	};
    std::ostream& operator<<(
      std::ostream&       os,
	  const ObjectClass&  objClass);
    template <ObjectClass objClass>
    struct ObjectClassTraits
	{
	};
    template <typename ClassType>
    struct ObjectClassTypeConst
	{
      static const ObjectClass  obj_class;
	};
    // specializations should provide a typedef for member data_type
    template <typename ClassType, ClassType ctype>
    struct ObjectClassTypeTraits
	{
	};
    template <typename Iterator, typename ClassType, ClassType ctype>
    struct ObjectClassTypeParseTraits
	{
	};
    template <typename OutputIterator, typename ClassType, ClassType ctype>
    struct ObjectClassTypeGenerateTraits
	{
	};
    // instantiate following with ObjectClassTypeData<ObjectClassTypeTraits<ClassType, ctype>::>data_type
    template <typename   ObjCTypeTraits>
    class ObjectClassTypeData
	{
	public:
      typedef typename ObjCTypeTraits::ctype_type     ctype_type;
      static const ctype_type                         ctype;
	  bool                                            m_negotiable;
	  typename ObjCTypeTraits::data_type              m_data;
	};
    template <typename   ObjCTypeTraits>
    std::ostream& operator<<(
      std::ostream&                        os,
	  const ObjectClassTypeData<ObjCTypeTraits>&  objClass);
	const lmp::WORD objHeaderLength = 4;
    namespace parse
    {
      namespace qi = boost::spirit::qi;

	  template <typename Iterator, typename ClassType, ClassType ctype>
      struct object_class_grammar : qi::grammar<Iterator, ObjectClassTypeData<ObjectClassTypeTraits<ClassType, ctype>>()>
      {
    	object_class_grammar();

    	typename ObjectClassTypeParseTraits<Iterator, ClassType, ctype>::grammar_type       object_body;
    	qi::rule<Iterator, ObjectClassTypeData<ObjectClassTypeTraits<ClassType, ctype>>()>  object_class_rule;
      };
    }
	namespace generate
	{
	  namespace karma = boost::spirit::karma;
	  template <typename OutputIterator, typename ClassType, ClassType ctype>
	  struct object_class_grammar : karma::grammar<OutputIterator, ObjectClassTypeData<ObjectClassTypeTraits<ClassType, ctype>>()>
	  {
		object_class_grammar();

    	typename ObjectClassTypeGenerateTraits<OutputIterator, ClassType, ctype>::grammar_type       object_body;
		karma::rule<OutputIterator, ObjectClassTypeData<ObjectClassTypeTraits<ClassType, ctype>>()>  object_class_rule;
	  };
	}
    namespace otype
    {
      enum ObjectClass
	  {
    	ControlChannelID = 1,
		NodeID,
		LinkID,
		InterfaceID,
		MessageID,
		Config,
		Hello
	  };
    } // namespace otype
  } // namespace obj
} // namespace lmp

#endif /* LMP_OBJ_OBJECTCLASS_HPP_ */
