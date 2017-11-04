#ifndef OROP_H
#define OROP_H
#include "connector.h"

class orOp:public connector
{
public:
    orOp();
    orOp(Base* left, Base* right):connector(left,right){}
    bool execute();

    /*
     *
     * execute summary:
     * execute left child
     * check left child passed
     * if yes -> nothing
     * if no -> execute right child
     *
     */
    ~orOp();
};

#endif // OROP_H

