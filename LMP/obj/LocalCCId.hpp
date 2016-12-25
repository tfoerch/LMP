#ifndef LMP_OBJ_LOCAL_CC_ID_HPP_
#define LMP_OBJ_LOCAL_CC_ID_HPP_
/*
 * LocalCCId.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "obj/ObjectClass.hpp"
#include "obj/ObjectHeader.hpp"
#include "obj/ControlChannelIdClass.hpp"
#include "obj/ObjectClassTypeTraits.hpp"
#include "obj/ObjectClassType.hpp"
#include "obj/ControlChannelIdTypeTraits.hpp"
#include "obj/ControlChannelIdIF.hpp"
#include "obj/ControlChannelIdData.hpp"

#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/karma.hpp>

namespace lmp
{
  namespace obj
  {
    typedef ObjectClassType<ccid::ClassType, ccid::ClassType::LocalCCId>  LocalCCId;
    template <>
    struct ObjectClassTypeTraits<ccid::ClassType, ccid::ClassType::LocalCCId>
    {
      typedef ccid::ClassType             ctype_type;
      static const ctype_type             ctype = ccid::ClassType::LocalCCId;
      typedef ccid::ControlChannelIdBody  data_type;
    };
    template <typename Iterator>
    struct ObjectClassTypeParseTraits<Iterator, ccid::ClassType, ccid::ClassType::LocalCCId>
    {
      typedef ccid::parse::control_channel_id_body_grammar<Iterator>  grammar_type;
    };
    template <typename OutputIterator>
    struct ObjectClassTypeGenerateTraits<OutputIterator, ccid::ClassType, ccid::ClassType::LocalCCId>
	{
      typedef ccid::generate::control_channel_id_body_grammar<OutputIterator>  grammar_type;
	};
 	namespace ccid
	{
	  typedef ObjectClassTypeData<ObjectClassTypeTraits<ccid::ClassType,
			                                            ccid::ClassType::LocalCCId>>  LocalCCIdData;
//	  struct LocalCCIdData
//	  {
//		bool        m_negotiable;
//		lmp::DWORD  m_CCId;
//	  };
	  const lmp::WORD localCCIdLength = objHeaderLength + 4;
//      std::ostream& operator<<(
//        std::ostream&         os,
//  	    const LocalCCIdData&  localCCId);
	  namespace parse
	  {
	    namespace qi = boost::spirit::qi;
	    template <typename Iterator>
        struct local_control_channel_id_grammar : qi::grammar<Iterator, LocalCCIdData()>
        {
      	  local_control_channel_id_grammar();

      	  lmp::obj::parse::ObjectHeaderFixLengthInput                   object_header_input;
		  lmp::obj::parse::object_header_fix_length_grammar<Iterator>   object_header;
		  lmp::obj::ccid::parse::control_channel_id_body_grammar<Iterator>  control_channel_id_body;
      	  qi::rule<Iterator, LocalCCIdData()>                           local_control_channel_id_rule;
        };
	  }
	  namespace generate
	  {
	    namespace karma = boost::spirit::karma;
	    template <typename OutputIterator>
	    struct local_control_channel_id_grammar : karma::grammar<OutputIterator, LocalCCIdData()>
	    {
	      local_control_channel_id_grammar();

	      lmp::obj::ObjectHeaderData                                    object_header_output;
	      lmp::obj::generate::object_header_grammar<OutputIterator>     object_header;
		  lmp::obj::ccid::generate::control_channel_id_body_grammar<OutputIterator>  control_channel_id_body;
	      karma::rule<OutputIterator, LocalCCIdData()>                  local_control_channel_id_rule;
	    };
	  }
	}
  } // namespace obj
} // namespace lmp

#endif /* LMP_OBJ_LOCAL_CC_ID_HPP_ */
