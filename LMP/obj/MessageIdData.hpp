#ifndef LMP_OBJ_MESSAGE_ID_DATA_HPP_
#define LMP_OBJ_MESSAGE_ID_DATA_HPP_
/*
 * MessageIdData.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include <ProtocolTypes.hpp>                  // for WORD
#include <LMPObjectIF.hpp>

namespace lmp
{
  namespace obj
  {
    class MessageIdData
	{
	public:
      MessageIdData(
    	lmp::DWORD  MessageId);
      inline lmp::DWORD getMessageId() const { return m_messageId; }
      lmp::WORD getContentsLength() const { return c_contentsLength; }
      ObjectHeader::OptEncError encode(
    	boost::asio::mutable_buffer&  buffer) const;
	private:
  	  lmp::DWORD              m_messageId;
      static const lmp::WORD  c_contentsLength;
	};
  } // namespace obj
} // namespace lmp

#endif /* LMP_OBJ_MESSAGE_ID_DATA_HPP_ */
