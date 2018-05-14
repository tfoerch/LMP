#ifndef LMP_OBJ_OBJECTHEADER_GENERATOR_HPP_
#define LMP_OBJ_OBJECTHEADER_GENERATOR_HPP_
/*
 * ObjectHeaderGenerator.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "obj/ObjectHeaderAst.hpp"
#include <boost/spirit/include/karma.hpp>
#include <iostream>

namespace lmp
{
  namespace obj
  {
    template <typename OutputIterator, typename ClassType, ClassType ctype>
    struct ObjectHeaderTypeGenerateTraits
    {
    };
    namespace generator
    {
      template<typename HeaderCTypeTraits>
      struct GetLength
      {
        template<typename> struct result { typedef lmp::WORD type; };
        lmp::WORD operator()(
          const ast::ObjectHeader<HeaderCTypeTraits>& objHeader) const
        {
          return getLength(objHeader);
        }
      };

      namespace karma = boost::spirit::karma;
      template <typename OutputIterator, typename ClassType, ClassType ctype>
      struct object_header_grammar : karma::grammar<OutputIterator, ast::ObjectHeader<HeaderCTypeTraits<ClassType, ctype>>()>
      {
        object_header_grammar();

        boost::phoenix::function<GetLength<HeaderCTypeTraits<ClassType, ctype>>>                 phx_getLength;
        karma::rule<OutputIterator, ast::ObjectHeader<HeaderCTypeTraits<ClassType, ctype>>()>  object_header_rule;
      };
    }
  } // namespace obj
} // namespace lmp

#endif /* LMP_OBJ_OBJECTHEADER_GENERATOR_HPP_ */
