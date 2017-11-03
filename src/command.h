#ifndef COMMAND_H
#define COMMAND_H
#include "base.h"

class command: public Base
{
public:

    command(char* cm);
    bool execute(); //executes the command...
    ~command();

private:
    char* cmd; //command and arguments
    bool completed; //status of the cmd (if it failed or not), might not be necessary

};

#endif // COMMAND_H

