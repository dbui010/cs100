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
        rightChild->execute();
        return true;
    }//if it passes
    return false;


}

AndOp::~AndOp()
{

}


