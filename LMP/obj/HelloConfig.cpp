/*
 * HelloConfig.cpp
 *
 *  Created on: 20.02.2015
 *      Author: tom
 */

#include "HelloConfig.hpp"

namespace lmp
{
  namespace obj
  {
    const lmp::BYTE HelloConfig::c_helloConfigClassType = 1;
    const lmp::WORD HelloConfig::c_contentsLength = 8;

    HelloConfig::HelloConfig(
      lmp::WORD  helloIntv,
	  lmp::WORD  helloDeadIntv)
    : m_helloIntv(helloIntv),
	  m_helloDeadIntv(helloDeadIntv)
    {}
    lmp::BYTE HelloConfig::do_getClassType() const
    {
      return c_helloConfigClassType;
    }
    bool HelloConfig::do_isNegotiable() const
    {
      return true;
    }
    const otype::ObjectClass HelloConfig::do_getObjectClass() const
    {
      return otype::Config;
    }
    lmp::WORD HelloConfig::do_getContentsLength() const
    {
      return c_contentsLength;
    }
    ObjectHeader::OptEncError HelloConfig::do_encodeContents(
  	boost::asio::mutable_buffer&  buffer) const
    {

    }
  } // namespace obj
} // namespace lmp
