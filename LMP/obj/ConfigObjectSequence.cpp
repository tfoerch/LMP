/*
 * ConfigObjectSequence.cpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "obj/ConfigObjectSequence_def.hpp"

#include <boost/asio/buffer.hpp>
#include <boost/asio/buffers_iterator.hpp>

typedef boost::asio::buffers_iterator<boost::asio::const_buffers_1>  BufIterType;
template struct lmp::obj::config::parse::config_object_sequence_grammar<BufIterType>;

std::ostream& lmp::obj::config::operator<<(
  std::ostream&                                  os,
  const lmp::obj::config::ConfigObjectSequence&  configObjectSequence)
{
  for (std::vector<lmp::obj::config::ConfigCTypes>::const_iterator iter = configObjectSequence.begin();
       iter != configObjectSequence.end();
       ++iter)
  {
    if (iter != configObjectSequence.begin())
    {
      os << ", ";
    }
    os << *iter;
  }
  return os;
}
