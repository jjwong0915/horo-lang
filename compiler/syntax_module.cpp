#include <string>
#include <list>
#include <iterator>
#include "ast_struct.hpp"
#include "output.hpp"
#include "syntax_module.hpp"

using std::string;
using std::list;
using std::next;
using std::prev;
using ast_struct::syntax_tree;
using ast_struct::syntax_tree_iterator;
using output::error_log;

/*
 * Syntax modules are put in this header.
 * 
 * Interface: int syntax(list<syntax_tree_iterator>& now)
 * 
 * Return value { 0: error, 1: continue, 2: end }
 *
 */

namespace syntax_module {
	// "if() {}"
	int if_while_syntax(list<syntax_tree_iterator>& now) {
		list<string>& ts = now.back()->tokens;
		if(ts.front()=="if" || ts.front()=="while") {
			if(ts.size() < 2) {
				error_log("wrong \""+ts.front()+"\" syntax", now.back()->linenum);
				return 0;
			}
			ts.insert(next(ts.begin()), "(");
			ts.push_back(")");
			ts.push_back("{");
			syntax_tree temp;
			temp.indent = now.back()->indent;
			temp.tokens.push_back("}");
			(*prev(now.end(), 2))->children.insert(next(now.back()), temp);

			return 2;
		} else {
			return 1;
		}
	}
	// ";" (must be last)
	int semicolon_syntax(list<syntax_tree_iterator>& now) {
		list<string>& ts = now.back()->tokens;
		auto valid = [](string s) {
			string notlast[] = {"{","}",";",":"," "};
			for(auto i : notlast) {
				if(s == i) {
					return false;
				}
			}
			return true;
		};
		if(ts.front().front()!='#' && valid(ts.back())) {
			ts.push_back(";");
			return 2;
		}
		return 1;
	}
	// function (must after block keywords)
	int function_syntax(list<syntax_tree_iterator>& now) {
		list<string>& ts = now.back()->tokens;
		if(ts.size()>=2 && now.back()->children.size()) {
			ts.insert(next(ts.begin(), 2), "(");
			ts.push_back(")");
			ts.push_back("{");
			syntax_tree temp;
			temp.indent = now.back()->indent;
			temp.tokens.push_back("}");
			(*prev(now.end(), 2))->children.insert(next(now.back()), temp);

			return 2;
		} else {
			return 1;
		}
	}
	// "} else {}" | "} else if() {}"
	int else_syntax(list<syntax_tree_iterator>& now) {
		list<string>& ts = now.back()->tokens;
		if(ts.front() == "else") {
			list<string> prev_line = prev(now.back(), 2)->tokens;
			if(prev_line.front()!="if" && *next(prev_line.begin(),2)!="if") {
				error_log("unexpected \"else\"", now.back()->linenum);
				return 0;
			} else {
				if(ts.size() == 2) {
					error_log("wrong \"else\" syntax", now.back()->linenum);
					return 0;
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

				return 2;
			}
		} else {
			return 1;
		}
	}
	// block "{};"
	int block_syntax(list<syntax_tree_iterator>& now) {
		string key = now.back()->tokens.front();
		if(key=="struct" || key=="class" || key=="union" || key=="enum") {
			now.back()->tokens.push_back("{");
			syntax_tree temp;
			temp.indent = now.back()->indent;
			temp.tokens.push_back("}");
			temp.tokens.push_back(";");
			(*prev(now.end(), 2))->children.insert(next(now.back()), temp);
			return 2;
		} else {
			return 1;
		}
	}
	// for loop
	int for_syntax(list<syntax_tree_iterator>& now) {
		list<string>& tk = now.back()->tokens;
		if(tk.front()=="for") {
			auto to_p = tk.end();					//iterator for "to"
			for(auto i=tk.begin();i!=tk.end();i++) {
				if(*i=="to") {
					if(to_p==tk.end()){
						to_p = i;
					} else {
						error_log("wrong \"for\" syntax", now.back()->linenum);
						return 0;
					}
				}
			}
			if(to_p!=tk.end()) {
				string type_name;
				list<string>::iterator var_p;
				if(*next(tk.begin(), 2) == "=") {
					type_name = "auto";
					var_p = next(tk.begin());
				} else {
					type_name = *next(tk.begin());
					var_p = next(tk.begin(), 2);
				}
				list<string> tempk;
				tempk.push_back("for");
				tempk.push_back("(");
				tempk.push_back(type_name);
				tempk.push_back(*var_p);
				for(auto i=next(var_p);i!=to_p;i++) {
					tempk.push_back(*i);
				}
				tempk.push_back(";");
				tempk.push_back(*var_p);
				tempk.push_back("!=");
				for(auto i=next(to_p);i!=tk.end();i++) {
					tempk.push_back(*i);
				}
				tempk.push_back(";");
				tempk.push_back(*var_p);
				tempk.push_back("++");
				tempk.push_back(")");
				tempk.push_back("{");
				tk = tempk;
			} else {
				tk.insert(next(tk.begin()), "(");
				tk.push_back(")");
				tk.push_back("{");
			}
			syntax_tree temp;
			temp.indent = now.back()->indent;
			temp.tokens.push_back("}");
			(*prev(now.end(), 2))->children.insert(next(now.back()), temp);
			return 2;
		} else {
			return 1;
		}
	}
	// return 
	int return_syntax(list<syntax_tree_iterator>& now) {
		auto& tkf = now.back()->tokens.front();
		if(tkf == "=>") {
			tkf = "return";
		}
		return 1;
	}

}
