#ifndef LMP_OBJ_UNKNOWN_CC_ID_HPP_
#define LMP_OBJ_UNKNOWN_CC_ID_HPP_
/*
 * UnknownCCIdCType.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "obj/ObjectClass.hpp"
#include "obj/ObjectHeader.hpp"
#include "obj/ByteSequence.hpp"
#include "obj/ControlChannelIdClass.hpp"
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
	namespace ccid
	{
	  struct UnknownCCIdCTypeData
	  {
		lmp::obj::parse::ObjectHeaderUnknownCTypeOutput  m_header;
		ByteSequence                                     m_data;
	  };
      std::ostream& operator<<(
        std::ostream&                os,
  	    const UnknownCCIdCTypeData&  unknownCCIdCType);
	  namespace parse
	  {
	    namespace qi = boost::spirit::qi;
	    template <typename Iterator>
        struct unknown_control_channel_id_grammar : qi::grammar<Iterator, UnknownCCIdCTypeData()>
        {
          unknown_control_channel_id_grammar();

		  lmp::obj::parse::object_header_unknown_class_type_grammar<Iterator>  object_header;
	      lmp::obj::parse::byte_sequence_grammar<Iterator>                     byte_sequence;
      	  qi::rule<Iterator, UnknownCCIdCTypeData()>                           unknown_control_channel_id_rule;
        };
	  }
	}
  } // namespace obj
} // namespace lmp

#endif /* LMP_OBJ_UNKNOWN_CC_ID_HPP_ */
