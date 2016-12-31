/*
 * UnknownObjectClass.cpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "obj/UnknownObjectClass_def.hpp"

#include <boost/asio/buffer.hpp>
#include <boost/asio/buffers_iterator.hpp>

typedef boost::asio::buffers_iterator<boost::asio::const_buffers_1>  BufIterType;
template struct lmp::obj::parse::unknown_object_class_grammar<BufIterType>;

std::ostream& lmp::obj::operator<<(
  std::ostream&                            os,
  const lmp::obj::UnknownObjectClassData&  unknownObjectClass)
{
  using lmp::obj::hex_stream::operator<<;

  os << static_cast<lmp::WORD>(unknownObjectClass.m_object_class) << ", "
	 << static_cast<lmp::WORD>(unknownObjectClass.m_class_type) << ", "
	 << (unknownObjectClass.m_negotiable ? "negotiable" : "not negotiable") << ", "
	 << unknownObjectClass.m_length << ", "
	 << unknownObjectClass.m_data;
  return os;
}
