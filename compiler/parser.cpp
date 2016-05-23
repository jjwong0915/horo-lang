#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <boost/spirit/include/qi.hpp>

using std::cin;
using std::cout;
using std::endl;
using std::list;
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


// AST structs
struct syntax_tree;

struct syntax_tree {
 	int indent = -2;
 	list<string> tokens;
 	list<syntax_tree> children;
};

typedef list<syntax_tree>::iterator syntax_tree_iterator;


// process syntax
bool if_syntax(list<syntax_tree_iterator>& now) {
	list<string>& ts = now.back()->tokens;
	syntax_tree_iterator parent = *(--(--now.end()));
	if(ts.front() == "if") {
		ts.insert(++ts.begin(), "(");
		ts.push_back(") {");
		syntax_tree temp;
		temp.indent = parent->indent;
		temp.tokens.push_back("}");
		parent->children.insert(++(now.back()), temp);
		return true;
	} else {
		return false;
	}
}

list<bool (*)(list<syntax_tree_iterator>&)> syntaxes = {if_syntax};

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



