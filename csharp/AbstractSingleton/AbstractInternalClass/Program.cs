using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace AbstractInternalClass
{
    class Program
    {
        static void Main(string[] args)
        {
        }
    }
}


public abstract class Item 
{
    public Item Parent { get; private set; }
    public abstract class Container : Item 
    {
        private HashSet<Item> items = new HashSet<Item>();
        public void Add(Item item) 
        {
            if (item.Parent != null)
                throw new Exception("Item has inconsistent containment.");
            item.Parent = this;
            items.Add(item);
        }
        public void Remove(Item item) 
        {
            if (!Contains(item))
                throw new Exception("Container does not contain that item.");
            items.Remove(item);
            item.Parent = null;
        }
        public bool Contains(Item item) 
        {
            return items.Contains(item);
        }
        public IEnumerable<Item> Items 
        {
            // Do not just return items. Then the caller could cast it
            // to HashSet<Item> and then make modifications to your
            // internal state! Return a read-only sequence:
            get 
            {
                foreach(Item item in items) yield return item;
            }
        }
    }
} 

    