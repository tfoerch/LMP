/*
 * ObjectClass.cpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "obj/ObjectClass_def.hpp"

std::ostream& lmp::obj::operator<<(
  std::ostream&                 os,
  const lmp::obj::ObjectClass&  objClass)
{
  switch(objClass)
  {
    case lmp::obj::ObjectClass::ControlChannelID:
      os << "ControlChannelID";
      break;
    case lmp::obj::ObjectClass::NodeID:
      os << "NodeID";
      break;
    case lmp::obj::ObjectClass::LinkID:
      os << "LinkID";
      break;
    case lmp::obj::ObjectClass::InterfaceID:
      os << "InterfaceID";
      break;
    case lmp::obj::ObjectClass::MessageID:
      os << "MessageID";
      break;
    case lmp::obj::ObjectClass::Config:
      os << "Config";
      break;
    case lmp::obj::ObjectClass::Hello:
      os << "Hello";
      break;
  }
  return os;
}
