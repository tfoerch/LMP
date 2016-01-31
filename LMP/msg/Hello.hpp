#ifndef LMP_MSG_HELLO_HPP_
#define LMP_MSG_HELLO_HPP_
/*
 * Config.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "msg/LMPMessageIF.hpp"
#include "obj/Hello.hpp"
#include "base/ProtocolTypes.hpp"                  // for DWORD

namespace lmp
{
  namespace msg
  {
    class Hello : public LMPMessageIF
    {
	public:
      Hello(
        const lmp::obj::Hello&  hello);
      inline const lmp::obj::Hello& getHello() const { return m_hello; }
    private:
      virtual const mtype::MsgType do_getMsgType() const;
      virtual lmp::WORD do_getContentsLength() const;
      virtual CommonHeader::OptEncError do_encodeContents(
    	boost::asio::mutable_buffer&  buffer) const;
      lmp::obj::Hello  m_hello;
    };
  } // namespace msg
} // namespace lmp

#endif /* LMP_MSG_HELLO_HPP_ */
