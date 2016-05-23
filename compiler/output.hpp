#include <iostream>
#include <string>
#include <vector>
#include <boost/spirit/include/qi.hpp>

#include "ast_struct.hpp"

using namespace std;
using namespace ast_struct;
// output
namespace output{
	void print(syntax_tree t) {
		if(t.indent >= 0) {
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
	void print_now(vector<syntax_tree_iterator>& now) {
		for(syntax_tree_iterator i : now) {
			cout << i->tokens[0] << " ";
		}
		cout << endl;
	}	
}