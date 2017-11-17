#ifndef Cmd_h
#define Cmd_h
#include <unistd.h>
#include <iostream>
#include <stdio.h>
#include <sys/wait.h>
#include <sys/types.h>
#include "base.h"
#include <iostream>
#include <queue>
#include <stack>
using namespace std;

class Cmd: public Base
{
  protected:
  char * command;
  queue<char *> arg;

  public:
  Cmd();
  Cmd(string);
  ~Cmd();

  virtual bool execute();

};

class ExitCmd: public Base
{

  public:
  ExitCmd();
  ~ExitCmd();
  bool execute();


};


#endif
