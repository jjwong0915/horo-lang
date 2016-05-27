#include <iostream>
#include <cstring>
#include <fstream>
#include <cerr>
#include "parser.hpp"
#include "commandline.hpp"

using std::cout;
using std::cin;
using std::cerr;
using std::endl;
using std::strcmp;
using namespace cmd;
using horo_parser::parser;

int main(int argc, char* argv[]) {
	if(!cmd::mainconsole(argc,argv)){//mainconsole:if wrong or -help,return 1;
		bool wrong=0;
		istream input=cin;
		ostream output=cout;
		fstream finput,foutput;
		if(inputname!=" "){
			finput.open(inputname);
			if(finput.is_open())
				input=finput;
			else{
				cerr << "[Error] file cann't open" << endl;
				return 1;
			}
		}
		if(outputname!=" "){
			foutput.open(outputname);
			output=foutput;
		}
		return parse(input,ouput);
	}else{
		return 0;
	}
}