#include "command.h"
#include <cstring>

Cmd::Cmd()
{
  command = NULL;
}

Cmd::Cmd(string cmd)
{
  this->command = NULL;
  string temp = "";
  char spot;
  for(unsigned i = 0; i < cmd.size(); ++i)
  {
    spot = cmd.at(i);
    //if spot is a space
    if(spot == ' ')
    {
      if(temp!= "")
      {
        char * a = new char [temp.size()+1];
        memcpy(a, temp.c_str(), temp.size() + 1);
        if(command == NULL)
        {
          command = a;
        }
        else
        {
          arg.push(a);
        }
      }
      temp = "";
    }
    //if space is a letter
    else
    {
    temp+=spot;
    }
  }
  //if the foor loop ends but the temp string
  //has not been cleared
  if(temp != "")
  {
    char * a = new char [temp.size()+1];
    memcpy(a, temp.c_str(), temp.size() + 1);
    if(command == NULL)
    {
      command = a;
    }
    else
    {
      arg.push(a);
    }
  }
}

Cmd::~Cmd()
{
  if(command != NULL)
  {
    delete[] command;
  }
  while(arg.size() > 0)
  {
     char * a = arg.front();
     arg.pop();
     delete[] a;
  }
}


bool Cmd::execute()
{
    bool status = true;
    char * list[500];
    int i = 1;
    queue<char * > arg_2;
    //set list[0] to the command
    list[0] = command;
    //set the rest to the flags
    while(arg.size() > 0)
    {
      char * a = arg.front();
      arg.pop();
      list[i] = a;
      arg_2.push(a);
      ++i;
    }
    list[i] = NULL;

    while(arg_2.size() > 0)
    {
      char * a = arg_2.front();
      arg_2.pop();
      arg.push(a);
    }


    //fork the process
  pid_t pid = fork();
  //child process
  if(pid == 0)
  {
    int result = execvp(list[0],list);
    if(result == -1)
    {
      string error = "rshell: ";
      error += (string)list[0];
      perror(error.c_str());
      _exit(1);
    }
  }
  //parent process
  else if(pid > 0)
  {
    int child;
    if(waitpid(pid,&child,0) == -1)
    {
      perror("wait failure");
    }
    if(WEXITSTATUS(child))
    {
      status = false;
    }
  }
  return status;
  }
