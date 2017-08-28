#ifndef OBJ_BYTE_SEQUENCE_DEF_HPP_
#define OBJ_BYTE_SEQUENCE_DEF_HPP_
/*
 * ByteSequence_def.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "obj/ByteSequence.hpp"
//#include <boost/spirit/home/x3/support/utility/annotate_on_success.hpp>
//#include <boost/spirit/home/x3/binary/binary.hpp>

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
#if 0
      namespace x3 = boost::spirit::x3;
      using x3::byte_;
      // using qi::repeat;
      using x3::eps;
      // using qi::lazy;
      using x3::_val;
      using x3::_attr;
      //using x3::_1;

      ///////////////////////////////////////////////////////////////////////////
      // Rule IDs
      ///////////////////////////////////////////////////////////////////////////

      struct byte_sequence_class;
      struct recursive_byte_seq_class;

      ///////////////////////////////////////////////////////////////////////////
      // Rules
      ///////////////////////////////////////////////////////////////////////////

      x3::rule<byte_sequence_class, ByteSequence> const
        byte_sequence_value = "ByteSequence";

      x3::rule<recursive_byte_seq_class, ByteSequence> const
        recursive_byte_seq_value = "ByteSequence";

      byte_sequence_type const byte_sequence = "ByteSequence";


      ///////////////////////////////////////////////////////////////////////////
      // Grammar
      ///////////////////////////////////////////////////////////////////////////

      auto const byte_sequence_value_def =
        byte_ [ push_back(_val(ctx), _1) ]
        >> ( eps(_r1 > 1)
             >> recursive_byte_seq(_val(ctx), _r1 - 1) ) |
           eps(true)
        ;

      auto const recursive_byte_seq_def =
        byte_ [ push_back(_r1, _1) ]
        >> ( eps(_r2 > 1)
             >> recursive_byte_seq(_r1, _r2 - 1) ) |
           eps(true)
      ;

      BOOST_SPIRIT_DEFINE(byte_sequence_value, recursive_byte_seq_def);
#endif

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
            byte_ [ push_back(_val, _1) ]
            >> ( eps(_r1 > 1)
                 >> recursive_byte_seq(_val, _r1 - 1) ) |
                 eps(true)
            ;

        recursive_byte_seq =
            byte_ [ push_back(_r1, _1) ]
            >> ( eps(_r2 > 1)
                 >> recursive_byte_seq(_r1, _r2 - 1) ) |
               eps(true)
            ;

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
