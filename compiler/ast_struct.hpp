
#if !defined(AST_STRUCT)

#define AST_STRUCT

#include <iostream>
#include <string>
#include <vector>

using namespace std;
// AST structs
namespace ast_struct{
	struct syntax_tree;
	struct syntax_tree {
	 	int indent;
	 	vector<string> tokens;
	 	vector<syntax_tree> children;
	};

	typedef vector<syntax_tree>::iterator syntax_tree_iterator;
}

#endif