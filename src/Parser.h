#ifndef PARSER_H
#define PARSER_H

#include <stdio.h>
#include <string.h>
#include <vector>
#include <iostream>

#include "CommandShell.h"
#include "Command.h"
#include "Exit.h"
#include "FailConnect.h"
#include "SuccessConnect.h"
#include "NextConnect.h"
#include "TestCommand.h"

using namespace std;

class Parser{
	private:
		char input[100];
		public:
		Parser(vector<char> i){
			int j = 0;
			while(j < i.size()){
				input[j] = i.at(j);
				j++;
			}
			input[j] = '\0';
		}

		//tests if char* parameter is test or [, returns bool
		bool checkTest(char* check){
			if(strcmp(check, "test") == 0 || strcmp(check, "[") == 0){
				return true;
			}
			return false;
		}

		//parses the input string for commands and calls their executes
		vector<char*> parse(){
			char* pch = strtok(input, " \n]#;");
			vector<char*> comslist;	//tokenized strings of user input
			vector<CommandShell*> cmds; //list of commands to be executed after parsing
					
			vector<char*> temp1; //temporary vectors to hold commands for connecting
			vector<char*> temp2;

			CommandShell* tempcom1; //temporary pointers to commands for use in connectors
			CommandShell* tempcom2;
			int locctr = 0;		//location of start of previous command, increment every time something added to cmds
			while(pch != NULL){
				comslist.push_back(pch);
				pch = strtok(NULL, " \n]#;");
			}
			int k = 0;
			while(k < comslist.size()){
				if(strcmp(comslist.at(k), "exit") == 0){
					cmds.push_back(new Exit());
					k++;
				}
				else if(strcmp(comslist.at(k), "||") == 0){
					if(cmds.size() == 0){
						for(int m = 0; m < k; m++){
							temp1.push_back(comslist.at(m));	
						}
						k++;
						if(checkTest(temp1.at(0))){
							tempcom1 = new TestCommand(temp1);
						}
						else{
							tempcom1 = new Command(temp1);
						}
						while(k < comslist.size() && strcmp(comslist.at(k), "&&") != 0 && strcmp(comslist.at(k), "||") != 0){
							if(strcmp(comslist.at(k), "exit") == 0){
								tempcom2 = new Exit();
								k++;
							}
							else{
								temp2.push_back(comslist.at(k));
								k++;
							}
						}
						if(temp2.empty()){
							cmds.push_back(new FailConnect(tempcom1, tempcom2));
						}
						else if (!temp2.empty() && checkTest(temp2.at(0))){
							cmds.push_back(new FailConnect(tempcom1, new TestCommand(temp2)));
						}
						else{
							cmds.push_back(new FailConnect(tempcom1, new Command(temp2)));
						}
						temp1.clear(); temp2.clear(); 
					}
					else{
						k++;
						while(k < comslist.size() && strcmp(comslist.at(k), "&&") != 0 && strcmp(comslist.at(k), "||") != 0){
							if(strcmp(comslist.at(k), "exit") == 0){
								tempcom1 = new Exit();
								k++;
							}
							else{
								temp1.push_back(comslist.at(k));
								k++;
							}
						}
						if(temp1.empty()){
							cmds.push_back(new FailConnect(cmds.at(locctr), tempcom1));
						}
						else if(!temp1.empty() && checkTest(temp1.at(0))){
							cmds.push_back(new FailConnect(cmds.at(locctr), new TestCommand(temp1)));
						}
						else{
							cmds.push_back(new FailConnect(cmds.at(locctr), new Command(temp1)));
						}
						locctr++;
						temp1.clear();
					}
				}
				else if(strcmp(comslist.at(k), "&&") == 0){
					if(cmds.size() == 0){
						for(int n = 0; n < k; n++){
							temp1.push_back(comslist.at(n));
						}
						if(checkTest(temp1.at(0))){
							tempcom1 = new TestCommand(temp1);
						}
						else{
							tempcom1 = new Command(temp1);
						}
						k++;
						while(k < comslist.size() && strcmp(comslist.at(k), "&&") != 0 && strcmp(comslist.at(k), "||") != 0){
							if(strcmp(comslist.at(k), "exit") == 0){
								tempcom2 = new Exit();
								k++;
							}
							else{
								temp2.push_back(comslist.at(k));
								k++;
							}
						}
						if(temp2.empty()){
							cmds.push_back(new SuccessConnect(tempcom1, tempcom2));
						}
						else if(!temp2.empty() && checkTest(temp2.at(0))){
							cmds.push_back(new SuccessConnect(tempcom1, new TestCommand(temp2)));
						}
						else{
							cmds.push_back(new SuccessConnect(tempcom1, new Command(temp2)));
						}
						temp1.clear(); temp2.clear();
					}
					else{
						k++;
						while(k < comslist.size() - 1 && strcmp(comslist.at(k), "&&") != 0 && strcmp(comslist.at(k), "||") != 0){
							if(strcmp(comslist.at(k), "exit") == 0){
								tempcom1 = new Exit();
							}
							else{
								temp1.push_back(comslist.at(k));
								k++;
							}
						}	
						if(temp1.empty()){
							cmds.push_back(new SuccessConnect(cmds.at(locctr), tempcom1));
						}
						else if(!temp1.empty() && checkTest(temp1.at(0))){
							cmds.push_back(new SuccessConnect(cmds.at(locctr), new TestCommand(temp1)));
						}
						else{
							cmds.push_back(new SuccessConnect(cmds.at(locctr), new Command(temp1)));
						}
						locctr++;
						temp1.clear();
					}
				}
				else{
					k++;
				}
			}
			if(cmds.size() == 0){
				if(checkTest(comslist.at(0))){
					cmds.push_back(new TestCommand(comslist));
				}
				else{
					cmds.push_back(new Command(comslist));
				}
			}
			
			cmds.back()->execute();
			cmds.clear();
			return comslist;
			
		}
		
};
#endif
