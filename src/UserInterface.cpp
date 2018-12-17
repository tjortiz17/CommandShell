#ifndef USERINTERFACE_CPP
#define USERINTERFACE_CPP

#include "CommandShell.h"
#include "Parser.h"

#include <iostream>
#include <unistd.h>
#include <limits.h>
#include <vector>
using namespace std;

main(){

	vector<char> userinput;
	char hostname[HOST_NAME_MAX];
	char username[LOGIN_NAME_MAX];
	
	gethostname(hostname, HOST_NAME_MAX); //host name for device running program
	getlogin_r(username, LOGIN_NAME_MAX); //username of person on device

	Parser* p;

	int k = -1; //counter to check for enter input
	while(true){ //only exit on exit command
 		cout << username << "@" << hostname << "$ ";
 		do{
			userinput.push_back(getchar());
			k++;
			if(userinput.at(k) == ';'){
				p = new Parser(userinput);
				p->parse();
				userinput.clear();
				k = 0 ;
				userinput.push_back(' ');
			}
		}while(userinput.at(k) != '\n'); //user input keeps going until enter is hit
		p = new Parser(userinput);
		p->parse();
		userinput.clear();
		k = -1;
	}
	return 0;
}
#endif

