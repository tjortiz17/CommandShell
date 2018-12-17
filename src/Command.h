#ifndef COMMAND_H
#define COMMAND_H

#include "CommandShell.h"

#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <vector>
#include <stdlib.h>
#include <iostream>

using namespace std;

class Command : public CommandShell {
   private:
   //char** cmds;//[];
   vector<char*> cmds;
   public:
   Command(){};
   Command(vector<char*> array){
     cmds = array;
     cmds.push_back(NULL);
   }


   int execute(){
      char* commands[cmds.size()];
      for(int i = 0; i < cmds.size(); i++){
         commands[i] = cmds.at(i);
      }
 
      pid_t pid;
      int status;
      
      if((pid = fork()) < 0){
         perror("ERROR: Invalid Command\n");
         return -1;
	 exit(0);
      }
      else if (pid == 0){
         if (execvp(commands[0], commands) < 0) { /* execute the command */
	    perror("ERROR: Command failed to execute");
	    return -1;
	    exit(0);
	 }
      }
      else{
         while (wait(&status) != pid);
      }
      return 0;
   }
};

#endif
