#ifndef LMP_OBJ_OBJECTSEQUENCE_HPP_
#define LMP_OBJ_OBJECTSEQUENCE_HPP_
/*
 * ObjectSequence.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "obj/Objects.hpp"

#include <boost/variant.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/karma.hpp>

namespace lmp
{
  namespace obj
  {
    typedef  std::vector<lmp::obj::Objects>   ObjectSequence;
//    bool operator==(
//      const ObjectSequence&  first,
//      const ObjectSequence&  second);
    lmp::DWORD getLength(
      const ObjectSequence&  objectSequence);
    std::ostream& operator<<(
      std::ostream&          os,
      const ObjectSequence&  objectSequence);
    namespace parse
    {
      namespace qi = boost::spirit::qi;
      template <typename Iterator>
      struct object_sequence_grammar : qi::grammar<Iterator, ObjectSequence(lmp::WORD)>
      {
        object_sequence_grammar();

        lmp::obj::parse::objects_grammar<Iterator>      objects;
        qi::rule<Iterator, ObjectSequence(lmp::WORD)>   object_sequence;
      };
    }
    namespace generate
    {
      namespace karma = boost::spirit::karma;
      template <typename OutputIterator>
      struct object_sequence_grammar : karma::grammar<OutputIterator, ObjectSequence()>
      {
        object_sequence_grammar();

        lmp::obj::generate::objects_grammar<OutputIterator>   objects;
        karma::rule<OutputIterator, ObjectSequence()>         object_sequence;
      };
    }
  } // namespace obj
} // namespace lmp

#endif /* LMP_OBJ_OBJECTSEQUENCE_HPP_ */
