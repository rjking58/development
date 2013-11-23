#include <iostream>
using namespace std;
#include <string.h>

#define MAX_CHILDCOUNT 100



class treenodeAction;

class treenode
{
   friend class BaseTreenodeAction;

private:
   char     m_myName[100];
   treenode *m_myParent;
   // this is TOTALLY quick and dirty.. don't try this at home kids!
   treenode *m_myChildren[100];
   int      m_childCount;
   int      m_depth;

public:        
   treenode(char *name,treenode *parent)
   :  m_childCount(0),
      m_myParent(0),
      m_depth(0)

   {
      strcpy(m_myName,name);
      m_myParent = parent;
      for (int x = 0; x < MAX_CHILDCOUNT; x++)
      {
         m_myChildren[x] = 0;
      }

      if (parent)
      {
         parent->addChild(this);
      }
   }
   
   ~treenode()
   {
      for (int x = 0; x < m_childCount; x++)
      {
         delete m_myChildren[x];
         m_myChildren[x] = 0;
      }
   }
   void addChild(treenode *child)
   {
      if (m_childCount + 1 >=MAX_CHILDCOUNT)
      {
         cout << "TOO MANY CHILDREN" << endl;
      }
      m_myChildren[m_childCount] = child;
      child->m_myParent = this;
      m_childCount++;
   }


   bool hasMoreChildren(int &currIdx)
   {
      return  currIdx < m_childCount;
   }

   void printName()
   {
      cout << m_myName ;
   }

   void setDepth(int depth)
   {
      m_depth = depth;
   }
   void getDepth(int depth)
   {
      return m_depth;
   }
   
   void printDepth()
   {
      cout << m_depth;
   }
};

class BaseTreenodeAction
{
   private:

   public:
   
   BaseTreenodeAction()
   {
   }
         
         
   virtual void Action(int depth,treenode* curr_node,treenode* curr_child)
   {
   }


   void walkTreeWithInnerTree(int depth, treenode *tn)
   {
      int currChild = 0;
      depth ++;

      // first the parent..      
      
      walkFullSubTree(depth,tn,tn);
      
      for (currChild = 0; currChild < tn->m_childCount; currChild++)
      {
         // then every child..
         walkTreeWithInnerTree(depth,tn->m_myChildren[currChild]);
      }
   
   }
   void walkFullSubTree(int depth, treenode *tn, treenode *next_node)
   {
      int currChild = 0;


      if (     (  tn != next_node      )
          ||   (     (tn == next_node)
                  && (depth == 1     )
                                       )
         )                             
      {
         Action(depth,tn,next_node);
      }   

      depth ++;
      
      for (currChild = 0; currChild < next_node->m_childCount; currChild++)
      {
         walkFullSubTree(depth,tn,next_node->m_myChildren[currChild]);
      }
      
      // check for no child count.. that means this is a leaf and should be written..
      if (     (!(next_node->m_childCount))
            && (tn == next_node           )
         )
      {
         Action(depth,next_node,next_node);
      }
   }
   
   void walkChildrenWithNode(int depth,treenode *tn)
   {
      int currChild = 0;
      depth ++;

      Action(depth,tn,0);
      
      for (currChild = 0; currChild < tn->m_childCount; currChild++)
      {
         walkChildrenWithNode(depth,tn->m_myChildren[currChild]);
      }
   }
   void walkChildrenWithParentChild(int depth,treenode *tn)
   {
      int currChild = 0;
      depth ++;

      
      for (currChild = 0; currChild < tn->m_childCount; currChild++)
      {
         Action(depth,tn,tn->m_myChildren[currChild]);
         walkChildrenWithParentChild(depth,tn->m_myChildren[currChild]);
      }
   }
   
};

class treenodeDecoratedAction : public BaseTreenodeAction
{
   private:
   BaseTreenodeAction *m_currentAction;
   
   public:
   treenodeDecoratedAction(BaseTreenodeAction *currentAction)
   :  m_currentAction(currentAction)
   {
   }
   
   virtual ~treenodeDecoratedAction()
   {
      delete m_currentAction;
   }
   virtual void Action(int depth,treenode* curr_node,treenode* curr_child)
   {
      m_currentAction->Action(depth,curr_node,curr_child);
   }
};


