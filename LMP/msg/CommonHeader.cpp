/*
 * CommonHeader.cpp
 *
 *  Created on: 20.02.2015
 *      Author: tom
 */

#include "CommonHeader_def.hpp"
#include <boost/asio/buffer.hpp>
#include <boost/asio/buffers_iterator.hpp>
#include <boost/endian/conversion.hpp>
#include <iostream>

typedef boost::asio::buffers_iterator<boost::asio::const_buffers_1>  BufIterType;
template struct lmp::msg::parse::common_header_grammar<BufIterType>;
typedef boost::asio::buffers_iterator<boost::asio::mutable_buffers_1>  BufOutIterType;
template struct lmp::msg::generate::common_header_grammar<BufOutIterType>;

namespace lmp
{
  namespace msg
  {
    lmp::DWORD getLength(
      const CommonHeader&  commonHeader)
    {
      return c_headerLength;
    }
    bool operator==(
      const CommonHeader&  first,
      const CommonHeader&  second)
    {
      return
        ( first.m_flags == second.m_flags &&
          first.m_msg_type == second.m_msg_type &&
          first.m_length == second.m_length );
    }
    std::ostream& operator<<(
      std::ostream&        os,
      const CommonHeader&  commonHeader)
    {
      os << static_cast<lmp::WORD>(commonHeader.m_flags) << ", "
         << static_cast<lmp::WORD>(commonHeader.m_msg_type) << ", "
         << commonHeader.m_length;
      return os;
    }
  } // namespace msg
} // namespace lmp
