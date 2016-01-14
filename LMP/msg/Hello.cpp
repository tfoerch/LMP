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
      lmp::DWORD   txSeqNum,
	  lmp::DWORD   rcvSeqNum)
    : theTxSeqNum(txSeqNum),
	  theRcvSeqNum(rcvSeqNum)
    {}
  } // namespace msg
} // namespace lmp
