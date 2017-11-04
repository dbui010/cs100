#ifndef SEMICOLON_H
#define SEMICOLON_H
#include "connector.h"

class SemiColon:public connector
{
public:
    SemiColon();
    SemiColon(Base* left, Base* right):connector(left,right){}
    bool execute();
    /*
     * execute summary:
     * execute left child
     * execute right child
     */

    ~SemiColon();
};

#endif // SEMICOLON_H

