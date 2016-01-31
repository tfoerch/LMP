#ifndef LMP_OBJ_HELLO_DATA_HPP_
#define LMP_OBJ_HELLO_DATA_HPP_
/*
 * HelloData.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "base/ProtocolTypes.hpp"                  // for WORD
#include "obj/LMPObjectIF.hpp"

namespace lmp
{
  namespace obj
  {
    class HelloData
	{
	public:
      HelloData(
    	lmp::DWORD  txSeqNum,
		lmp::DWORD  rcvSeqNum);
      inline lmp::DWORD getTxSeqNum() const { return m_txSeqNum; }
      inline lmp::DWORD getRcvSeqNum() const { return m_rcvSeqNum; }
      lmp::WORD getContentsLength() const { return c_contentsLength; }
      ObjectHeader::OptEncError encode(
    	boost::asio::mutable_buffer&  buffer) const;
	private:
  	  lmp::DWORD              m_txSeqNum;
      lmp::DWORD              m_rcvSeqNum;
      static const lmp::WORD  c_contentsLength;
	};
  } // namespace obj
} // namespace lmp

#endif /* LMP_OBJ_HELLO_DATA_HPP_ */
