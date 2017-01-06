#ifndef LMP_OBJ_HELLO_HPP_
#define LMP_OBJ_HELLO_HPP_
/*
 * Hello.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "obj/ObjectClass.hpp"
#include "obj/HelloClass.hpp"

#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/karma.hpp>

#include <iostream>

namespace lmp
{
  namespace obj
  {
    namespace hello
    {
      struct HelloBody
      {
        lmp::DWORD   m_txSeqNum;
        lmp::DWORD   m_rcvSeqNum;
      };
      std::ostream& operator<<(
        std::ostream&      os,
        const HelloBody&   hello);
      struct IsEqualFtor
      {
        bool operator()(
          const HelloBody& first,
          const HelloBody& second) const;
      };
      struct GetLengthFtor
      {
        lmp::WORD operator()(
          const HelloBody&  hello) const;
        static const lmp::WORD c_length;
      };
      namespace parse
      {
        namespace qi = boost::spirit::qi;
        template <typename Iterator>
        struct hello_body_grammar : qi::grammar<Iterator, HelloBody()>
        {
          hello_body_grammar();

          qi::rule<Iterator, HelloBody()>                         hello_body_rule;
        };
      }
      namespace generate
      {
        namespace karma = boost::spirit::karma;
        template <typename OutputIterator>
        struct hello_body_grammar : karma::grammar<OutputIterator, HelloBody()>
        {
          hello_body_grammar();

          karma::rule<OutputIterator, HelloBody()>                hello_body_rule;
        };
      }
    }
    template <>
    struct ObjectClassTypeTraits<hello::ClassType, hello::ClassType::Hello>
    {
      typedef typename hello::ClassType      ctype_type;
      typedef typename hello::HelloBody      data_type;
      typedef typename hello::IsEqualFtor    equal_ftor_type;
      typedef typename hello::GetLengthFtor  get_length_ftor_type;
      static const ctype_type                ctype = hello::ClassType::Hello;
    };
    template <typename Iterator>
    struct ObjectClassTypeParseTraits<Iterator, hello::ClassType, hello::ClassType::Hello>
    {
      typedef hello::parse::hello_body_grammar<Iterator>  grammar_type;
    };
    template <typename OutputIterator>
    struct ObjectClassTypeGenerateTraits<OutputIterator, hello::ClassType, hello::ClassType::Hello>
    {
      typedef hello::generate::hello_body_grammar<OutputIterator>  grammar_type;
    };
    namespace hello
    {
      typedef ObjectClassTypeData<ObjectClassTypeTraits<hello::ClassType,
                                                        hello::ClassType::Hello>>  HelloData;
      const lmp::WORD helloLength = c_objHeaderLength + 4 + 4;
    }
  } // namespace obj
} // namespace lmp

#endif /* LMP_OBJ_HELLO_HPP_ */