class updateDepthAction : public treenodeDecoratedAction
{
public:
   updateDepthAction(BaseTreenodeAction *currentAction) 
   :  treenodeDecoratedAction(currentAction)
   {
   }
   void Action(int depth,treenode* curr_node,treenode* curr_child) 
   {
      treenodeDecoratedAction::Action(depth,curr_node,curr_child);
      curr_node->setDepth(depth);
   }
};
class printParentDepthAction : public treenodeDecoratedAction
{
public:
   printParentDepthAction(BaseTreenodeAction *currentAction) 
   :  treenodeDecoratedAction(currentAction)
   {
   }
   void Action(int depth,treenode* curr_node,treenode* curr_child) 
   {
      treenodeDecoratedAction::Action(depth,curr_node,curr_child);
      curr_node->printDepth();
   }
};

class printParentNameAction : public treenodeDecoratedAction
{
public:
   printParentNameAction(BaseTreenodeAction *currentAction) 
   :  treenodeDecoratedAction(currentAction)
   {
   }
   void Action(int depth,treenode* curr_node,treenode* curr_child) 
   {
      treenodeDecoratedAction::Action(depth,curr_node,curr_child);
      curr_node->printName();
   }
};
class printChildNameAction : public treenodeDecoratedAction
{
public:
   printChildNameAction(BaseTreenodeAction *currentAction) 
   :  treenodeDecoratedAction(currentAction)
   {
   }
   void Action(int depth,treenode* curr_node,treenode* curr_child) 
   {
      treenodeDecoratedAction::Action(depth,curr_node,curr_child);
      curr_child->printName();
   }
};
class printChildDepthAction : public treenodeDecoratedAction
{
public:
   printChildDepthAction(BaseTreenodeAction *currentAction) 
   :  treenodeDecoratedAction(currentAction)
   {
   }
   void Action(int depth,treenode* curr_node,treenode* curr_child) 
   {
      treenodeDecoratedAction::Action(depth,curr_node,curr_child);
      curr_child->printDepth();
   }
};

class printCommaAction : public treenodeDecoratedAction
{
public:
   printCommaAction(BaseTreenodeAction *currentAction) 
   :  treenodeDecoratedAction(currentAction)
   {
   }
   void Action(int depth,treenode* curr_node,treenode* curr_child) 
   {
      treenodeDecoratedAction::Action(depth,curr_node,curr_child);
      cout << ",";
   }
};

class printENDLAction : public treenodeDecoratedAction
{
public:
   printENDLAction(BaseTreenodeAction *currentAction) 
   :  treenodeDecoratedAction(currentAction)
   {
   }
   void Action(int depth,treenode* curr_node,treenode* curr_child) 
   {
      treenodeDecoratedAction::Action(depth,curr_node,curr_child);
      cout << endl;
   }
};

