#include "semicolon.h"

SemiColon::SemiColon()
{

}

bool SemiColon::execute()
{
    leftChild->execute();
    rightChild->execute();

}

SemiColon::~SemiColon()
{

}


