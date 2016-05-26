#ifndef HORO_PARSER
#define HORO_PARSER

#include <iostream>
#include <string>
#include <vector>
#include <list>
#include "boost/spirit/include/qi.hpp"
#include "ast_struct.hpp"


using std::string;
using std::vector;
using std::list;
namespace qi = boost::spirit::qi;
using qi::rule;
using qi::grammar;
using qi::parse;
using ast_struct::syntax_tree_iterator;



namespace horo_parser {

	// grammer
	struct tokenizer : grammar<string::iterator, vector<string>()>  {
		tokenizer();
		rule<string::iterator, vector<string>()> cmd;
	};

	bool process_syntax(list<syntax_tree_iterator>&);
	// modify AST 
	void insert_node(list<syntax_tree_iterator>&, vector<string>);

	int check_indent(list<syntax_tree_iterator>&, int);
	// parser
	int parser();

}

#endif

