#include "orop.h"
#include "connector.h"

orOp::orOp()
{

}


bool orOp::execute()
{
    bool status = true;
      if(!leftChild->execute())
      {
        if(!rightChild->execute())
        {
          status = false;
        }
      }
      return status;
}

orOp::~orOp()
{

}


