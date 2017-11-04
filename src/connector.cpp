#include "connector.h"


connector::connector()
{

}

connector::connector(Base* left, Base* right)
{
    this->assignChildren(left,right);
}

void connector::assignChildren(Base* left, Base*right)
{
    leftChild = left;
    rightChild = right;
}


connector::~connector()
{

}


