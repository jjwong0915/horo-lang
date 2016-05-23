
#if !defined(AST_STRUCT)

#define AST_STRUCT

#include <iostream>
#include <string>
#include <vector>

using namespace std;

namespace ast_struct{
	// AST structs
	struct syntax_tree;

	struct syntax_tree {
	 	int indent = -2;
	 	list<string> tokens;
	 	list<syntax_tree> children;
	};

	typedef list<syntax_tree>::iterator syntax_tree_iterator;
}

#endif