#include <iostream>
#include <queue>
#include <stack>
#include <stdio.h>
#include "base.h"
#include "command.h"
#include "orop.h"
#include "andop.h"
#include "semicolon.h"
#include <vector>
#include <cstring>
#include <string>

#include <algorithm>
#include <sstream>
#include <unistd.h>

using namespace std;

/*
 * Note:
 * So I have the classes available to construct the tree for you
 * Here is the heiarchy for the classes i made
 *
 * class: Base -> subclasses: command and connector
 * class: connector -> subclasses: AndOp (&&), OrOp(||), SemiColon
 *
 * Therefore, all the commands of the input are put into the command object (look at the constructor)
 * Therefore, all the connectors of the input are put into the connector object (look at the constructor too)
 *
 * So your goal: Infix to post
 *
 * 1,2,3,4 -> commands -> i.e. ls -a, echo b, ls,
 *
 * process:
 * 1 && 2 || 3; 4  //infix
 * 1 && 2 || 3 ; 4 ; //separating the ; connector from the 3 command AND ; at the end to make it easier to process
 * 1 2 && 3 || 4 ; //postfix
 *
 * Afterwards: you tokenize the char string
 * [ [1], [2], [&&], [3], [||], [4], [;] ] //postfix tokenized string
 * make a queue<char*> then use the push(char*) function through each index from left to right
 *(look up the push function on c++ reference)
 *
 * To make the tree
 * check the contents within the index of the iteration
 * if its a command -> construct a command object (look at constructor)
 * if its a connector -> construct a andOP, orOP, or SemiColon object based on what the connector is (look at constructor)
 *
 * DONE!
 *
 */

void readCommandLine(string &);
void separateConnectors(string &);
char** tokenize_input(string &);
queue<string> tokenize(string &);

Base* generateTree(queue<string>& Q);
Base* exitorCommand(string s);

int main () {

    while(1)
    {
        string input;
        queue<string> postOrder;
        Base* head;
        //char **args;
        //int argsSize = 0;

        readCommandLine(input);
        separateConnectors(input);
        postOrder = tokenize(input);
        head = generateTree(postOrder);
        head->execute();
        delete head;
        head =NULL;
    }

    //tokenize(input);
    //args = tokenize_input(input);

    //char *execArgs[] = { "ls", "-a", NULL };
    //execvp(args[0], args);

    return 0;
}

void readCommandLine(string &input) {
    cout << "$ ";

    // Read the line of command from user
    getline(cin,input);

    // Truncate Bash comment
    if (input.find("#") != string::npos) {
        input.erase(input.find("#"),input.length());
    }
}

