#ifndef SYNTAX_MODULE
#define SYNTAX_MODULE

#include <list>
#include "ast_struct.hpp"

using std::list;
using ast_struct::syntax_tree_iterator;

namespace syntax_module {

	int if_while_syntax(list<syntax_tree_iterator>&);

	int semicolon_syntax(list<syntax_tree_iterator>&);

	int function_syntax(list<syntax_tree_iterator>&);

	int else_syntax(list<syntax_tree_iterator>&);

}

#endif
