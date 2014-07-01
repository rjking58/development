// Binary Tree Traversal example
// compiled and tested in Microsoft Visual C++ .net (2003)
// Author: Richard King
//    revision history:
//          2006-Jun-20:  initial creation.

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#include <iostream>



// struct BinaryNode
//    --implement simple BinaryNode for purposes of demonstrating preorder 
//      traversal
//
//  possible improvements:
//     o Implement unique node numbering to guarantee no overlap of node 
//       numbers (i.e. don't make user responsible for making sure 
//       uniqueness is guaranteed)
//     o container class that implements basic tree mechanisms and uses 
//       struct privately (implement basic data hiding mechanisms)   
//     o copy semantics for container class (i.e. copyTree).

struct BinaryNode1
{
public:
   // constructor
   // verify pointers are properly set to null on creation.
   // NodeNum is numerical identifier of the node.
   // 
   BinaryNode1(int NodeNum)
      :  m_right(0),
         m_left(0),
         m_nodeNumber(NodeNum)
   {
   }
   
   void printSelf()
   {
      std::cout << "Node(" << m_nodeNumber << ")" << std::endl;
   }
   
   BinaryNode1 *m_right;
   BinaryNode1 *m_left;
   
private:
   int        m_nodeNumber;
   
   BinaryNode1(BinaryNode1 &node); // copy semantics NOT supported.
   BinaryNode1 & operator=(BinaryNode1 &node);  // copy semantics NOT supported.
   
};


// Basic preorder demonstration
//  Possible improvements:
//     o Implement using Iterator pattern based on an abstract iterator class 
//       so that other traversal mechanisms can be implemented
//     o don't use this, use STL!  :)
//     o this is done recursively, which depends on the call stack of the 
//       architecture where it is implemented (which is inherently 
//       limited and possibly dangerous).. implement using non-recursive 
//       data structuring to allow for traversal of very deep trees
//
void BinaryNode_preorder(BinaryNode1 *head)
{
   BinaryNode1 *curr_node = head;
   // traverse preorder..
   if (head != 0)
   {
      curr_node->printSelf();
      BinaryNode_preorder(curr_node->m_left);
      BinaryNode_preorder(curr_node->m_right);
   }
}

// Tear down of binary tree. 'postorder' traversal style.
//  Possible improvements
//    o same as preorder traversal above.
void BinaryNode_deleteTree(BinaryNode1 *head)
{
   BinaryNode1 *curr_node = head;
   if (head != 0)
   {
      BinaryNode_deleteTree(curr_node->m_left);
      BinaryNode_deleteTree(curr_node->m_right);
      std::cout << "deleting: ";
      curr_node->printSelf();
      delete curr_node;
   }
}

// test our tree traversal.
//   Possible improvements:
//   move test cases into CPPTest or other test case framework for repeatability.
void main(void)
{
   // build tree of this form:
   //              1
   //          /       \
   //         2        3
   //       /   \     /   \
   //      4  (nul) (nul) 5                

   // for this tree.. preorder should give:
   // 1,2,4,3,5
   {
      // 
      BinaryNode1 *head_ptr = 0;
      head_ptr = new BinaryNode1(1);
      
      int NodeNum = 2;                           
      
      BinaryNode1 * tmp_l = new BinaryNode1(NodeNum++);
      BinaryNode1 * tmp_r = new BinaryNode1(NodeNum++);
      
      head_ptr->m_right = tmp_r;
      head_ptr->m_left = tmp_l;
      tmp_l->m_left = new BinaryNode1(NodeNum++);
      tmp_r->m_right = new BinaryNode1(NodeNum++);
      
      BinaryNode_preorder(head_ptr);
      BinaryNode_deleteTree(head_ptr);
   }

   // now build tree of this form:
   //              1
   //          /       \
   //         (nul)      2
   //                 /   \
   //                (nul) 3                
   //                   /   \
   //                  (nul) 4                
   // for this tree.. preorder should give:
   // 1,2,3,4

   {
      BinaryNode1 *head_ptr = 0;
      head_ptr = new BinaryNode1(1);
      
      int NodeNum = 2;                           
      BinaryNode1 * tmp_r = new BinaryNode1(NodeNum++);
      head_ptr->m_right = tmp_r;
      BinaryNode1 * tmp_r2 = new BinaryNode1(NodeNum++);
      tmp_r->m_right = tmp_r2;
      tmp_r2->m_right = new BinaryNode1(NodeNum++);
      BinaryNode_preorder(head_ptr);
      BinaryNode_deleteTree(head_ptr);
   }
   
   // make sure we deleted all nodes!
   _CrtDumpMemoryLeaks();
}
