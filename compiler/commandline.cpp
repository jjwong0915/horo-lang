#include "commandline.hpp"

#include <iostream>
#include <vector>
#include <cstring>

using namespace std;

namespace cmd{

	string outputname="jizz",ccstd="-std=c++11",inputname=" ";
	
	bool compile=0;

	const char *command[]={
		"-h, --help",//help
		"-o <file>",//name after
		"-x"//gcc
	};

	const char *commandillustrate[]={
		"Display this information",
		"Place the output into <file>(default: \"jizz.cpp\")",
		"Compile the output with g++ after transpiled"
	};

	void command_help(void)
	{
		cout << "Usage: horo [options] [file]" << endl;
		cout << "Options:" << endl;
		for(int i=0;i<COMMANDNUM;++i){
			cout << cmd::command[i] << ": " << cmd::commandillustrate[i] << endl;
		}
		return ;
	}

	bool argument_check(char** parameter,int argc,vector<int> &cmd)
	{	
		int err=0;
		bool inputexise=0,outputexise=0;
		for(int i=1;i<argc;++i){
			if(strcmp(parameter[i],cmd::command[0])==0) {
				command_help();
				return 1;
			}else if(strcmp(parameter[i],cmd::command[1])==0){
				if(i+1>=argc||parameter[i+1][0]=='-'){
					cerr << "[Error] unexpected argument after -o" << endl;
				}else{
					cmd.push_back(1);
					++i;
				}
			}else if(strcmp(parameter[i],cmd::command[2])==0){
				cmd.push_back(2);
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

	void argument_process(char** parameter,int argc,vector<int> &cmd){
		for(int i=0,n=cmd.size(),pi=1;i<n;++i,++pi){
			switch(cmd[i]){
				case 1:
					outputname=parameter[1+pi++];
					break;
				case 2:
					compile=1;
					break;
				default:
					continue;
			}
		}
	}

	bool mainconsole(int argn,char* argu[])
	{
		vector<int> cmd;
		if(!argument_check(argu,argn,cmd)){
			argument_process(argu,argn,cmd);
			return 0;
		}else{
			return 1;
		}
	}

}