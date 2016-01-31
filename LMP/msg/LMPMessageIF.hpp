#ifndef LMP_MSG_LMPMESSAGEIF_HPP_
#define LMP_MSG_LMPMESSAGEIF_HPP_
/*
 * LMPMessageIF.hpp
 *
 *  Created on: 16.02.2015
 *      Author: tom
 */

#include "base/ProtocolTypes.hpp"
#include "msg/MsgType.hpp"
#include "msg/CommonHeader.hpp"

// http://www.boost.org/doc/libs/1_57_0/libs/ptr_container/doc/guidelines.html
namespace lmp
{
  namespace msg
  {
    class LMPMessageIF
    {
    public:
      inline const mtype::MsgType getMsgType() const { return do_getMsgType(); }
      inline lmp::WORD getLmpLength() const
      { return CommonHeader::c_headerLength + do_getContentsLength(); }
      inline CommonHeader::OptEncError encode(
    	lmp::BYTE                     version,
		bool                          controlChannelDown,
		bool                          lmpRestart,
    	boost::asio::mutable_buffer&  buffer) const
      {
    	CommonHeader  msgHeader(version, controlChannelDown, lmpRestart, getMsgType(), getLmpLength());
    	CommonHeader::OptEncError optHeaderEncResult = msgHeader.encode(buffer);
    	if (optHeaderEncResult)
    	{
    	  return optHeaderEncResult;
    	}
    	else
    	{
          return do_encodeContents(buffer);
    	}
      }
      virtual ~LMPMessageIF(){}
    private:
      virtual const mtype::MsgType do_getMsgType() const = 0;
      virtual lmp::WORD do_getContentsLength() const = 0;
      virtual CommonHeader::OptEncError do_encodeContents(
    	boost::asio::mutable_buffer&  buffer) const = 0;
    };
  } // namespace msg
} // namespace lmp

#endif /* LMP_MSG_LMPMESSAGEIF_HPP_ */
