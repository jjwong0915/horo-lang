#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <list>
#include <iterator>
#include <cctype>
#include "parser.hpp"
#include "output.hpp"
#include "ast_struct.hpp"
#include "syntax_module.hpp"

using std::cerr;
using std::cin;
using std::endl;
using std::getline;
using std::string;
using std::stringstream;
using std::isspace;
using std::list;
using std::next;
using std::prev;
using output::print;
using ast_struct::syntax_tree;
using ast_struct::syntax_tree_iterator;
using syntax_module::if_while_syntax;
using syntax_module::semicolon_syntax;
using syntax_module::function_syntax;
using syntax_module::else_syntax;
using syntax_module::block_syntax;
using syntax_module::for_syntax;
using syntax_module::return_syntax;


namespace horo_parser {

	const list<int (*)(list<syntax_tree_iterator>&)> syntaxes = {
		if_while_syntax,
		else_syntax,
		for_syntax,
		block_syntax,
		function_syntax,
		return_syntax,
		semicolon_syntax
	};

	void lexer(string input, int& indent, list<string>& tokens) {
		stringstream ss (input);
		indent = 0;
		while(isspace(ss.peek())) {
			ss.get();
			indent++;
		}
		string s;
		while(ss >> s) {
			tokens.push_back(s);
		}
		if(tokens.empty()) {
			tokens.push_back(" ");
		}
	}

	bool process_syntax(list<syntax_tree_iterator>& now) {
		list<syntax_tree>& chd = now.back()->children;
		for(auto i=chd.begin();i!=chd.end();i++) {
			now.push_back(i);
			bool ok = process_syntax(now);
			if(!ok) {
				return false;
			}
			now.pop_back();
		}
		
		for(auto i : syntaxes) {
			int end = i(now);
			if(end) {
				if(end == 1) {
					break;
				} else {
					return false;
				}
			}
		}
		return true;
	}
	// modify AST 
	void insert_node(list<syntax_tree_iterator>& now, int indent, list<string>& tokens) {
		syntax_tree t;
		t.indent = indent;
		t.tokens.insert(t.tokens.end(), tokens.begin(), tokens.end());
		now.back()->children.push_back(t);
		now.push_back(prev(now.back()->children.end()));
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
				cerr << "[error] indent error" << endl;
				return 1;
			}
			now.pop_back();
		}
		return 0;
	}
	// parser
	int parser() {	

		syntax_tree root;
		root.indent = -2;
		root.children.emplace_back();

		list<syntax_tree_iterator> now;
		now.push_back(prev(root.children.end()));
		now.back()->indent = -1;
		now.back()->tokens.push_back("module");

		string s;
		while(getline(cin, s)) {
			int indent;
			list<string> tokens;
			lexer(s, indent, tokens);
			int status = check_indent(now, indent);
			if(!status) {
				insert_node(now, indent, tokens);
			} else {
				return 1;
			}
		}

		while(now.size() > 1) {
			now.pop_back();
		}
		bool ok = process_syntax(now);
		if(!ok) {
			cerr << "terminated..." << endl;
			return 1;
		}

		for(syntax_tree i : root.children.back().children) {
			print(i);
		}

		return 0;

	}

}

