# C++ Command Prompt Shell

A program written in C++ to mimic some of the functionality of a command terminal. Functionality addressed includes bash commands run using the execvp() function from the C++ standard libaray, an additional functionality for the test command that will actually print if the test returns true or false, and an exit command. Additional functionality includes the ability to use connectors "&& || ;" to string together as many commands as needed.

Current bugs: exit command must be called once for every failed command attempted before it is able to close out the program
