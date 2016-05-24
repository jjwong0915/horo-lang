#ifndef OUTPUT
#define OUTPUT

#include <list>
#include "ast_struct.hpp"

using std::list;
using ast_struct::syntax_tree;
using ast_struct::syntax_tree_iterator;

namespace output{
	// output
	void print(syntax_tree t);
	//debug
	void print_now(list<syntax_tree_iterator>& now);

}

#endif