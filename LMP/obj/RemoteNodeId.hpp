#ifndef LMP_OBJ_REMOTE_NODE_ID_HPP_
#define LMP_OBJ_REMOTE_NODE_ID_HPP_
/*
 * RemoteNodeId.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "obj/NodeIdClass.hpp"
#include "obj/ObjectClassTypeTraits.hpp"
#include "obj/ObjectClassType.hpp"
#include "obj/NodeIdTypeTraits.hpp"
#include "obj/NodeIdIF.hpp"
#include "obj/NodeIdData.hpp"

namespace lmp
{
  namespace obj
  {
    typedef ObjectClassType<nodeid::ClassType, nodeid::ClassType::RemoteNodeId>  RemoteNodeId;
	namespace nodeid
	{
	  struct RemoteNodeIdData
	  {
	    bool        m_negotiable;
	    lmp::DWORD  m_nodeId;
	  };
	  std::ostream& operator<<(
		std::ostream&            os,
		const RemoteNodeIdData&  nodeId);
	  const lmp::WORD remoteNodeIdLength = objHeaderLength + 4;
	  namespace parse
	  {
	    namespace qi = boost::spirit::qi;
	    template <typename Iterator>
      struct remote_node_id_grammar : qi::grammar<Iterator, RemoteNodeIdData()>
      {
    	  remote_node_id_grammar();

    	  lmp::obj::parse::ObjectHeaderFixLengthInput                   object_header_input;
		  lmp::obj::parse::object_header_fix_length_grammar<Iterator>   object_header;
    	  qi::rule<Iterator, RemoteNodeIdData()>                        remote_node_id_rule;
      };
	}
	}
  } // namespace obj
} // namespace lmp

#endif /* LMP_OBJ_REMOTE_NODE_ID_HPP_ */
