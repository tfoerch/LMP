#ifndef OBJ_BYTE_SEQUENCE_DEF_HPP_
#define OBJ_BYTE_SEQUENCE_DEF_HPP_
/*
 * ByteSequence_def.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "obj/ByteSequence.hpp"
#include <boost/spirit/include/qi_binary.hpp>
#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/spirit/include/phoenix_fusion.hpp>
#include <boost/spirit/include/phoenix_stl.hpp>
#include <boost/phoenix/object/static_cast.hpp>

#include <type_traits>

namespace lmp
{
  namespace obj
  {
    namespace parse
    {
      namespace fusion = boost::fusion;
      namespace phoenix = boost::phoenix;
      namespace qi = boost::spirit::qi;

      template <typename Iterator>
      byte_sequence_grammar<Iterator>::byte_sequence_grammar()
	  : byte_sequence_grammar::base_type(byte_sequence, "byte_sequence")
      {
        using qi::byte_;
        // using qi::repeat;
        using qi::eps;
        // using qi::lazy;
        using qi::_a;
        using qi::_1;
        // using phoenix::at_c;
        using phoenix::push_back;
        using namespace qi::labels;

        byte_sequence =
            ( eps(_r1 > 1)
              >> byte_sequence(_r1 - 1) [ _val = _1 ]
              >> byte_ [ push_back(_val, _1) ] ) |
            byte_ [ push_back(_val, _1) ];


        byte_sequence.name("byte_sequence");
      }
    } // namespace parse
    namespace generate
    {
      namespace fusion = boost::fusion;
      namespace phoenix = boost::phoenix;
      namespace qi = boost::spirit::qi;

      template <typename OutputIterator>
      byte_sequence_grammar<OutputIterator>::byte_sequence_grammar()
      : byte_sequence_grammar::base_type(byte_sequence, "byte_sequence")
      {
        using qi::byte_;
        using phoenix::at_c;
        using namespace qi::labels;

        byte_sequence =
            *byte_
            ;

        byte_sequence.name("byte_sequence");
      }
    }
  } // namespace obj
} // namespace lmp

#endif /* OBJ_BYTE_SEQUENCE_DEF_HPP_ */
