#include "semicolon.h"


SemiColon::SemiColon()
{

}

bool SemiColon::execute()
{
    leftChild->execute();
    if(rightChild->execute())
	return true;
    return false;
}

SemiColon::~SemiColon()
{

}


