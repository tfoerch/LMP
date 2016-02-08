#ifndef LMP_OBJ_HELLOCONFIGDATA_HPP_
#define LMP_OBJ_HELLOCONFIGDATA_HPP_
/*
 * HelloConfigData.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "base/ProtocolTypes.hpp"                  // for WORD
#include "obj/LMPObjectIF.hpp"

namespace lmp
{
  namespace obj
  {
    class HelloConfigData
	{
	public:
      typedef boost::optional<HelloConfigData>                       opt_data_type;
      typedef std::pair<opt_data_type, ObjectHeader::OptDecError>    DataTypeDecodingResult;
      HelloConfigData(
    	lmp::WORD  helloIntv,
		lmp::WORD  helloDeadIntv);
      inline lmp::WORD getHelloIntv() const { return m_helloIntv; }
      inline lmp::WORD getHelloDeadIntv() const { return m_helloDeadIntv; }
      bool isNegotiable() const { return true; }
      static lmp::WORD getContentsLength() { return c_contentsLength; }
      ObjectHeader::OptEncError encode(
    	boost::asio::mutable_buffer&  buffer) const;
      static DataTypeDecodingResult decode(
    	boost::asio::const_buffer&    buffer);
	private:
  	  lmp::WORD  m_helloIntv;
      lmp::WORD  m_helloDeadIntv;
      static const lmp::WORD c_contentsLength;
	};
  } // namespace obj
} // namespace lmp

#endif /* LMP_OBJ_HELLOCONFIGDATA_HPP_ */
