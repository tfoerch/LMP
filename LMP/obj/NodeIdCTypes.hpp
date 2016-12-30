#ifndef LMP_OBJ_NODE_ID_CTYPES_HPP_
#define LMP_OBJ_NODE_ID_CTYPES_HPP_
/*
 * NodeIdCTypes.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "obj/LocalNodeId.hpp"
#include "obj/RemoteNodeId.hpp"
#include "obj/UnknownNodeIdCType.hpp"

#include <boost/variant.hpp>
#include <boost/spirit/include/qi.hpp>

namespace lmp
{
  namespace obj
  {
	namespace nodeid
	{
	typedef
	  boost::variant<lmp::obj::nodeid::LocalNodeIdData,
	                 lmp::obj::nodeid::RemoteNodeIdData,
					 lmp::obj::nodeid::UnknownNodeIdCTypeData>   NodeIdCTypes;
      std::ostream& operator<<(
        std::ostream&                  os,
  	    const NodeIdCTypes&            nodeIdCTypes);
	  namespace parse
	  {
	    namespace qi = boost::spirit::qi;
	    template <typename Iterator>
        struct node_id_ctypes_grammar : qi::grammar<Iterator, NodeIdCTypes()>
        {
      	  node_id_ctypes_grammar();

          lmp::obj::parse::object_class_grammar<Iterator,
		                                        lmp::obj::nodeid::ClassType,
												lmp::obj::nodeid::ClassType::LocalNodeId>    local_nodeid;
          lmp::obj::parse::object_class_grammar<Iterator,
		                                        lmp::obj::nodeid::ClassType,
												lmp::obj::nodeid::ClassType::RemoteNodeId>    remote_nodeid;
          lmp::obj::parse::object_class_unknown_ctype_grammar<Iterator,
		                                                      lmp::obj::ObjectClass::NodeID>  unknown_nodeid_ctype;
      	  qi::rule<Iterator, NodeIdCTypes()>                          node_id_ctypes_rule;
        };
	  }
	}
  } // namespace obj
} // namespace lmp

#endif /* LMP_OBJ_NODE_ID_CTYPES_HPP_ */
