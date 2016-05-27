#include <iostream>
#include <list>
#include "output.hpp"


using std::ostream;
using std::endl;
using std::list;
using ast_struct::syntax_tree;
using ast_struct::syntax_tree_iterator;

namespace output{
	// output
	void print(syntax_tree t, ostream& out) {
		if(t.indent >= -1) {
			for(int i=0;i<t.indent;i++) {
				out << " ";
			}
			for(string s : t.tokens) {
				out << s << " ";
			}
			out << endl;
		}
		for(syntax_tree i : t.children) {
			print(i, out);
		}
	}

}

