#ifndef LMP_OBJ_LOCAL_CC_ID_PARSER_HPP_
#define LMP_OBJ_LOCAL_CC_ID_PARSER_HPP_
/*
 * LocalCCIdParser.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "obj/LocalCCIdAst.hpp"

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

      struct local_cc_id_class;
      typedef
        x3::rule<local_cc_id_class, ccid::ast::LocalCCId>  local_cc_id_type;
      BOOST_SPIRIT_DECLARE(local_cc_id_type);
    }
    parser::local_cc_id_type const& local_cc_id();
  } // namespace obj
} // namespace lmp

#endif /* LMP_OBJ_LOCAL_CC_ID_PARSER_HPP_ */
