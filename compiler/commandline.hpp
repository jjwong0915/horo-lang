#ifndef COMMANDLINE
#define COMMANDLINE

#include <iostream>
#include <cstring>
#include <cstdio>
#include <vector>
#define COMMANDNUM 3

using namespace std;

namespace cmd{

extern const char *command[];

extern const char *commandillustrate[];


void command_help();

bool argument_check(char** parameter,int argc,vector<int> &cmd);

void argument_process(char** parameter,int argc,vector<int> &cmd);
bool mainconsole(int argn,char* argu[]);
}

#endif