class printSingleDepthAction : public treenodeDecoratedAction
{
public:
   printSingleDepthAction(BaseTreenodeAction *currentAction) 
   :  treenodeDecoratedAction(currentAction)
   {
   }
   void Action(int depth,treenode* curr_node,treenode* curr_child) 
   {
      treenodeDecoratedAction::Action(depth,curr_node,curr_child);
      if ( (curr_child->getDepth() - curr_node->getDepth()) == 1 )
      {
         cout << "'Y'";
      }
      else
      {
         cout << "'N'";
      }
      
      
   }
};

   
void main()
{

   treenode *topNode;
   treenode *year1997;
   treenode *year1998;
   treenode *year1999;
   treenode *year2000;

   topNode = new treenode("v_top_hier_node",0);
   

   year1997 = new treenode("v_year1997",0);
   year1998 = new treenode("v_year1998",0);
   year1999 = new treenode("v_year1999",0);
   year2000 = new treenode("v_year2000",0);

   topNode->addChild(year1997);
   topNode->addChild(year1998);
   topNode->addChild(year1999);
   topNode->addChild(year2000);


   treenode *currQtr;
  
   currQtr = new treenode("v_Q4_1997",year1997);
   currQtr->addChild(new treenode("v_M12_1997",0));

   currQtr = new treenode("v_Q1_1998",year1998);
   currQtr->addChild(new treenode("v_M01_1998",0));
   currQtr->addChild(new treenode("v_M02_1998",0));
   currQtr->addChild(new treenode("v_M03_1998",0));
   
   currQtr = new treenode("v_Q2_1998",year1998);
   currQtr->addChild(new treenode("v_M04_1998",0));
   currQtr->addChild(new treenode("v_M05_1998",0));
   currQtr->addChild(new treenode("v_M06_1998",0));
   
   currQtr = new treenode("v_Q3_1998",year1998);
   currQtr->addChild(new treenode("v_M07_1998",0));
   currQtr->addChild(new treenode("v_M08_1998",0));
   currQtr->addChild(new treenode("v_M09_1998",0));
   
   currQtr = new treenode("v_Q4_1998",year1998);
   currQtr->addChild(new treenode("v_M10_1998",0));
   currQtr->addChild(new treenode("v_M11_1998",0));
   currQtr->addChild(new treenode("v_M12_1998",0));
   
   
   currQtr = new treenode("v_Q1_1999",year1999);
   currQtr->addChild(new treenode("v_M01_1999",0));
   currQtr->addChild(new treenode("v_M02_1999",0));
   currQtr->addChild(new treenode("v_M03_1999",0));
   currQtr->addChild(new treenode("v_M04_1999",0));
   currQtr->addChild(new treenode("v_M05_1999",0));
   
   currQtr = new treenode("v_Q2_1999",year1999);
   currQtr->addChild(new treenode("v_M06_1999",0));
   
   currQtr = new treenode("v_Q3_1999",year1999);
   currQtr->addChild(new treenode("v_M07_1999",0));
   
   currQtr = new treenode("v_Q4_1999",year1999);
   currQtr->addChild(new treenode("v_M08_1999",0));
   currQtr->addChild(new treenode("v_M09_1999",0));
   currQtr->addChild(new treenode("v_M10_1999",0));
   currQtr->addChild(new treenode("v_M11_1999",0));
   currQtr->addChild(new treenode("v_M12_1999",0));
   
   
   currQtr = new treenode("v_Q1_2000",year2000);
   currQtr->addChild(new treenode("v_M01_2000",0));
   currQtr->addChild(new treenode("v_M02_2000",0));
   currQtr->addChild(new treenode("v_M03_2000",0));
   
   currQtr = new treenode("v_Q2_2000",year2000);
   currQtr->addChild(new treenode("v_M04_2000",0));
   currQtr->addChild(new treenode("v_M05_2000",0));
   currQtr->addChild(new treenode("v_M06_2000",0));
   
   currQtr = new treenode("v_Q3_2000",year2000);
   currQtr->addChild(new treenode("v_M07_2000",0));
   currQtr->addChild(new treenode("v_M08_2000",0));
   currQtr->addChild(new treenode("v_M09_2000",0));
   
   currQtr = new treenode("v_Q4_2000",year2000);
   currQtr->addChild(new treenode("v_M10_2000",0));
   currQtr->addChild(new treenode("v_M11_2000",0));
   currQtr->addChild(new treenode("v_M12_2000",0));

   // walk the tree

   // start a walking..

   // depth first..
   // 
   int depth = 0;
   
   BaseTreenodeAction *Actions = new updateDepthAction(new BaseTreenodeAction);
   Actions->walkChildrenWithNode(depth,topNode);
   
   delete Actions;
   Actions = 0;
   
   
   
   Actions = new printENDLAction       (
             new printSingleDepthAction   (
             new printCommaAction            (
             new printChildDepthAction          (
             new printCommaAction                  (
             new printChildNameAction                 (
             new printCommaAction                        (
             new printParentDepthAction                     (
             new printCommaAction                              (
             new printParentNameAction                            (  
             new BaseTreenodeAction                               )
                                                               )
                                                            )
                                                         )   
                                                      )   
                                                   )
                                                )      
                                             )
                                          )
                                       );
                                             
   Actions->walkTreeWithInnerTree(depth, topNode);
 //  Actions->walkFullSubTree(depth,topNode,topNode);
   
   
   
   delete Actions;
   delete topNode;

}