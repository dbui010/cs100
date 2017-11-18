#include "command.h"
#include <cstring>

#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

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

ExitCmd::ExitCmd(){}

bool ExitCmd::execute()
{
    exit(0);
}

ExitCmd::~ExitCmd(){}

//===========================TEST========================
TestCmd::TestCmd(string s){


    argument = s;
    string p;
    flag = string("");
    bool flag_set = false;
while(s.substr(0,1) == " ")
    {
        s= s.substr(1,s.length());
    }
    if(s.substr(0,1) == "[")
    {
        //[ function ]
        s = s.substr(1, s.length());
        s = s.substr(0,s.find_last_of(']')-1);
    }

    if(s.substr(0,1) == "t")
    {
        //test flag path
        string t = "test";
        s= s.substr(t.length(),s.length());
    }

   while(s.length() != 0)
    {
        if(s.substr(0,1)== " ")
        {
            s=s.substr(1,s.length());
        }

        else{

            string p = s.substr(0,s.find_first_of(" "));
            if(p.substr(0,1) == "-" && flag == "")
            {
                //assume its the flag
                flag = p;
		flag_set = true;

            }
            else{

                argumentList.push_back(p);

            }

             s = s.substr(p.length(), s.length());


        }

    }

    if(!flag_set){
	flag = "-e";
    }

}
TestCmd::~TestCmd(){}
bool TestCmd::execute(){

//  struct stat sb;
  struct stat sb;

  if(argumentList.size() == 0)
  {
	cout<<"NO FILEPATH GVEN for "<<argument<<endl;
	return false;
  }
  if(argumentList.size() > 1)
  {
  	cout<<"TOO MANY ARGUMENTS for "<<argument<<endl;
	return false;
  }
  
  int value = stat(argumentList[0].c_str(), &sb);

  if(value == -1)
  {
  	cout<<"(False)"<<endl;
	return false;
  }
  
  if(flag =="-e")
  {
	cout<<"(True)"<<endl;
	return true;
  }

 else if(flag == "-f")
 {
    if(S_ISREG(sb.st_mode))
    {
       cout<<"(True)"<<endl;
       return true;
    } 
    else
    {
	cout<<"(False)"<<endl;
	return false;
    }
 }

 else if(flag == "-d")
 {
     if(S_ISDIR(sb.st_mode))
      {
        cout<<"(True)"<<endl;
        return true;
      }
      else
      {
        cout<<"(False)"<<endl;
        return false;
      } 	
 
 cout<<"(False)"<<endl;
 return false;	
 }
//  if (stat(argv[1], &sb) == -1) {
//           perror("stat");
//           return false;
//       }

////      printf("File type:                ");

//      switch (sb.st_mode & S_IFMT) {
//       case S_IFDIR:
//       case S_IFREG:
//            cout<<"(True)"<<endl;
//            break;//       default:
//            cout<<"(False)"<<endl;
//            break;
//       }

//      return true;

}




