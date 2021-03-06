#ifndef HORO_PARSER
#define HORO_PARSER

#include <iostream>
#include <string>
#include <list>
#include "ast_struct.hpp"

using std::istream;
using std::ostream;
using std::string;
using std::list;
using ast_struct::syntax_tree_iterator;


namespace horo_parser {

	extern const list<int (*)(list<syntax_tree_iterator>&)> syntaxes;

	void lexer(string, int&, list<string>&);

	bool process_syntax(list<syntax_tree_iterator>&);
	// modify AST 
	void insert_node(list<syntax_tree_iterator>&, int, int, list<string>&);

	bool check_indent(list<syntax_tree_iterator>&, int, int);
	// parser
	bool parser(istream&, ostream&);

}

#endif

