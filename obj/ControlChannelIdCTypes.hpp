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
#include <boost/spirit/include/karma.hpp>

namespace lmp
{
  namespace obj
  {
    namespace ccid
    {
      typedef boost::variant<lmp::obj::ccid::LocalCCIdData,
                             lmp::obj::ccid::RemoteCCIdData,
                             lmp::obj::ccid::UnknownCCIdCTypeData>   ControlChannelIdCTypes;
      lmp::DWORD getLength(
        const ControlChannelIdCTypes&  controlChannelIdCTypes);
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

          lmp::obj::parse::object_class_grammar<Iterator,
                                                lmp::obj::ccid::ClassType,
                                                lmp::obj::ccid::ClassType::LocalCCId>                   local_ccid;
          lmp::obj::parse::object_class_grammar<Iterator,
                                                lmp::obj::ccid::ClassType,
                                                lmp::obj::ccid::ClassType::RemoteCCId>                  remote_ccid;
          lmp::obj::parse::object_class_unknown_ctype_grammar<Iterator,
                                                              lmp::obj::ObjectClass::ControlChannelID>  unknown_ccid_ctype;
          qi::rule<Iterator, ControlChannelIdCTypes()>                                                  control_channel_id_ctypes_rule;
        };
      }
      namespace generate
      {
        namespace karma = boost::spirit::karma;
        template <typename OutputIterator>
        struct control_channel_id_ctypes_grammar : karma::grammar<OutputIterator, ControlChannelIdCTypes()>
        {
          control_channel_id_ctypes_grammar();

          lmp::obj::generate::object_class_grammar<OutputIterator,
                                                   lmp::obj::ccid::ClassType,
                                                   lmp::obj::ccid::ClassType::LocalCCId>     local_ccid;
          lmp::obj::generate::object_class_grammar<OutputIterator,
                                                   lmp::obj::ccid::ClassType,
                                                   lmp::obj::ccid::ClassType::RemoteCCId>    remote_ccid;
          lmp::obj::generate::object_class_unknown_ctype_grammar<OutputIterator,
                                                                 lmp::obj::ObjectClass::ControlChannelID>  unknown_ccid_ctype;
          karma::rule<OutputIterator, ControlChannelIdCTypes()>                                            control_channel_id_ctypes_rule;
        };
      }
    }
  } // namespace obj
} // namespace lmp

#endif /* LMP_OBJ_CC_ID_CTYPES_HPP_ */
