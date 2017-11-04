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
