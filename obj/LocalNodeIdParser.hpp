#ifndef LMP_OBJ_LOCAL_NODE_ID_PARSER_HPP_
#define LMP_OBJ_LOCAL_NODE_ID_PARSER_HPP_
/*
 * LocalNodeIdParser.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "obj/LocalNodeIdAst.hpp"

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

      struct local_node_id_class;
      typedef
        x3::rule<local_node_id_class, nodeid::ast::LocalNodeId>  local_node_id_type;
      BOOST_SPIRIT_DECLARE(local_node_id_type);
    }
    parser::local_node_id_type const& local_node_id();
  } // namespace obj
} // namespace lmp

#endif /* LMP_OBJ_LOCAL_NODE_ID_PARSER_HPP_ */
