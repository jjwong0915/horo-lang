#include <iostream>
#include <string>
#include <list>
#include "ast_struct.hpp"
#include "syntax_module.hpp"

using std::cout;
using std::endl;
using std::string;
using std::list;
using ast_struct::syntax_tree;
using ast_struct::syntax_tree_iterator;

namespace syntax_module {
	
	bool if_syntax(list<syntax_tree_iterator>& now) {
		list<string>& ts = now.back()->tokens;
		syntax_tree_iterator parent = *(--(--now.end()));
		if(ts.front() == "if") {
			ts.insert(++ts.begin(), "(");
			ts.push_back(") {");
			syntax_tree temp;
			temp.indent = now.back()->indent;
			temp.tokens.push_back("}");
			parent->children.insert(++(*(--now.end())), temp);
			return true;
		} else {
			return false;
		}
	}

}
