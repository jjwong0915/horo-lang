#include <iostream>
#include <cstring>
#include "parser.hpp"
#include "commandline.hpp"

using std::cin;
using std::cout;
using horo_parser::parser;

int main(int argc, char* argv[]) {
	if(!cmd::mainconsole(argc,argv)){//mainconsole:if wrong or -help,return 1;
		bool wrong=parser(cin,cout);
		
	}else{
		return 0;
	}
}