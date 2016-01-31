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
  } // namespace obj
} // namespace lmp

#endif /* LMP_OBJ_OBJECTHEADER_HPP_ */
