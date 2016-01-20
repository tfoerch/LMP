#ifndef LMP_OBJ_LMPOBJECTIF_HPP_
#define LMP_OBJ_LMPOBJECTIF_HPP_
/*
 * LMPObjectIF.hpp
 *
 *  Created on: 16.02.2015
 *      Author: tom
 */

#include <ProtocolTypes.hpp>
#include <ObjectClass.hpp>
#include <ObjectHeader.hpp>

// http://www.boost.org/doc/libs/1_57_0/libs/ptr_container/doc/guidelines.html
namespace lmp
{
  namespace obj
  {
    class LMPObjectIF
    {
    public:
      inline lmp::BYTE getClassType() const { return do_getClassType(); }
      inline bool isNegotiable() const { return do_isNegotiable(); }
      inline const otype::ObjectClass getObjectClass() const { return do_getObjectClass(); }
      inline lmp::WORD getObjLength() const
      { return ObjectHeader::c_headerLength + do_getContentsLength(); }
      inline ObjectHeader::OptEncError encode(
    	boost::asio::mutable_buffer&  buffer) const
      {
    	ObjectHeader  objHeader(isNegotiable(), getClassType(), getObjectClass(), getObjLength());
    	ObjectHeader::OptEncError optHeaderEncResult = objHeader.encode(buffer);
    	if (optHeaderEncResult)
    	{
    	  return optHeaderEncResult;
    	}
    	else
    	{
          return do_encodeContents(buffer);
    	}
      }
      virtual ~LMPObjectIF(){}
    private:
      virtual lmp::BYTE do_getClassType() const = 0;
      virtual bool do_isNegotiable() const = 0;
      virtual const otype::ObjectClass do_getObjectClass() const = 0;
      virtual lmp::WORD do_getContentsLength() const = 0;
      virtual ObjectHeader::OptEncError do_encodeContents(
    	boost::asio::mutable_buffer&  buffer) const = 0;
    };
  } // namespace obj
} // namespace lmp

#endif /* LMP_OBJ_LMPOBJECTIF_HPP_ */
