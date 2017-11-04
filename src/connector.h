#ifndef CONNECTOR_H
#define CONNECTOR_H

#include "base.h"


/*
 * This should breakdown into more subclasses
 * &&
 * ||
 * ;
 * Different implementations
 */
class connector:public Base
{
public:
    connector();
    connector(Base* left, Base* right);
    virtual bool execute()=0;
    void assignChildren(Base* left, Base*right);

    ~connector();

protected:
    Base* leftChild;
    Base* rightChild; //should be the commands and connectors only

    /*
     *
     * Connector     or   Connector
     *  /    \           /      \
     * CMD    CMD   Connector   CMD
     *
     */
};

#endif // CONNECTOR_H

