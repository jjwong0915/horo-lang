#include <iostream>
#include <cstring>
#include <fstream>
#include "parser.hpp"
#include "commandline.hpp"

using std::cin;
using std::cout;
using std::cerr;
using std::endl;
using std::strcmp;
using namespace cmd;
using horo_parser::parser;

int main(int argc, char* argv[]) {
	if(!cmd::mainconsole(argc,argv)){//mainconsole:if wrong or -help,return 1;
		bool wrong=0;
		istream input(cin.rdbuf());
		//cin >> input;
		ostream output(cout.rdbuf());
		fstream finput,foutput;
		if(inputname!=" "){
			finput.open(inputname);
			if(finput.is_open())
				input.rdbuf(finput.rdbuf());
			else{
				cerr << "[Error] file cann't open" << endl;
				return 1;
			}
		}
		if(outputname!=" "){
			foutput.open(outputname,fstream::out);
			output.rdbuf(foutput.rdbuf());
		}
		wrong=parser(input,output);
		foutput.close();
		return wrong;
	}else{
		return 0;
	}
}