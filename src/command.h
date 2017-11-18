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


class TestCmd:public Base
{
  /*
   * steps: creating the test object
   * -check if its valid command
   * 1st strtok -> [ or test
   * 2nd strtok -> command
   * maybe check if a valid flag right here
   *
   * maybe because perror is within the class, the error should be
   * within the Test class
   * notes about Test
   * In Assignment 3:
   *    -uses int stat(const char *path, struct stat *buf); function
   *    -MACROS: S_ISDIR -> is directory
   *             S_ISREG -> is regular file
   *    -flags are: -e (check if file exists),
   *                -f (if exists and reg file),
   *                -d (if exists or directory)
   *    -output: (True) or (False)
   *
   *
   */
  public:
    TestCmd(string s);
    ~TestCmd();
    bool execute();
  private:
    string argument;
    string flag;
    vector<string> argumentList;

};


#endif
