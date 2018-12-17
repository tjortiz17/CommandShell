#ifndef FAILCONNECT_H
#define FAILCONNECT_H

#include "Connector.h"
#include "CommandShell.h"
class FailConnect : public Connector {
	private:
		CommandShell* first;
		CommandShell* second;
	public:
		FailConnect(CommandShell* f, CommandShell* s){
			first = f;
			second = s;
		}

		//executes by only continuing to next command if the first fails
		//returns -1 if cannot execute
		int execute(){
			if(first->execute() == -1){
				return second->execute();
			}
			else{
				return 0;
			}
		}
};
#endif
