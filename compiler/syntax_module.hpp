
#include <iostream>
#include <string>
#include <vector>
#include <boost/spirit/include/qi.hpp>

#include "ast_struct.hpp"

using std::cin;
using std::cout;
using std::endl;
using std::getline;
using std::vector;
using std::string;
using namespace ast_struct;

namespace syntax_module{
	bool if_syntax(vector<syntax_tree_iterator>& now) {
		vector<string>& ts = now.back()->tokens;
		syntax_tree_iterator parent = *(--now.end());
		if(ts.front() == "if") {
			ts.insert(++ts.begin(), "(");
			ts.insert(ts.end(), ") {");
			syntax_tree temp;
			temp.indent = parent->indent;
			temp.tokens.push_back("}");
			parent->children.insert(++now.back(), temp);
			return true;
		} else {
			return false;
		}
	}
}