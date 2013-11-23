using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace MultiNodeTree
{
    /// <summary>
    /// simple multi-node tree implementation.  Supports creating a PreOrder iterator.
    /// </summary>
    class TreeMultiNode<T>
    {
        private T               m_val ;
        List<TreeMultiNode<T>>  m_children = new List<TreeMultiNode<T>>();
        TreeMultiNode<T>        m_parent = null;

        public T Val
        {
            get
            {
                return m_val;
            }
            set
            {
                m_val = value;
            }
        }
        internal List<TreeMultiNode<T>> Children
        {
            get 
            { 
                return m_children; 
            }
        }
        internal TreeMultiNode<T> Parent
        {
            get 
            { 
                return m_parent; 
            }
        }
        public TreeMultiNode(T val)
        {
            m_val       = val;
            m_parent    = null;
        }
        public T GetNode()
        {
            return m_val;
        }
        public void AddNode(TreeMultiNode<T> node)
        {
            node.m_parent = this;
            m_children.Add(node);
        }

        /// <summary>
        /// root is set to the node where the iterator is created..
        /// </summary>
        /// <returns></returns>
        public TreeNodePreOrderIterator GetPreOrderIterator()
        {
            return new TreeNodePreOrderIterator(this);
        }
        public class TreeNodePreOrderIterator
        {
            private TreeMultiNode<T>        m_root          = null;
            private TreeMultiNode<T>        m_current       = null;
            private Stack<TreeMultiNode<T>> m_nextsubtree   = new Stack<TreeMultiNode<T>>();

            public TreeNodePreOrderIterator(TreeMultiNode<T> root)
            {
                m_root      = root;
                m_current   = root;
            }

            public void Reset()
            {
                m_current = m_root;
                m_nextsubtree.Clear();
            }

            public TreeMultiNode<T> Current
            {
                get
                {
                    return m_current;
                }
            }
            public static TreeNodePreOrderIterator operator++(TreeNodePreOrderIterator node)
            {
                if(node.m_current.Children.Count == 0)
                {
                    if(node.m_nextsubtree.Count > 0)
                    {
                        node.m_current = node.m_nextsubtree.Pop();
                    }
                    else
                    {
                        node.m_current = null;
                    }
                }
                else
                {
                    if(node.m_current.Children.Count > 1)
                    {
                        for(int curr_child = (node.m_current.Children.Count - 1);
                            curr_child >0;
                            curr_child--)
                        {
                            node.m_nextsubtree.Push(node.m_current.Children[curr_child]);
                        }
                    }
                    node.m_current = node.m_current.Children[0];
                }
                return node;
            }
        }
    }
}
