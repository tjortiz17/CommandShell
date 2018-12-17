#ifndef COMMANDSHELL_H
#define COMMANDSHELL_H

class CommandShell{
	private:
		char* commands[];
	public:
		virtual int execute() = 0;
};
#endif
