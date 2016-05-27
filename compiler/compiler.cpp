#include <iostream>
#include <cstring>
#include <fstream>
#include <cstdlib>
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
		cout << "jizz 23" << endl;
		if(inputname!=" "){
			finput.open(inputname);
			if(finput.is_open())
				input.rdbuf(finput.rdbuf());
			else{
				cerr << "[Error] file cann't open" << endl;
				return 0;
			}
		}
		cout << "jizz33 " << endl;
		if(outputname=="jizz"&&inputname!=" ")
			outputname=inputname;
		foutput.open(outputname+".cpp",fstream::out);
		output.rdbuf(foutput.rdbuf());
		wrong=parser(input,output);
		foutput.close();
		cout << "jizz 40" << endl;
		if(cmd::compile){ 
			string systemcmd="g++ " + cmd::outputname +".cpp " + cmd::ccstd + " -o " + outputname;
			cout << systemcmd <<endl;
			wrong=system(systemcmd.c_str());
		}
		return wrong;
	}else{
		cout << "jizz48 " << endl;
		return 0;
	}
}