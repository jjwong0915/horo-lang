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

using std::getline;
using std::string;
using std::stringstream;
using std::isspace;
using std::list;
using std::prev;
using output::print;
using output::error_log;
using ast_struct::syntax_tree;
using ast_struct::syntax_tree_iterator;
using namespace syntax_module;


namespace horo_parser {

	// list for syntaxes to process with
	const list<int (*)(list<syntax_tree_iterator>&)> syntaxes = {
		if_while_syntax,
		else_syntax,
		for_syntax,
		block_syntax,
		function_syntax,
		return_syntax,
		semicolon_syntax
	};

	// lex "input" string into "indent" and "tokens"
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

	// Return value {true: success, false: error}
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
			int status = i(now);
			if(!status) {
				return false;
			} else if(status == 2) {
				break;
			}
		}
		return true;
	}

	// add new syntax tree
	void insert_node(list<syntax_tree_iterator>& now, int indent, int linenum, list<string>& tokens) {
		syntax_tree t;
		t.indent = indent;
		t.linenum = linenum;
		t.tokens.insert(t.tokens.end(), tokens.begin(), tokens.end());
		now.back()->children.push_back(t);
		now.push_back(prev(now.back()->children.end()));
	}

	// Return value {true: success, false: error}
	bool check_indent(list<syntax_tree_iterator>& now, int input_indent, int linenum) {
		int now_indent = now.back()->indent;
		if(input_indent == now_indent) {
			now.pop_back();
		} else if(input_indent < now_indent) {
			while(now.back()->indent > input_indent) {
				now.pop_back();
			}
			if(now.back()->indent < input_indent) {
				error_log("indent error", linenum);
				return false;
			}
			now.pop_back();
		}
		return true;
	}

	// Return value {true: success, false: error}
	bool parser(istream& in, ostream& out) {	

		syntax_tree root;
		root.indent = -2;
		root.linenum = -2;
		root.children.emplace_back();

		list<syntax_tree_iterator> now;
		now.push_back(prev(root.children.end()));
		now.back()->indent = -1;
		now.back()->linenum = -1;
		now.back()->tokens.push_back("module");

		int linenow = 0;
		string s;
		while(getline(in, s)) {
			linenow++;
			int indent;
			list<string> tokens;
			lexer(s, indent, tokens);
			bool success = check_indent(now, indent, linenow);
			if(success) {
				insert_node(now, indent, linenow, tokens);
			} else {
				return false;
			}
		}
		while(now.size() > 1) {
			now.pop_back();
		}
		if(!process_syntax(now)) {
			return false;
		}
		for(syntax_tree i : root.children.back().children) {
			print(i, out);
		}

		return true;

	}

}

