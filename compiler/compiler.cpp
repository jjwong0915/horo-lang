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
using horo_parser::parser;
using cmd::outputname;
using cmd::inputname;

int main(int argc, char* argv[]) {
	if(cmd::mainconsole(argc,argv)){//mainconsole:if error or -help,return false;
		bool success = true;
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
		auto basename = [](string s) {
			string ans;
			for(auto i : s) {
				if(i == '.') {
					break;
				} else {
					ans += i;
				}
			}
			return ans;
		};
		if(outputname=="jizz"&&inputname!=" ")
			outputname=basename(inputname);
		foutput.open(outputname+".cpp",fstream::out);
		output.rdbuf(foutput.rdbuf());
		success = parser(input, output);
		foutput.close();
		if(cmd::compile){ 
			string systemcmd="g++ " + cmd::outputname +".cpp " + cmd::ccstd + " -o " + outputname;
			cout << systemcmd <<endl;
			success = !system(systemcmd.c_str());
		}
		return !success;
	}else{
		return 0;
	}
}