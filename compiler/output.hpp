#ifndef OUTPUT
#define OUTPUT

#include <iostream>
#include <list>
#include <string>
#include "ast_struct.hpp"

using std::ostream;
using std::list;
using std::string;
using ast_struct::syntax_tree;
using ast_struct::syntax_tree_iterator;

namespace output {
	// output
	void print(syntax_tree&, ostream&);

	void error_log(string, int);

}

#endif