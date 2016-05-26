
#ifndef AST_STRUCT
#define AST_STRUCT

#include <list>
#include <string>

using std::list;
using std::string;

namespace ast_struct {
	// AST structs
	struct syntax_tree;

	struct syntax_tree {
	 	int indent;
	 	list<string> tokens;
	 	list<syntax_tree> children;
	};

	typedef list<syntax_tree>::iterator syntax_tree_iterator;

}

#endif