void separateConnectors(string &input) {
    //Read input to a stream so split the commands
    stringstream stream(input);
    string splitInput;
    vector<string> vectorSubCMD;

    //Store the commands into a vector
    while(getline(stream,splitInput, ' ')) {
        vectorSubCMD.push_back(splitInput);
    }

    //Add space right before semicolon for all cmd;
    for (int i = 0; i < vectorSubCMD.size(); i++) {
        //Do not include space commands that are size 0
        if(vectorSubCMD.at(i).size() > 0) {
            //Check if command in vector has a semicolon at the end
            if(vectorSubCMD.at(i).at(vectorSubCMD.at(i).size()-1) == ';') {
                vectorSubCMD.at(i).pop_back();
                vectorSubCMD.at(i).push_back('#');
                vectorSubCMD.at(i).push_back(';');
                vectorSubCMD.at(i).push_back('#');
            }
            //Check if connector && exists
            else if (vectorSubCMD.at(i) == "&&") {
                    vectorSubCMD.at(i).pop_back();
                    vectorSubCMD.at(i).pop_back();

                    vectorSubCMD.at(i).push_back('#');
                    vectorSubCMD.at(i).push_back('&');
                    vectorSubCMD.at(i).push_back('&');
                    vectorSubCMD.at(i).push_back('#');
            }
            //Check if connector || exists
            else if (vectorSubCMD.at(i) == "||") {
                    vectorSubCMD.at(i).pop_back();
                    vectorSubCMD.at(i).pop_back();

                    vectorSubCMD.at(i).push_back('#');
                    vectorSubCMD.at(i).push_back('|');
                    vectorSubCMD.at(i).push_back('|');
                    vectorSubCMD.at(i).push_back('#');
            }
        }
    }

    //Empty input string to store vector of subcommands
    input = "";
    for (int i = 0; i < vectorSubCMD.size(); i++) {

            input += vectorSubCMD.at(i);
            input += " ";
    }
}
queue<string> tokenize(string& input) {
    //Store subcommands into inOrder queue
    queue<string> inOrder;
    //Store connectors into connector stack
    stack<string> connector;
    //Store subcommands into postOrder queue
    queue<string> postOrder;
    //Read input to a stream so split the commands
    stringstream stream(input);
    string splitInput;

    //Store the commands into the inorder queue
    while (getline(stream,splitInput, '#')) {
        inOrder.push(splitInput);
    }

    while (!inOrder.empty()) {
        //Convert from inOrder to postOrder
        //Check if front of inOrder queue is a command
        if (inOrder.front() != "&&" && inOrder.front() != "||"
            && inOrder.front() != ";") {
            // Pop command from inOrder into postOrder
            postOrder.push(inOrder.front());
            inOrder.pop();
        }
        //If front of inOrder queue is a connector
        else {
            //Push connector to stack if stack is empty
            if(connector.empty()) {
                connector.push(inOrder.front());
                inOrder.pop();
            }
            //Pop stack connector into postOrder
            //and pop inOrder connector into stack
            //if stack is not empty
            else {
                postOrder.push(connector.top());
                connector.pop();
                connector.push(inOrder.front());
                inOrder.pop();
            }
        }
    }
    //Empty the stack into postOrder
    while (!connector.empty()) {
        postOrder.push(connector.top());
        connector.pop();
    }

    return postOrder;
}
char** tokenize_input(string& input) {
    // Convert input string into c-string
    char* cinput = (char*)input.c_str();

    // Create array of char* pointer to store each cmd/arg/con
    char **truncateCMD = new char *[input.length()+1];
    int truncateSize = 0;

    // Tokenize each cmd/arg/con by space delimiter
    char *p = strtok(cinput," ");

    // Store each cmd/arg/con into the array of char* pointers
    while (p!=0) {
        truncateCMD[truncateSize] = p;
        p = strtok(NULL,"#");
        truncateSize++;
    }
    // Add null at the end of array of pointers
    truncateCMD[truncateSize] = NULL;

    //Delete c-string to clear memory
    delete[] cinput;

    for (int i = 0; i < truncateSize; i++) {
        //cout << truncateCMD[i] << endl;
    }

    return truncateCMD;
}
Base * exitorCommand(string s)
{
  //variables
  Base * temp;
  char * val;
  char * split, *store;
  store = split = new char[500];
  strcpy(split,s.c_str());
  val = strtok(split," ");
  //create an exit node
  if(string(val) == "exit" || string(val) == "Exit")
  {
   string r = "exit";
   temp = new Cmd(r);
  }

  //create a command node
  else
  {
    temp = new Cmd(s);
  }
  if(store != NULL)
  {
  delete[] store;
  }
  return temp;

}

Base* generateTree(queue<string>& Q)
{
//Assume its already in postfix
//  vector<string> v = infix_to_postfix(vec);
  //this stack will create our tree
  stack<Base*> S;
  unsigned index = 0;
  while(!Q.empty())
  {
      //if || op
    if(Q.front() == "||")
    {
      if(S.size()>1)
      {
        Base* r = S.top();
        S.pop();
        Base* l = S.top();
        S.pop();
        Base* temp = new orOp(l,r);
        S.push(temp);
      }
    }
    //if && op
    else if(Q.front() == "&&")
    {
      if(S.size()>1)
      {
        Base* r = S.top();
        S.pop();
        Base* l = S.top();
        S.pop();
        Base* temp = new AndOp(l,r);
        S.push(temp);
      }
    }

    //if ; op
    else if( Q.front() == ";")
    {
      if(S.size()>1)
      {
        Base* r = S.top();
        S.pop();
        Base* l = S.top();
        S.pop();
        Base* temp = new SemiColon(l,r);
        S.push(temp);
      }
    }


    //if command
    else
    {
      //will create a cmd node, exit node, or test node
      Base* temp = exitorCommand(Q.front());
      S.push(temp);
    }
    index++;
  }
  //if there is a node, return it
  if(S.size())
  {
  return S.top();
  }
  //if there is not, then create an empty node to execute
  else
  {
    Base* p = new Cmd();
    return p;
  }
}

