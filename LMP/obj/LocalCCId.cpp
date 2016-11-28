/*
 * LocalCCId.cpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "obj/LocalCCId_def.hpp"

#include <boost/asio/buffer.hpp>
#include <boost/asio/buffers_iterator.hpp>

typedef boost::asio::buffers_iterator<boost::asio::const_buffers_1>  BufIterType;
typedef boost::asio::buffers_iterator<boost::asio::mutable_buffers_1>  BufOutIterType;
template struct lmp::obj::ccid::parse::local_control_channel_id_grammar<BufIterType>;
template struct lmp::obj::ccid::generate::local_control_channel_id__grammar<BufOutIterType>;

std::ostream& lmp::obj::ccid::operator<<(
  std::ostream&                         os,
  const lmp::obj::ccid::LocalCCIdData&  localCCId)
{
  os << (localCCId.m_negotiable ? "negotiable" : "not negotiable") << ", "
	 << localCCId.m_CCId;
  return os;
}
