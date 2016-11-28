#ifndef LMP_MSG_COMMONHEADER_DEF_HPP_
#define LMP_MSG_COMMONHEADER_DEF_HPP_
/*
 * CommonHeader_def.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "CommonHeader.hpp"
#include <boost/spirit/include/qi_binary.hpp>
#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/spirit/include/phoenix_fusion.hpp>
#include <boost/spirit/include/phoenix_stl.hpp>
#include <boost/spirit/include/karma_attr_cast.hpp>
#include <boost/phoenix/object/static_cast.hpp>
#include <boost/fusion/adapted/struct/adapt_struct.hpp>
#include <boost/fusion/include/adapt_struct.hpp>

//BOOST_FUSION_ADAPT_STRUCT(
//  lmp::msg::parse::CommonHeaderInput,
//  (lmp::BYTE,       m_version)
//  (lmp::BYTE,       m_msg_type)
//)
//
//BOOST_FUSION_ADAPT_STRUCT(
//  lmp::msg::parse::CommonHeaderOutput,
//  (lmp::BYTE,       m_flags)
//  (lmp::WORD,       m_length)
//)
//
//BOOST_FUSION_ADAPT_STRUCT(
//  lmp::msg::parse::CommonHeaderUnknownMessageInput,
//  (lmp::BYTE,       m_version)
//)

BOOST_FUSION_ADAPT_STRUCT(
  lmp::msg::parse::CommonHeaderOutput,
  (lmp::BYTE,       m_flags)
  (lmp::BYTE,       m_msg_type)
  (lmp::WORD,       m_length)
)


namespace lmp
{
  namespace msg
  {
    namespace parse
	{
      namespace fusion = boost::fusion;
      namespace phoenix = boost::phoenix;
      namespace qi = boost::spirit::qi;

//      template <typename Iterator>
//      common_header_grammar<Iterator>::common_header_grammar()
//	  : common_header_grammar<Iterator>::base_type(common_header_rule, "common_header")
//	  {
//        using qi::byte_;
//        using qi::big_word;
//        using phoenix::at_c;
//        using namespace qi::labels;
//
//        common_header_rule =
//            byte_(at_c<0>(_r1))                // version
//		    >> byte_  [ at_c<0>(_val) = _1 ]   // flags
//			>> byte_	                       // reserved
//		    >> byte_(at_c<1>(_r1))             // msg type
//		    >> big_word [ at_c<1>(_val) = _1 ] // length
//		    >> big_word                        // reserved
//		    ;
//
//        common_header_rule.name("common_header");
//	  }
      template <typename Iterator>
      common_header_grammar<Iterator>::common_header_grammar()
	  : common_header_grammar<Iterator>::base_type(common_header_rule, "common_header")
	  {
        using qi::byte_;
        using qi::big_word;
        using qi::_a;
        using qi::_1;
        using phoenix::at_c;
        using namespace qi::labels;

        common_header_rule =
                byte_(_r1)                           // version
    		    >> byte_    [ at_c<0>(_val) = _1 ]  // flags
				>> byte_	                        // reserved
    		    >> byte_    [ at_c<1>(_val) = _1 ]  // msg type
    		    >> big_word [ at_c<2>(_val) = _1 ]  // length
    		    >> big_word                         // reserved
    		    ;

        common_header_rule.name("common_header");
	  }
	} // namespace parse
  } // namespace msg
} // namespace lmp

#endif /* LMP_MSG_COMMONHEADER_DEF_HPP_ */
