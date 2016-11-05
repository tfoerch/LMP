/*
 * ControlChannelIdClass.cpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "obj/ControlChannelIdClass.hpp"

std::ostream& lmp::obj::ccid::operator<<(
  std::ostream&                     os,
  const lmp::obj::ccid::ClassType&  cType)
{
  switch(cType)
  {
    case lmp::obj::ccid::ClassType::LocalCCId:
	  os << "LocalCCId";
	  break;
    case lmp::obj::ccid::ClassType::RemoteCCId:
  	  os << "RemoteCCId";
  	  break;
  }
  return os;
}