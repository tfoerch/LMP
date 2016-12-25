/*
 * ObjectClass.cpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "obj/ObjectClass_def.hpp"
#include "obj/ControlChannelIdTypeTraits.hpp"
#include "obj/ConfigTypeTraits.hpp"
#include <boost/asio/buffer.hpp>
#include <boost/asio/buffers_iterator.hpp>

typedef boost::asio::buffers_iterator<boost::asio::const_buffers_1>  BufIterType;
template struct lmp::obj::parse::control_channel_id_object_class_grammar<BufIterType>;
template struct lmp::obj::parse::node_id_object_class_grammar<BufIterType>;
template struct lmp::obj::parse::link_id_object_class_grammar<BufIterType>;
template struct lmp::obj::parse::interface_id_object_class_grammar<BufIterType>;
template struct lmp::obj::parse::message_id_object_class_grammar<BufIterType>;
template struct lmp::obj::parse::config_object_class_grammar<BufIterType>;
template struct lmp::obj::parse::hello_object_class_grammar<BufIterType>;
typedef boost::asio::buffers_iterator<boost::asio::mutable_buffers_1>  BufOutIterType;
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
