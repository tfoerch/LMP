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

namespace lmp
{
  namespace obj
  {
    struct ObjectSequence
    {
      std::vector<lmp::obj::Objects>   m_objects;
    };
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
  } // namespace obj
} // namespace lmp

#endif /* LMP_OBJ_OBJECTSEQUENCE_HPP_ */
