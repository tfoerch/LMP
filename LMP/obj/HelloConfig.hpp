#ifndef LMP_OBJ_HELLOCONFIG_HPP_
#define LMP_OBJ_HELLOCONFIG_HPP_
/*
 * HelloConfig.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include <ProtocolTypes.hpp>                  // for WORD
#include <LMPObjectIF.hpp>

namespace lmp
{
  namespace obj
  {
    class HelloConfig : public LMPObjectIF
	{
	public:
      HelloConfig(
    	lmp::WORD  helloIntv,
		lmp::WORD  helloDeadIntv);
      inline lmp::WORD getHelloIntv() const { return m_helloIntv; }
      inline lmp::WORD getHelloDeadIntv() const { return m_helloDeadIntv; }
    private:
      virtual lmp::BYTE do_getClassType() const;
      virtual bool do_isNegotiable() const;
      virtual const otype::ObjectClass do_getObjectClass() const;
      virtual lmp::WORD do_getContentsLength() const;
      virtual ObjectHeader::OptEncError do_encodeContents(
    	boost::asio::mutable_buffer&  buffer) const;
  	  lmp::WORD  m_helloIntv;
      lmp::WORD  m_helloDeadIntv;
      static const lmp::BYTE c_helloConfigClassType;
      static const lmp::WORD c_contentsLength;
	};
  } // namespace obj
} // namespace lmp

#endif /* LMP_OBJ_HELLOCONFIG_HPP_ */
