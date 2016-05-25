#include <iostream>
#include <string>
#include <list>
#include <iterator>
#include "ast_struct.hpp"
#include "syntax_module.hpp"

using std::cout;
using std::endl;
using std::string;
using std::list;
using std::next;
using std::prev;
using ast_struct::syntax_tree;
using ast_struct::syntax_tree_iterator;

namespace syntax_module {
	// "if() {}"
	int if_while_syntax(list<syntax_tree_iterator>& now) {
		list<string>& ts = now.back()->tokens;
		if(ts.front()=="if" || ts.front()=="while") {
			ts.insert(next(ts.begin()), "(");
			ts.push_back(")");
			ts.push_back("{");
			syntax_tree temp;
			temp.indent = now.back()->indent;
			temp.tokens.push_back("}");
			(*prev(now.end(), 2))->children.insert(next(now.back()), temp);

			//cout << "end with if while" << endl;
			return 1;
		} else {
			return 0;
		}
	}
	// ";" (must be last)
	int semicolon_syntax(list<syntax_tree_iterator>& now) {
		list<string>& ts = now.back()->tokens;
		if(ts.front().front()!='#' && ts.back()!="{" && ts.back()!="}") {
			ts.push_back(";");
			//cout << "end with ;" << endl;
			return 1;
		}
		return 0;
	}
	// function (must after block keywords)
	int function_syntax(list<syntax_tree_iterator>& now) {
		list<string>& ts = now.back()->tokens;
		if(ts.size()>=2 && now.back()->children.size()) {
			ts.insert(next(ts.begin(), 2), "(");
			ts.push_back(")");
			ts.push_back("{");
			//cout << "left side ok";
			syntax_tree temp;
			temp.indent = now.back()->indent;
			temp.tokens.push_back("}");
			(*prev(now.end(), 2))->children.insert(next(now.back()), temp);

			//cout << "end with func" << endl;
			return 1;
		} else {
			return 0;
		}
	}

	int else_syntax(list<syntax_tree_iterator>& now) {
		list<string>& ts = now.back()->tokens;
		if(ts.front() == "else") {
			list<string> prev_line = prev(now.back(), 2)->tokens;
			if(prev_line.front()!="if" && *next(prev_line.begin())!="else") {
				cout << "[error] unexpected \"else\"" << endl;
				return 2;
			} else {
				if(ts.size() == 2) {
					cout << "[error] wrong else syntax" << endl;
					return 2;
				}
				syntax_tree_iterator parent = *prev(now.end(), 2);

				parent->children.erase(prev(now.back()));
				if(ts.size()>=3 && *next(ts.begin())=="if") {
					ts.insert(next(ts.begin(), 2), "(");
					ts.push_back(")");
				}
				ts.push_front("}");
				ts.push_back("{");
				syntax_tree temp;
				temp.indent = now.back()->indent;
				temp.tokens.push_back("}");
				parent->children.insert(next(now.back()), temp);

				//cout << "end with else" << endl;
				return 1;
			}
		} else {
			return 0;
		}
	}

}
