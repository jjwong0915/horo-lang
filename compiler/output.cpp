#include <iostream>
#include <list>
#include "output.hpp"

using std::cout;
using std::endl;
using std::list;
using ast_struct::syntax_tree;
using ast_struct::syntax_tree_iterator;

namespace output{
	// output
	void print(syntax_tree t) {
		if(t.indent >= -1) {
			for(int i=0;i<t.indent;i++) {
				cout << " ";
			}
			for(string s : t.tokens) {
				cout << s << " ";
			}
			cout << endl;
		}
		for(syntax_tree i : t.children) {
			print(i);
		}
	}
	//debug
	void print_now(list<syntax_tree_iterator>& now) {
		for(syntax_tree_iterator i : now) {
			cout << i->tokens.front() << " ";
		}
		cout << endl;
	}

}

