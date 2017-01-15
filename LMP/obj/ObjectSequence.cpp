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

lmp::DWORD lmp::obj::getLength(
  const lmp::obj::ObjectSequence&  objectSequence)
{
  lmp::DWORD length = 0;
  for (std::vector<lmp::obj::Objects>::const_iterator iter = objectSequence.begin();
       iter != objectSequence.end();
       ++iter)
  {
    length += lmp::obj::getLength(*iter);
  }
  return length;
}

std::ostream& lmp::obj::operator<<(
  std::ostream&             os,
  const lmp::obj::ObjectSequence&  objectSequence)
{
  for (std::vector<lmp::obj::Objects>::const_iterator iter = objectSequence.begin();
       iter != objectSequence.end();
       ++iter)
  {
    if (iter != objectSequence.begin())
    {
      os << ", ";
    }
    os << *iter;
  }
  return os;
}
