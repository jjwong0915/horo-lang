#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <boost/spirit/include/qi.hpp>

#include "output.hpp"
#include "ast_struct.hpp"
#include "syntax_module.hpp"
using std::cin;
using std::cout;
using std::endl;
using std::list;
using std::getline;
using std::vector;
using std::string;


using namespace output;
using namespace ast_struct;
using namespace	syntax_module;

void process_syntax(list<syntax_tree_iterator>& now) {
	list<syntax_tree>& chd = now.back()->children;
	for(auto i=chd.begin();i!=chd.end();i++) {
		now.push_back(i);
		process_syntax(now);
		now.pop_back();
	}
	for(auto& i : syntaxes) {
		bool end = i(now);
		if(end) {
			break;
		}
	}
}


// modify AST 
void insert_node(list<syntax_tree_iterator>& now, vector<string> data) {
	syntax_tree t;
	t.indent = data[0].length();
	t.tokens.insert(t.tokens.end(), ++data.begin(), data.end());
	now.back()->children.push_back(t);
	now.push_back(--(now.back()->children.end()));
}

int check_indent(list<syntax_tree_iterator>& now, int input_indent) {
	int now_indent = now.back()->indent;
	//cout << "now indent: " << now_indent << endl;
	if(input_indent == now_indent) {
		now.pop_back();
	} else if(input_indent < now_indent) {
		while(now.back()->indent > input_indent) {
			now.pop_back();
		}
		if(now.back()->indent < input_indent) {
			cout << "[error] indent error" << endl;
			return 1;
		}
	}
	return 0;
}

// parser
int main() {

	string s;
	syntax expr;
	syntax_tree root;
	list<syntax_tree_iterator> now;

	root.children.emplace_back();
	now.push_back(--root.children.end());
	now.back()->indent = -1;
	now.back()->tokens.push_back("module");

	while(getline(cin, s)) {
		string::iterator begin = s.begin();
		vector<string> data;
		bool ok = parse(begin, s.end(), expr, data);
		if(ok && begin == s.end()) {
			int status = check_indent(now, data[0].length());
			//cout << status << endl;
			if(!status) {
				insert_node(now, data);
			} else {
				return 1;
			}
			//print(root.children.back());
		}
	}

	while(now.size() > 1) {
		now.pop_back();
	}
	process_syntax(now);

	for(syntax_tree i : root.children.back().children) {
		print(i);
	}

	return 0;
}



