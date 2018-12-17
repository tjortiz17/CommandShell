#ifndef TEST_COMMAND_H
#define TEST_COMMAND_H

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <vector>
#include <stdio.h>
#include <string.h>
#include "Command.h"

class TestCommand : public Command {
	private:
		vector<char*> cmd;
	public: 
		TestCommand(vector<char*> in){
			cmd = in;
		};
	
		int execute(){
			struct stat sb;
			int k = cmd.size() - 1;
			/*if(stat(cmd.at(k), &sb) == -1){
				cout << "(False)" << endl;
				return -1;
			}*/
			//else{
				stat(cmd.at(k), &sb);
				if(strcmp(cmd.at(1), "-f") == 0){
					if(S_ISREG(sb.st_mode)){
						cout << "(True)" << endl;
						return 0;
					}
					else{
						cout << "(False)" << endl;
						return -1;
					}
				}
				else if(strcmp(cmd.at(1), "-d") == 0){
					if(S_ISDIR(sb.st_mode)){
						cout << "(True)" << endl;
						return 0;
					}
					else{
						cout << "(False)" << endl;
						return -1;
					}
					
				}
				else{
					if(S_ISREG(sb.st_mode) || S_ISDIR(sb.st_mode)){
						cout << "(True)" << endl;
						return 0;
					}
					else{
						cout << "(False)" << endl;
						return -1;
					}
				}
			}
		//}
};

#endif 
