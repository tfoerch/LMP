#ifndef LMP_OBJ_REMOTE_CC_ID_HPP_
#define LMP_OBJ_REMOTE_CC_ID_HPP_
/*
 * RemoteCCId.hpp
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

namespace lmp
{
  namespace obj
  {
    typedef ObjectClassType<ccid::ClassType, ccid::ClassType::RemoteCCId>  RemoteCCId;
    template <>
    struct ObjectClassTypeTraits<ccid::ClassType, ccid::ClassType::RemoteCCId>
    {
      typedef ccid::ClassType             ctype_type;
      static const ctype_type             ctype = ccid::ClassType::RemoteCCId;
      typedef ccid::ControlChannelIdBody  data_type;
    };
    template <typename Iterator>
    struct ObjectClassTypeParseTraits<Iterator, ccid::ClassType, ccid::ClassType::RemoteCCId>
    {
      typedef ccid::parse::control_channel_id_body_grammar<Iterator>  grammar_type;
    };
    template <typename OutputIterator>
    struct ObjectClassTypeGenerateTraits<OutputIterator, ccid::ClassType, ccid::ClassType::RemoteCCId>
	{
      typedef ccid::generate::control_channel_id_body_grammar<OutputIterator>  grammar_type;
	};
	namespace ccid
	{
	  typedef ObjectClassTypeData<ObjectClassTypeTraits<ccid::ClassType,
			                                            ccid::ClassType::RemoteCCId>>  RemoteCCIdData;
//	  struct RemoteCCIdData
//	  {
//		bool        m_negotiable;
//		lmp::DWORD  m_CCId;
//	  };
	  const lmp::DWORD remoteCCIdLength = objHeaderLength + 4;
//      std::ostream& operator<<(
//        std::ostream&          os,
//  	    const RemoteCCIdData&  remoteCCId);
	  namespace parse
	  {
	    namespace qi = boost::spirit::qi;
        template <typename Iterator>
        struct remote_control_channel_id_grammar : qi::grammar<Iterator, RemoteCCIdData()>
        {
      	  remote_control_channel_id_grammar();

      	  lmp::obj::parse::ObjectHeaderFixLengthInput                   object_header_input;
		  lmp::obj::parse::object_header_fix_length_grammar<Iterator>   object_header;
		  lmp::obj::ccid::parse::control_channel_id_body_grammar<Iterator>  control_channel_id_body;
      	  qi::rule<Iterator, RemoteCCIdData()>                          remote_control_channel_id_rule;
        };
	  }
	}
  } // namespace obj
} // namespace lmp

#endif /* LMP_OBJ_REMOTE_CC_ID_HPP_ */
