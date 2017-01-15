#ifndef LMP_MSG_COMMONHEADER_HPP_
#define LMP_MSG_COMMONHEADER_HPP_
/*
 * CommonHeader.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "base/ProtocolTypes.hpp"                  // for DWORD
#include "msg/MsgType.hpp"

#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/karma.hpp>

namespace lmp
{
  namespace msg
  {
    struct CommonHeader
    {
      lmp::BYTE               m_flags;
      lmp::BYTE               m_msg_type;
      lmp::WORD               m_length;
    };
    const lmp::WORD  c_headerLength = 8;
    const lmp::BYTE  c_versionMask = 0xf0;
    const lmp::BYTE  c_supportedVersion = 1;
    const lmp::BYTE  c_controlChannelDownMask = 0x01;
    const lmp::BYTE  c_lmpRestartMask = 0x02;

    bool operator==(
      const CommonHeader&  first,
      const CommonHeader&  second);
    lmp::DWORD getLength(
      const CommonHeader&  commonHeader);
    std::ostream& operator<<(
      std::ostream&        os,
      const CommonHeader&  commonHeader);
    namespace parse
    {
      namespace qi = boost::spirit::qi;
      template <typename Iterator>
      struct common_header_grammar : qi::grammar<Iterator, CommonHeader()>
      {
    	common_header_grammar();

        qi::rule<Iterator, CommonHeader()>   common_header_rule;
      };
    }
    namespace generate
    {
      namespace karma = boost::spirit::karma;
      template <typename OutputIterator>
      struct common_header_grammar : karma::grammar<OutputIterator, CommonHeader()>
      {
        common_header_grammar();
        karma::rule<OutputIterator, CommonHeader()>      common_header_rule;
      };
    }
  } // namespace msg
} // namespace lmp

#endif /* LMP_MSG_COMMONHEADER_HPP_ */
