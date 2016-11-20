#ifndef LMP_OBJ_CC_ID_CTYPES_HPP_
#define LMP_OBJ_CC_ID_CTYPES_HPP_
/*
 * ControlChannelIdCTypes.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "obj/LocalCCId.hpp"
#include "obj/RemoteCCId.hpp"
#include "obj/UnknownCCIdCType.hpp"

#include <boost/variant.hpp>
#include <boost/spirit/include/qi.hpp>

namespace lmp
{
  namespace obj
  {
	namespace ccid
	{
	typedef
	  boost::variant<lmp::obj::ccid::LocalCCIdData,
	                 lmp::obj::ccid::RemoteCCIdData,
					 lmp::obj::ccid::UnknownCCIdCTypeData>   ControlChannelIdCTypes;
      std::ostream& operator<<(
        std::ostream&                  os,
  	    const ControlChannelIdCTypes&  controlChannelIdCTypes);
	  namespace parse
	  {
	    namespace qi = boost::spirit::qi;
	    template <typename Iterator>
        struct control_channel_id_ctypes_grammar : qi::grammar<Iterator, ControlChannelIdCTypes()>
        {
      	  control_channel_id_ctypes_grammar();

          lmp::obj::ccid::parse::local_control_channel_id_grammar<Iterator>    local_ccid;
          lmp::obj::ccid::parse::remote_control_channel_id_grammar<Iterator>   remote_ccid;
          lmp::obj::ccid::parse::unknown_control_channel_id_grammar<Iterator>  unknown_ccid_ctype;
      	  qi::rule<Iterator, ControlChannelIdCTypes()>                         control_channel_id_ctypes_rule;
        };
	  }
	}
  } // namespace obj
} // namespace lmp

#endif /* LMP_OBJ_CC_ID_CTYPES_HPP_ */
