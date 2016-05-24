#ifndef SYNTAX_MODULE
#define SYNTAX_MODULE

#include <list>
#include "ast_struct.hpp"

using std::list;
using ast_struct::syntax_tree_iterator;

namespace syntax_module {

	bool if_syntax(list<syntax_tree_iterator>&);

}

#endif
