#if !defined(SYNTAX_MODULE)

#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <boost/spirit/include/qi.hpp>

#define SYNTAX_MODULE

#include "ast_struct.hpp"

using std::cin;
using std::cout;
using std::endl;
using std::getline;
using std::vector;
using std::string;
using std::list;

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

using namespace ast_struct;

namespace syntax_module{
	// grammer
	struct syntax : grammar<string::iterator, vector<string>()> {
		syntax(): syntax::base_type(cmd) {
			cmd = *space >> +(char_ - space) % space;
		}
		rule<string::iterator, vector<string>()> cmd;
	};
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
}

#endif