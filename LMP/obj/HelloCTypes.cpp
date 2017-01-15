/*
 * HelloCTypes.cpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "obj/HelloCTypes_def.hpp"

#include <boost/asio/buffer.hpp>
#include <boost/asio/buffers_iterator.hpp>

typedef boost::asio::buffers_iterator<boost::asio::const_buffers_1>  BufIterType;
template struct lmp::obj::hello::parse::hello_ctypes_grammar<BufIterType>;

namespace
{
  struct HelloCTypes_GetLengthVisitor : boost::static_visitor<lmp::DWORD>
  {
    lmp::DWORD operator()(const lmp::obj::hello::HelloData& hello) const
    {
      return lmp::obj::getLength(hello);
    }
    lmp::DWORD operator()(const lmp::obj::hello::UnknownHelloCTypeData& unknownHello) const
    {
      return lmp::obj::getLength(unknownHello);
    }
  };
  struct HelloCTypes_Printer : boost::static_visitor<std::ostream&>
  {
    HelloCTypes_Printer(std::ostream& os)
    : m_os(os)
    {}
    std::ostream& operator()(const lmp::obj::hello::HelloData& hello) const
    {
      m_os << hello;
      return m_os;
    }
    std::ostream& operator()(const lmp::obj::hello::UnknownHelloCTypeData& unknownHello) const
    {
      m_os << unknownHello;
      return m_os;
    }
    std::ostream&   m_os;
  };
}

lmp::DWORD lmp::obj::hello::getLength(
  const lmp::obj::hello::HelloCTypes&  helloCType)
{
  return boost::apply_visitor(HelloCTypes_GetLengthVisitor(), helloCType);
}

std::ostream& lmp::obj::hello::operator<<(
  std::ostream&                        os,
  const lmp::obj::hello::HelloCTypes&  helloCTypes)
{
  boost::apply_visitor(HelloCTypes_Printer(os), helloCTypes);
  return os;
}
