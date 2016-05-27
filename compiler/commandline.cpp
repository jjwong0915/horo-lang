#include "commandline.hpp"

#include <iostream>
#include <vector>
#include <cstring>

using namespace std;

namespace cmd{

	string outputname="jizz",ccstd="-std=c++11",inputname=" ";
	
	bool compile=0;

	const char *commandillustrate[]={
		"-h, --help      Display this information",
		"-o <file>.cpp   Place the output into <file>.cpp(default: \"jizz.cpp\")",
		"-x              Compile the output with g++ after transpiled"
	};

	void command_help(void)
	{
		cout << "Usage: horo [options] [file]" << endl;
		cout << "Options:" << endl;
		for(int i=0;i<COMMANDNUM;++i){
			cout << cmd::commandillustrate[i] << endl;
		}
		return ;
	}

	bool argument_check(char** parameter,int argc)
	{	
		int err=0;
		bool inputexise=0,outputexise=0;
		for(int i=1;i<argc;++i){
			if((strcmp(parameter[i],"-h")&&strcmp(parameter[i],"--help"))==0) {
				command_help();
				return 1;
			}else if(strcmp(parameter[i],"-o")==0){
				if(i+1>=argc||parameter[i+1][0]=='-'){
					cerr << "[Error] unexpected argument after -o" << endl;
				}else{
					outputname=parameter[1+i++];
				}
			}else if(strcmp(parameter[i],"-x")==0){
				compile=1;
			}else if(!inputexise && parameter[i][0]!='-'){
				inputexise=1;
				inputname=parameter[i];
			}else{
				cerr << "[Error] argument \"" << parameter[i] << "\" can't be found QQ" << endl;
				++err;
			}
		}
		return err>0;
	}


	bool mainconsole(int argn,char* argu[])
	{
		if(!argument_check(argu,argn)){
			return 0;
		}else{
			return 1;
		}
	}

}