#ifndef LMP_OBJ_OBJECTS_HPP_
#define LMP_OBJ_OBJECTS_HPP_
/*
 * Objects.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "obj/ControlChannelIdCTypes.hpp"
#include "obj/MessageIdCTypes.hpp"
#include "obj/NodeIdCTypes.hpp"
#include "obj/ConfigCTypes.hpp"
#include "obj/HelloCTypes.hpp"
#include "obj/UnknownObjectClass.hpp"

#include <boost/variant.hpp>
#include <boost/spirit/include/qi.hpp>

namespace lmp
{
  namespace obj
  {
    typedef boost::variant<lmp::obj::ccid::ControlChannelIdCTypes,
                           lmp::obj::msgid::MessageIdCTypes,
                           lmp::obj::nodeid::NodeIdCTypes,
                           lmp::obj::config::ConfigCTypes,
                           lmp::obj::hello::HelloCTypes,
                           lmp::obj::UnknownObjectClassData>   Objects;
    std::ostream& operator<<(
      std::ostream&   os,
      const Objects&  objects);
    namespace parse
    {
      namespace qi = boost::spirit::qi;
      template <typename Iterator>
      struct objects_grammar : qi::grammar<Iterator, Objects()>
      {
        objects_grammar();

        lmp::obj::ccid::parse::control_channel_id_ctypes_grammar<Iterator>    control_channel_id_ctypes;
        lmp::obj::msgid::parse::message_id_ctypes_grammar<Iterator>           message_id_ctypes;
        lmp::obj::nodeid::parse::node_id_ctypes_grammar<Iterator>             node_id_ctypes;
        lmp::obj::config::parse::config_ctypes_grammar<Iterator>              config_ctypes;
        lmp::obj::hello::parse::hello_ctypes_grammar<Iterator>                hello_ctypes;
        lmp::obj::parse::unknown_object_class_grammar<Iterator>               unknown_object_class;
        qi::rule<Iterator, Objects()>                                         objects;
      };
    }
  } // namespace obj
} // namespace lmp

#endif /* LMP_OBJ_OBJECTS_HPP_ */
