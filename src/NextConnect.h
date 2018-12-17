#ifndef NEXTCONNECT_H
#define NEXTCONNECT_H

#include "Connector.h"
#include "CommandShell.h"

class NextConnect : public Connector{
	private:
		CommandShell* first;
		CommandShell* second;
	public:
		NextConnect(CommandShell* f, CommandShell* s){
			first = f;
			second = s;
		}

		//executes second command regardless of outcome of first, return -1 if error
		int execute(){
			first->execute();
			second->execute();
		}
};
#endif
