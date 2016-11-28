#ifndef LMP_OBJ_UNKNOWN_OBJECT_CLASS_HPP_
#define LMP_OBJ_UNKNOWN_OBJECT_CLASS_HPP_
/*
 * UnknownObjectClass.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "obj/ObjectClass.hpp"
#include "obj/ObjectHeader.hpp"
#include "obj/ByteSequence.hpp"
#include "obj/ObjectClassTypeTraits.hpp"
#include "obj/ObjectClassType.hpp"
#include "obj/ControlChannelIdTypeTraits.hpp"
#include "obj/ControlChannelIdIF.hpp"
#include "obj/ControlChannelIdData.hpp"

#include <boost/spirit/include/qi.hpp>

namespace lmp
{
  namespace obj
  {
    struct UnknownObjectClassData
	{
      lmp::obj::ObjectHeaderData  m_header;
      ByteSequence                m_data;
	};
    std::ostream& operator<<(
      std::ostream&                  os,
	  const UnknownObjectClassData&  unknownObjectClass);
    namespace parse
	{
      namespace qi = boost::spirit::qi;
      template <typename Iterator>
      struct unknown_object_class_grammar : qi::grammar<Iterator, UnknownObjectClassData()>
      {
    	unknown_object_class_grammar();

    	lmp::obj::parse::object_header_unknown_object_class_grammar<Iterator>  object_header;
    	lmp::obj::parse::byte_sequence_grammar<Iterator>                       byte_sequence;
    	qi::rule<Iterator, UnknownObjectClassData()>                           unknown_object_class_rule;
      };
	}
  } // namespace obj
} // namespace lmp

#endif /* LMP_OBJ_UNKNOWN_OBJECT_CLASS_HPP_ */
