/*
 * ByteSequence.cpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "obj/ByteSequence_def.hpp"

#include <boost/asio/buffer.hpp>
#include <boost/asio/buffers_iterator.hpp>

#include <iomanip>

typedef boost::asio::buffers_iterator<boost::asio::const_buffers_1>  BufIterType;
template struct lmp::obj::parse::byte_sequence_grammar<BufIterType>;

std::ostream& lmp::obj::hex_stream::operator<<(
    std::ostream&        os,
	const ByteSequence&  byteSequence)
{
  os << "'" << std::hex;
  for (ByteSequence::const_iterator iter = byteSequence.begin();
	   iter != byteSequence.end();
	   ++iter)
  {
    if (iter != byteSequence.begin())
    {
      os << " ";
    }
    os << std::setw(2) << std::setfill('0') << static_cast<lmp::WORD>(*iter);
  }
  os << "'" << std::dec;
  return os;
}
