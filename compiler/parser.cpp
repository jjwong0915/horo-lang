#include <iostream>
#include <string>
#include <vector>
#include <boost/spirit/include/qi.hpp>

using std::cin;
using std::cout;
using std::endl;
using std::getline;
using std::vector;
using std::string;

using boost::variant;
using boost::apply_visitor;
using boost::static_visitor;
using boost::recursive_wrapper;
namespace qi = boost::spirit::qi;
using qi::rule;
using qi::grammar;
using qi::parse;
namespace ascii = boost::spirit::ascii;
using ascii::char_;
using ascii::space;
using ascii::space_type;

// grammer
struct syntax : grammar<string::iterator, vector<string>()> {
	syntax(): syntax::base_type(cmd) {
		cmd = *space >> +(char_ - space) % space;
	}
	rule<string::iterator, vector<string>()> cmd;
};


// ast structs
struct syntax_tree;

struct syntax_tree {
 	int indent;
 	vector<string> content;
 	vector<syntax_tree> children;
};


// debug
string tab(int n) {
	string s;
	for(int i=0;i<n;i++) {
		s += " ";
	}
	return s;
}
void print(syntax_tree t) {
	cout << tab(t.indent);
	for(string i : t.content) {
		cout << i << " ";
	}
	cout << "{" << endl;
	for(syntax_tree i : t.children) {
		print(i);
	}
	cout << tab(t.indent) << "}" << endl;
}


// modify ast
void insert_node(vector<syntax_tree*>& now, vector<string> input) {
	syntax_tree t;
	t.indent = input[0].length();
	t.content.insert(t.content.end(), ++input.begin(), input.end());
	now.back()->children.push_back(t);
	now.push_back(&(now.back()->children.back()));
}
void modify(vector<syntax_tree*>& now, vector<string> input) {
	int input_indent = input[0].length();
	int now_indent = now.back()->indent;

	if(input_indent == now_indent) {
		now.pop_back();
		insert_node(now, input);
	} else if(input_indent > now_indent) {
		insert_node(now, input);
	} else if(input_indent < now_indent) {
		while(now.back()->indent > input_indent) {
			now.pop_back();
		}
		if(now.back()->indent == input_indent) {
			now.pop_back();
			modify(now, input);
		} else {
			cout << "[error] indent error" << endl;
		}
	}
}


// parser
int main() {

	string s;
	syntax expr;
	syntax_tree ast;
	vector<syntax_tree*> now;

	ast.indent = -1;
	ast.content.push_back("module");
	now.push_back(&ast);

	while(getline(cin, s)) {
		string::iterator begin = s.begin();
		vector<string> input;
		bool ok = parse(begin, s.end(), expr, input);
		if(ok && begin == s.end()) {
			modify(now, input);
		} else {
			cout << "Failed" << endl;
		}
	}

	for(syntax_tree i : ast.children) {
		print(i);
	}
}



