#ifndef LMP_MSG_HELLO_HPP_
#define LMP_MSG_HELLO_HPP_
/*
 * Config.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "obj/Hello.hpp"
#include "CommonHeader.hpp"
#include "base/ProtocolTypes.hpp"                  // for DWORD
#include <boost/spirit/include/qi.hpp>

namespace lmp
{
  namespace msg
  {
    struct HelloMsg
    {
      lmp::BYTE                          m_flags;
      lmp::obj::hello::HelloData         m_hello;
    };
    std::ostream& operator<<(
      std::ostream&        os,
      const HelloMsg&      hello);
    bool operator==(
      const HelloMsg&  first,
      const HelloMsg&  second);
    lmp::DWORD getLength(
      const HelloMsg&  hello);
    namespace parse
    {
      namespace qi = boost::spirit::qi;
      template <typename Iterator>
      struct hello_grammar : qi::grammar<Iterator, HelloMsg(CommonHeader)>
      {
    	hello_grammar();

        lmp::obj::parse::object_class_grammar<Iterator,
                                              lmp::obj::hello::ClassType,
                                              lmp::obj::hello::ClassType::Hello>   hello;
    	qi::rule<Iterator, HelloMsg(CommonHeader)>                                 hello_rule;
      };
    }
  } // namespace msg
} // namespace lmp

#endif /* LMP_MSG_HELLO_HPP_ */
