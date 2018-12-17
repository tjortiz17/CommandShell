#ifndef SUCCESSCONNECT_H
#define SUCCESSCONNECT_H

#include "Connector.h"
#include "CommandShell.h"

class SuccessConnect : public Connector{
	private:
		CommandShell* first;
		CommandShell* second;
	public:
		SuccessConnect(CommandShell* f, CommandShell* s){
			first = f;
			second = s;
		}

		//executes second command if first succeeds, return -1 if error
		int execute(){
			if(first->execute() == 0){
				if(second->execute() == 0){
					return 0;
				}
			}
			return -1;
		}
};
#endif
