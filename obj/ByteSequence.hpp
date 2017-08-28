#ifndef OBJ_BYTE_SEQUENCE_HPP_
#define OBJ_BYTE_SEQUENCE_HPP_
/*
 * ByteSequence.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "base/ProtocolTypes.hpp"
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/karma.hpp>

//#include <boost/spirit/home/x3.hpp>
#include <vector>

namespace lmp
{
  namespace obj
  {
    typedef std::vector<lmp::BYTE>  ByteSequence;
    namespace hex_stream
    {
      std::ostream& operator<<(
        std::ostream&        os,
        const ByteSequence&  byteSequence);
    }
    namespace parse
    {
      namespace qi = boost::spirit::qi;
      //namespace x3 = boost::spirit::x3;
#if 0
      struct byte_sequence_class;
      typedef
         x3::rule<byte_sequence_class, ByteSequence>  byte_sequence_type;
      BOOST_SPIRIT_DECLARE(byte_sequence_type);
#endif
      template <typename Iterator>
      struct byte_sequence_grammar : qi::grammar<Iterator, ByteSequence(lmp::WORD)>
      {
    	byte_sequence_grammar();

        qi::rule<Iterator, ByteSequence(lmp::WORD)>         byte_sequence;
        qi::rule<Iterator, void(ByteSequence&, lmp::WORD)>  recursive_byte_seq;
      };
    } // namespace parse

    namespace generate
    {
      namespace karma = boost::spirit::karma;
      template <typename OutputIterator>
      struct byte_sequence_grammar : karma::grammar<OutputIterator, ByteSequence()>
      {
        byte_sequence_grammar();

        karma::rule<OutputIterator, ByteSequence()>  byte_sequence;
      };
    }
//    parse::byte_sequence_type const& byte_sequence();

  } // namespace obj
} // namespace lmp

#endif /* OBJ_BYTE_SEQUENCE_HPP_ */
