/*
 * UnknownCCIdCTypeParser.cpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "obj/UnknownCCIdCTypeAst.hpp"
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
                               ccid::ast::UnknownCCIdCType,
                               ObjectClass::ControlChannelID>(object_class_unknown_ctype_type<ObjectClass::ControlChannelID>  rule,
                                                              iterator_type&                                                  first,
                                                              iterator_type const&                                            last,
                                                              context_type const&                                             context,
                                                              ccid::ast::UnknownCCIdCType&                                    attr);
    }
    template parser::object_class_unknown_ctype_type<ObjectClass::ControlChannelID> const& object_class_unknown_ctype();
  }
}

