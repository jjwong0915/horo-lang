#include <iostream>
#include <cstring>
#include "parser.hpp"
#include "commandline.hpp"

using std::cout;
using std::cerr;
using std::endl;
using std::strcmp;
using horo_parser::parser;

int main(int argc, char* argv[]) {
	if(!cmd::mainconsole(argc,argv)){//mainconsole:if wrong or -help,return 1;
		bool wrong=parser();
		
	}else{
		return 0;
	}
}