#include "orop.h"

orOp::orOp()
{

}

bool orOp::execute()
{
    if(!(leftChild->execute()))
    {
        rightChild->execute();
        return true;
    }
    return false;
}

orOp::~orOp()
{

}


