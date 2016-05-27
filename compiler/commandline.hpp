#ifndef COMMANDLINE
#define COMMANDLINE

#include <vector>
#define COMMANDNUM 3

using namespace std;

namespace cmd{

	extern const char *command[];

	extern const char *commandillustrate[];

	extern string outputname,ccstd;
	
	extern bool compile;

	void command_help();

	bool argument_check(char** parameter,int argc,vector<int> &cmd);

	void argument_process(char** parameter,int argc,vector<int> &cmd);

	bool mainconsole(int argn,char* argu[]);

}

#endif



