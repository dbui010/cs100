# rshell-kd
rshell-kd created by GitHub Classroom

# Authors
Kevin Frazier, Dinh Bui

### Installation

git clone https://github.com/cs100/rshell-kd.git   
cd rshell-kd/   
git checkout assn2  
cd src/   
make   
./rshell   


### Running a Basic Command Shell
This C++ command shell is designed to accept a one-line command argument in Bash from the user. The one-line argument consists of
multiple commands followed by connectors. Those connectors determine how the command is executed.

### Shell Process
The command shell has three main processes to execute the user's commands. The first process is the parsing the commands into postOrder notation. Parsing the commands use various functions shown in the docs folder to separate connectors and command arguments. The second process is storing all the parsed commands into an expression tree. All parsed commands convert into objects called Base and connect with one another through inheritance. The third process is executing through all the objects. By using a composite design pattern, every commands and connectors execute through the tree by calling on a derived Base class (see docs folder for more information). By executing through each command argument, an application in the Bash source file is called on to run the command. The user then receives the results on the terminal.

### Updates
Command shell now takes higher-order connectors such as parentheses into consideration. The command shell also includes the exit command. In addition, command shell can test to see if pathname exists by using test commands and flags.

### Known bugs
We cannot execute through the bin/rshell. The program must be made and ran through the ../src directory of rshell. There are no tags for the program so there only way to run the program is exactly through the installation provided. In addition, Windows and Mac users may need to install Git before downloading this repository if their operating system does not support Linux.

### Improvements
Parsing source code in main.cpp can be simplified by using fewer loops to improve execution efficiency. Also, when parsing, the program can reduce memory allocations by not using vectors to separate commands and connectors.
