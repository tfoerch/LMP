#ifndef LMP_OBJ_REMOTE_NODE_ID_PARSER_HPP_
#define LMP_OBJ_REMOTE_NODE_ID_PARSER_HPP_
/*
 * RemoteNodeIdParser.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "obj/RemoteNodeIdAst.hpp"

#include <boost/spirit/home/x3/support/traits/is_variant.hpp>
#include <boost/spirit/home/x3/support/traits/tuple_traits.hpp>
#include <boost/spirit/home/x3/nonterminal/rule.hpp>
//#include <boost/spirit/home/x3.hpp>

namespace lmp
{
  namespace obj
  {
    namespace parser
    {
      namespace x3 = boost::spirit::x3;

      struct remote_node_id_class;
      typedef
        x3::rule<remote_node_id_class, nodeid::ast::RemoteNodeId>  remote_node_id_type;
      BOOST_SPIRIT_DECLARE(remote_node_id_type);
    }
    parser::remote_node_id_type const& remote_node_id();
  } // namespace obj
} // namespace lmp

#endif /* LMP_OBJ_REMOTE_NODE_ID_PARSER_HPP_ */
