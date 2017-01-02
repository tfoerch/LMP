/*
 * ObjectSequence.cpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "obj/ObjectSequence_def.hpp"

#include <boost/asio/buffer.hpp>
#include <boost/asio/buffers_iterator.hpp>

typedef boost::asio::buffers_iterator<boost::asio::const_buffers_1>  BufIterType;
template struct lmp::obj::parse::object_sequence_grammar<BufIterType>;

std::ostream& lmp::obj::operator<<(
  std::ostream&             os,
  const lmp::obj::ObjectSequence&  objectSequence)
{
  for (std::vector<lmp::obj::Objects>::const_iterator iter = objectSequence.m_objects.begin();
       iter != objectSequence.m_objects.end();
       ++iter)
  {
    if (iter != objectSequence.m_objects.begin())
    {
      os << ", ";
    }
    os << *iter;
  }
  return os;
}
