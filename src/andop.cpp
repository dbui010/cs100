#include "andop.h"

AndOp::AndOp()
{
}

bool AndOp::execute()
{
    /*
 *      * Traversal: INORDER
 *           * execute summary:
 *                * execute left child
 *                     * check left child passed
 *                          * if yes -> execute right child
 *                               * if no -> nothing
 *                                    */

    if(leftChild->execute()){
        if(rightChild->execute())
	{
        	return true;
	}
	else
	{
		return false;
	}
    }

//if it fails

    return false;


}

AndOp::~AndOp()
{

}


