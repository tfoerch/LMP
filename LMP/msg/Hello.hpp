#ifndef LMP_MSG_HELLO_HPP_
#define LMP_MSG_HELLO_HPP_
/*
 * Config.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include <ProtocolTypes.hpp>                  // for DWORD

namespace lmp
{
  namespace msg
  {
    class Hello
    {
	public:
      Hello(
        lmp::DWORD   txSeqNum,
		lmp::DWORD   rcvSeqNum);
  	  lmp::DWORD   theTxSeqNum;
  	  lmp::DWORD   theRcvSeqNum;
    };
  } // namespace msg
} // namespace lmp

#endif /* LMP_MSG_HELLO_HPP_ */
