#ifndef LMP_OBJ_OBJECTCLASS_HPP_
#define LMP_OBJ_OBJECTCLASS_HPP_
/*
 * ObjectClass.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "base/ProtocolTypes.hpp"
#include "obj/ByteSequence.hpp"
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
      typedef ObjectClass            obj_class_type;
      static const  obj_class_type   obj_class = objClass;
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
    // instantiate following with ObjectClassTypeData<ObjectClassTypeTraits<ClassType, ctype>>
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
      std::ostream&                               os,
      const ObjectClassTypeData<ObjCTypeTraits>&  objClassCTypeData);
    template <typename   ObjCTypeTraits>
    bool operator==(
       const ObjectClassTypeData<ObjCTypeTraits>&  first,
       const ObjectClassTypeData<ObjCTypeTraits>&  second);
    template <typename   ObjCTypeTraits>
    lmp::DWORD getLength(
      const ObjectClassTypeData<ObjCTypeTraits>&  objClassCTypeData);
    template<typename ObjCTypeTraits>
    struct GetLength
    {
      template<typename> struct result { typedef lmp::WORD type; };
      lmp::WORD operator()(
        const ObjectClassTypeData<ObjCTypeTraits>& objClassCTypeData) const
      {
        return getLength(objClassCTypeData);
      }
    };
    template <typename  ObjClassTraits>
    class ObjectClassUnknownCTypeData
    {
    public:
      typedef typename ObjClassTraits::obj_class_type  obj_class_type;
      static const  obj_class_type                     obj_class;
      lmp::BYTE                                        m_class_type;
      bool                                             m_negotiable;
      ByteSequence                                     m_data;
    };
    template <typename   ObjClassTraits>
    std::ostream& operator<<(
      std::ostream&                                       os,
      const ObjectClassUnknownCTypeData<ObjClassTraits>&  objClassUnknownCTypeData);
    template <typename   ObjClassTraits>
    bool operator==(
      const ObjectClassUnknownCTypeData<ObjClassTraits>&  first,
      const ObjectClassUnknownCTypeData<ObjClassTraits>&  second);
    template <typename   ObjClassTraits>
    lmp::DWORD getLength(
      const ObjectClassUnknownCTypeData<ObjClassTraits>&  objClassUnknownCTypeData);
    template<typename ObjClassTraits>
    struct GetLengthUnknownCTypeData
    {
      template<typename> struct result { typedef lmp::WORD type; };
      lmp::WORD operator()(
        const ObjectClassUnknownCTypeData<ObjClassTraits>& objClassUnknownCTypeData) const
      {
        return getLength(objClassUnknownCTypeData);
      }
    };
    const lmp::WORD  c_objHeaderLength = 4;
    const lmp::BYTE  c_negotiableMask = 0x80;
    const lmp::BYTE  c_classTypeMask = 0x7f;
    namespace parse
    {
      namespace qi = boost::spirit::qi;
      template <typename Iterator, typename ClassType, ClassType ctype>
      struct object_class_grammar : qi::grammar<Iterator,
                                                ObjectClassTypeData<ObjectClassTypeTraits<ClassType, ctype> >(),
                                                qi::locals<lmp::WORD> >
      {
        object_class_grammar();

        typename ObjectClassTypeParseTraits<Iterator, ClassType, ctype>::grammar_type       object_body;
        qi::rule<Iterator,
                 ObjectClassTypeData<ObjectClassTypeTraits<ClassType, ctype>>(),
                 qi::locals<lmp::WORD>>                                                     object_class_rule;
      };
      template <typename Iterator, ObjectClass objClass>
      struct object_class_unknown_ctype_grammar : qi::grammar<Iterator,
                                                              ObjectClassUnknownCTypeData<ObjectClassTraits<objClass> >(),
                                                              qi::locals<lmp::WORD> >
      {
        object_class_unknown_ctype_grammar();

        byte_sequence_grammar<Iterator>                                         byte_sequence;
        qi::rule<Iterator,
                 ObjectClassUnknownCTypeData<ObjectClassTraits<objClass>>(),
                 qi::locals<lmp::WORD>>                                         object_class_unknown_ctype_rule;
      };
    }
    namespace generate
    {
      namespace qi = boost::spirit::qi;
      namespace karma = boost::spirit::karma;
      template <typename OutputIterator, typename ClassType, ClassType ctype>
      struct object_class_grammar : karma::grammar<OutputIterator, ObjectClassTypeData<ObjectClassTypeTraits<ClassType, ctype>>()>
      {
        object_class_grammar();

        boost::phoenix::function<GetLength<ObjectClassTypeTraits<ClassType, ctype>>>                 phx_getLength;
        typename ObjectClassTypeGenerateTraits<OutputIterator, ClassType, ctype>::grammar_type       object_body;
        karma::rule<OutputIterator, ObjectClassTypeData<ObjectClassTypeTraits<ClassType, ctype>>()>  object_class_rule;
      };
      template <typename OutputIterator, ObjectClass objClass>
      struct object_class_unknown_ctype_grammar : karma::grammar<OutputIterator, ObjectClassUnknownCTypeData<ObjectClassTraits<objClass>>()>
      {
        object_class_unknown_ctype_grammar();

        boost::phoenix::function<GetLengthUnknownCTypeData<ObjectClassTraits<objClass>>>         phx_getLength;
        byte_sequence_grammar<OutputIterator>                                                    byte_sequence;
        karma::rule<OutputIterator, ObjectClassUnknownCTypeData<ObjectClassTraits<objClass>>()>  object_class_unknown_ctype_rule;
      };
    }
  } // namespace obj
} // namespace lmp

#endif /* LMP_OBJ_OBJECTCLASS_HPP_ */
