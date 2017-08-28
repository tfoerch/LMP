#ifndef LMP_OBJ_OBJECTCLASS_UNKNOWN_CTYPE_HPP_
#define LMP_OBJ_OBJECTCLASS_UNKNOWN_CTYPE_HPP_
/*
 * ObjectClassUnknownCType.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "obj/ObjectClass.hpp"
#include "obj/ByteSequence.hpp"

namespace lmp
{
  namespace obj
  {
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
    namespace parse
    {
      namespace qi = boost::spirit::qi;
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

#endif /* LMP_OBJ_OBJECTCLASS_UNKNOWN_CTYPE_HPP_ */
