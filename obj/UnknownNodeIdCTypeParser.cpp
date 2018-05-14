/*
 * UnknownNodeIdCTypeParser.cpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "obj/UnknownNodeIdCTypeAst.hpp"
#include "obj/ObjectClassUnknownCTypeParser_def.hpp"
#include "obj/LMPParseConfig.hpp"

namespace lmp
{
  namespace obj
  {
    namespace parser
    {
      namespace x3 = boost::spirit::x3;

      template bool parse_rule<iterator_type,
                               context_type,
                               nodeid::ast::UnknownNodeIdCType,
                               ObjectClass::NodeID>(object_class_unknown_ctype_type<ObjectClass::NodeID>  rule,
                                                    iterator_type&                                        first,
                                                    iterator_type const&                                  last,
                                                    context_type const&                                   context,
                                                    nodeid::ast::UnknownNodeIdCType&                      attr);
    }
    template parser::object_class_unknown_ctype_type<ObjectClass::NodeID> const& object_class_unknown_ctype();
  }
}

