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

typedef variant<
	recursive_wrapper<syntax_tree>,
	string
> syntax_tree_node;

struct syntax_tree {
 	string name;
 	vector<syntax_tree_node> children;
};

BOOST_FUSION_ADAPT_STRUCT(
    syntax_tree,
    (string, name)
    (vector<syntax_tree_node>, children)
);


// debug
struct syntax_tree_printer {
	void operator() (syntax_tree t);
};
struct syntax_tree_node_printer : static_visitor<> {
	void operator() (syntax_tree t) {
		syntax_tree_printer printer;
		printer(t);
	}
	void operator() (string s) {
		cout << s << endl;
	}
};
void syntax_tree_printer::operator() (syntax_tree t) {
	syntax_tree_node_printer printer;
	cout << t.name << " {" << endl;
	for(auto i : t.children) {
		apply_visitor(printer, i);
	}
	cout << '}' << endl;
};


// modify ast
void modify(syntax_tree& now, int& step, vector<string> input) {
	if(input[0].length() == step) {
		if(input[1] == "def") {
			syntax_tree t;
			t.name = input[2];
			now.children.push_back(t);
			step = ~step;
		} else {
			cout << "\""+input[1]+"\" is undefined." << endl;
		}
	} else {
		if(step < 0 && input[0].length() > ~step) {
			step = input[0].length();
			modify(now, step, input);
		} else {
			cout << "indent error" << endl;
		}
	}
}


// parser
int main() {

	string s;
	syntax expr;
	syntax_tree ast;
	syntax_tree& now = ast;
	syntax_tree_printer printer;
	int step = 0;

	now.name = "module";

	while(getline(cin, s)) {
		string::iterator begin = s.begin();
		vector<string> input;
		bool ok = parse(begin, s.end(), expr, input);
		if(ok && begin == s.end()) {
			modify(now, step, input);
			printer(now);
		} else {
			cout << "Failed" << endl;
		}
	}


}



