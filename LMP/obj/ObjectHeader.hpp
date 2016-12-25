#ifndef LMP_OBJ_OBJECTHEADER_HPP_
#define LMP_OBJ_OBJECTHEADER_HPP_
/*
 * ObjectHeader.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "base/ProtocolTypes.hpp"                  // for DWORD
#include "ObjectClass.hpp"

#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/karma.hpp>

#include <boost/optional/optional.hpp>     // for optional

#include <utility>

namespace boost
{
  namespace asio
  {
    class const_buffer;
    class mutable_buffer;
  }
}

namespace lmp
{
  namespace obj
  {
    class ObjectHeader
	{
	public:
      typedef boost::optional<ObjectHeader>      OptHeader;
      enum decoding_error
	  {
    	not_supported_object_class,
		invalid_length,
		unspecified_decoding_error
	  };
      enum encoding_error
	  {
    	insufficient_buffer_length
	  };
      typedef boost::optional<decoding_error>      OptDecError;
      typedef std::pair<OptHeader, OptDecError>    DecodingResult;
      typedef boost::optional<encoding_error>      OptEncError;
      typedef boost::optional<otype::ObjectClass>  OptObjectClass;
      inline ObjectHeader(
    	bool                         negotiable,
        lmp::BYTE                    classType,
		otype::ObjectClass           objectClass,
		lmp::WORD                    objLength)
      : m_negotiable(negotiable),
		m_classType(classType),
		m_objectClass(objectClass),
		m_objLength(objLength)
      {}
      inline lmp::BYTE getClassType() const { return m_classType; }
      inline bool isNegotiable() const { return m_negotiable; }
      inline const otype::ObjectClass& getObjectClass() const { return m_objectClass; }
      inline lmp::WORD getObjLength() const { return m_objLength; }
      OptEncError encode(
        boost::asio::mutable_buffer&  buffer) const;
      static DecodingResult decode(
    	boost::asio::const_buffer&    buffer);
      static OptObjectClass objectClass_cast(
    	lmp::BYTE                     objectClassByte);
	private:
      bool                         m_negotiable;
      lmp::BYTE                    m_classType;
	  otype::ObjectClass           m_objectClass;
	  lmp::WORD                    m_objLength;
	public:
	  static const lmp::WORD       c_headerLength;
	  static const lmp::BYTE       c_negotiableMask;
	  static const lmp::BYTE       c_classTypeMask;
	};
    struct ObjectHeaderData
    {
//      ObjectHeaderData();
//      ObjectHeaderData(
//    	lmp::BYTE               object_class,
//		lmp::BYTE               class_type,
//		lmp::WORD               length);
      lmp::BYTE               m_object_class;
	  lmp::BYTE               m_class_type;
      bool                    m_negotiable;
      lmp::WORD               m_length;
    };
    std::ostream& operator<<(
      std::ostream&            os,
	  const ObjectHeaderData&  objectHeader);
   namespace parse
    {
      struct ObjectHeaderFixLengthInput
	  {
    	ObjectHeaderFixLengthInput(
    	  lmp::BYTE               object_class,
		  lmp::BYTE               class_type,
		  lmp::WORD               length);
	    lmp::BYTE               m_object_class;
	    lmp::BYTE               m_class_type;
	    lmp::WORD               m_length;
	  };
      struct ObjectHeaderVariableLengthInput
      {
        lmp::BYTE               m_object_class;
        lmp::BYTE               m_class_type;
      };
      struct ObjectHeaderVariableLengthOutput
      {
        bool                    m_negotiable;
        lmp::WORD               m_length;
      };
      struct ObjectHeaderUnknownCTypeOutput
      {
	    lmp::BYTE               m_class_type;
        bool                    m_negotiable;
        lmp::WORD               m_length;
      };
      std::ostream& operator<<(
        std::ostream&                          os,
  	    const ObjectHeaderUnknownCTypeOutput&  unknownClassType);
      namespace qi = boost::spirit::qi;
      template <typename Iterator>
      struct object_header_fix_length_grammar : qi::grammar<Iterator, bool(ObjectHeaderFixLengthInput)>
      {
    	object_header_fix_length_grammar();

        qi::rule<Iterator, bool(ObjectHeaderFixLengthInput)>            object_header_fix_length_rule;
      };
      template <typename Iterator>
      struct object_header_variable_length_grammar : qi::grammar<Iterator, ObjectHeaderVariableLengthOutput(ObjectHeaderVariableLengthInput)>
      {
    	object_header_variable_length_grammar();

        qi::rule<Iterator, ObjectHeaderVariableLengthOutput(ObjectHeaderVariableLengthInput)>            object_header_variable_length_rule;
      };
      template <typename Iterator>
      struct object_header_unknown_class_type_grammar : qi::grammar<Iterator, ObjectHeaderUnknownCTypeOutput(lmp::BYTE)>
      {
    	object_header_unknown_class_type_grammar();

        qi::rule<Iterator, ObjectHeaderUnknownCTypeOutput(lmp::BYTE)>           object_header_unknown_class_type_rule;
      };
      template <typename Iterator>
      struct object_header_unknown_object_class_grammar : qi::grammar<Iterator, ObjectHeaderData()>
      {
    	object_header_unknown_object_class_grammar();

        qi::rule<Iterator, ObjectHeaderData()>           object_header_unknown_object_class_rule;
      };
      const lmp::BYTE negotiableFlagValue = 0x80;
    }
	namespace generate
	{
	  namespace karma = boost::spirit::karma;
	  template <typename OutputIterator>
	  struct object_header_grammar : karma::grammar<OutputIterator, ObjectHeaderData()>
	  {
		object_header_grammar();

		karma::rule<OutputIterator, ObjectHeaderData()>   object_header_rule;
	  };
	}
  } // namespace obj
} // namespace lmp

#endif /* LMP_OBJ_OBJECTHEADER_HPP_ */
