#ifndef LMP_OBJ_HELLO_CTYPES_HPP_
#define LMP_OBJ_HELLO_CTYPES_HPP_
/*
 * HelloCTypes.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "obj/Hello.hpp"
#include "obj/UnknownHelloCType.hpp"

#include <boost/variant.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/karma.hpp>

namespace lmp
{
  namespace obj
  {
    namespace hello
    {
      typedef boost::variant<lmp::obj::hello::HelloData,
                             lmp::obj::hello::UnknownHelloCTypeData>   HelloCTypes;
      lmp::DWORD getLength(
        const HelloCTypes&  helloCTypes);
      std::ostream& operator<<(
        std::ostream&       os,
        const HelloCTypes&  helloCTypes);
      namespace parse
      {
        namespace qi = boost::spirit::qi;
        template <typename Iterator>
        struct hello_ctypes_grammar : qi::grammar<Iterator, HelloCTypes()>
        {
          hello_ctypes_grammar();

          lmp::obj::parse::object_class_grammar<Iterator,
                                                lmp::obj::hello::ClassType,
                                                lmp::obj::hello::ClassType::Hello>           hello;
          lmp::obj::parse::object_class_unknown_ctype_grammar<Iterator,
                                                              lmp::obj::ObjectClass::Hello>  unknown_hello_ctype;
          qi::rule<Iterator, HelloCTypes()>                                                  hello_ctypes_rule;
        };
      }
      namespace generate
      {
        namespace karma = boost::spirit::karma;
        template <typename OutputIterator>
        struct hello_ctypes_grammar : karma::grammar<OutputIterator, HelloCTypes()>
        {
          hello_ctypes_grammar();

          lmp::obj::generate::object_class_grammar<OutputIterator,
                                                   lmp::obj::hello::ClassType,
                                                   lmp::obj::hello::ClassType::Hello>     hello;
          lmp::obj::generate::object_class_unknown_ctype_grammar<OutputIterator,
                                                                 lmp::obj::ObjectClass::Hello>  unknown_hello_ctype;
          karma::rule<OutputIterator, HelloCTypes()>                                            hello_ctypes_rule;
        };
      }
    }
  } // namespace obj
} // namespace lmp

#endif /* LMP_OBJ_HELLO_CTYPES_HPP_ */
