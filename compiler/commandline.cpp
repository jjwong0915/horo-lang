#include "commandline.hpp"

#include <iostream>
#include <vector>
#include <cstring>
#include <string>

using namespace std;

namespace cmd{

	string outputname,ccstd;
	
	bool compile;

	const char *command[]={
		"-h",//help
		"-o",//name after
		"-x"//gcc
	};

	const char *commandillustrate[]={
		"help",
		"name your output filename",
		"compile file with g++ after transpile"
	};

	void command_help(void)
	{
		for(int i=0;i<COMMANDNUM;++i){
			cout << cmd::command[i] << ": " << cmd::commandillustrate[i] << endl;
		}
		return ;
	}

	bool argument_check(char** parameter,int argc,vector<int> &cmd)
	{	
		int err=0;
		for(int i=1;i<argc;++i){
			if(!strcmp(parameter[i],cmd::command[0])) {
				command_help();
				return 1;
			}else if(!strcmp(parameter[i],cmd::command[1])){
				if(i+1>=argc||parameter[i+1][0]=='-'){
					cerr << "[Error] unexpected argument after -o" << endl;
				}else{
					cmd.push_back(1);
					++i;
				}
			}else if(!strcmp(parameter[i],cmd::command[2])){
				cmd.push_back(2);
			}else{
				cerr << "[Error] argument \"" << parameter[i] << "\" can't be found QQ" << endl;
				++err;
			}
		}
		return err>0;
	}

	void argument_process(char** parameter,int argc,vector<int> &cmd){
		
		for(int i=0,n=cmd.size(),pi=1;i<n;++i,++pi){
			switch(cmd[i]){
				case 1:
					outputname=parameter[1+pi++];
				case 2:
					compile=1;
			}
		}
		//cout << outputname << endl;
	}

	bool mainconsole(int argn,char* argu[])
	{
		vector<int> cmd;
		if(!argument_check(argu,argn,cmd)){
			argument_process(argu,argn,cmd);
		}else{
			return 1;
		}
	}

	bool file_compile()
	{
		//string s=

	}

}