/*
 * Hello.cpp
 *
 *  Created on: 20.02.2015
 *      Author: tom
 */

#include "Hello.hpp"

namespace lmp
{
  namespace msg
  {
    Hello::Hello(
      const lmp::obj::Hello&  hello)
    : m_hello(hello)
    {}
    const mtype::MsgType Hello::do_getMsgType() const
    {
      return mtype::Hello;
    }
    lmp::WORD Hello::do_getContentsLength() const
    {
      return m_hello.getObjLength();
    }
    CommonHeader::OptEncError Hello::do_encodeContents(
  	  boost::asio::mutable_buffer&  buffer) const
    {
      obj::ObjectHeader::OptEncError optEncError = m_hello.encode(buffer);
      if (optEncError &&
    	  *optEncError == obj::ObjectHeader::insufficient_buffer_length)
      {
    	return CommonHeader::OptEncError(CommonHeader::insufficient_buffer_length);
      }
      return boost::none;
    }
  } // namespace msg
} // namespace lmp
