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

namespace lmp
{
  namespace obj
  {
    typedef ObjectClassType<ccid::ClassType, ccid::ClassType::LocalCCId>  LocalCCId;
	namespace ccid
	{
	  struct LocalCCIdData
	  {
		bool        m_negotiable;
		lmp::DWORD  m_CCId;
	  };
	  const lmp::WORD localCCIdLength = objHeaderLength + 4;
      std::ostream& operator<<(
        std::ostream&         os,
  	    const LocalCCIdData&  localCCId);
	  namespace parse
	  {
	    namespace qi = boost::spirit::qi;
	    template <typename Iterator>
        struct local_control_channel_id_grammar : qi::grammar<Iterator, LocalCCIdData()>
        {
      	  local_control_channel_id_grammar();

      	  lmp::obj::parse::ObjectHeaderFixLengthInput                   object_header_input;
		  lmp::obj::parse::object_header_fix_length_grammar<Iterator>   object_header;
      	  qi::rule<Iterator, LocalCCIdData()>                           local_control_channel_id_rule;
        };
	  }
	}
  } // namespace obj
} // namespace lmp

#endif /* LMP_OBJ_LOCAL_CC_ID_HPP_ */
