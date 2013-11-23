using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Decorator
{
    /// <summary>
    /// a component we will use.. the decorator will
    /// only decorate the DoSomething method.. 
    /// </summary>
    public abstract class AbstractComponent
    {
        public abstract void DoSomething();

        public abstract void DoSomethingElse();
    }

    /// <summary>
    /// our basic undecorated object.
    /// </summary>
    public class ConcreteComponent : AbstractComponent
    {
        public override void DoSomething()
        {
            Console.WriteLine("DoSomething");
        }

        public override void DoSomethingElse()
        {
            Console.WriteLine("DoSomethingElse");
        }
    }

    /// <summary>
    /// abstract definition of the decorator.. we simply forward the
    /// non decorated method in this class, and leave the DoSomething() 
    /// method untouched, since subclasses will decorate it as needed
    /// </summary>
    public abstract class ComponentDecorator : AbstractComponent
    {
        private AbstractComponent m_component = null;

        public ComponentDecorator(AbstractComponent ac)
        {
            m_component = ac;
        }

        // simply forward this, we aren't decorating
        public override void DoSomethingElse()
        {
            m_component.DoSomethingElse();
        }
    }

    /// <summary>
    /// a 'post decorator'.  Here, we do something AFTER the call to
    /// the decorated behavior
    /// </summary>
    public class Post1Decorator : ComponentDecorator
    {
        private AbstractComponent m_component = null;

        public Post1Decorator(AbstractComponent ac) : base(ac)
        {
            m_component = ac;
        }

        /// <summary>
        ///  the decorated behavior
        /// </summary>
        public override void DoSomething()
        {
            /// the standard behavior
            m_component.DoSomething();
            /// our decoration.. 
            Console.WriteLine("post1");
        }
    }

    /// <summary>
    /// a 'pre decorator'.  Here, we do something BEFORE the call to
    /// the decorated behavior
    /// </summary>
    public class Pre1Decorator : ComponentDecorator
    {
        private AbstractComponent m_component = null;

        public Pre1Decorator(AbstractComponent ac):base(ac)
        {
            m_component = ac;
        }

        /// <summary>
        ///  the decorated behavior
        /// </summary>
        public override void DoSomething()
        {
            /// our decoration.. 
            Console.WriteLine("pre1");
            /// the standard behavior
            m_component.DoSomething();
        }
    }

    /// <summary>
    /// a 'pre decorator'.  Here, we do something BEFORE the call to
    /// the decorated behavior
    /// </summary>
    public class Pre2Decorator : ComponentDecorator
    {
        private AbstractComponent m_component = null;

        public Pre2Decorator(AbstractComponent ac):base(ac)
        {
            m_component = ac;
        }

        /// <summary>
        ///  the decorated behavior
        /// </summary>
        public override void DoSomething()
        {
            /// our decoration.. 
            Console.WriteLine("pre2");
            /// the standard behavior
            m_component.DoSomething();
        }
    }

    class Program
    {
        static void Main(string[] args)
        {
            AbstractComponent ac = new ConcreteComponent();
            AbstractComponent DecoratedAc = null;

            DecoratedAc = new Pre1Decorator(ac);
            DecoratedAc = new Pre2Decorator(DecoratedAc);
            DecoratedAc = new Post1Decorator(DecoratedAc);

            DecoratedAc.DoSomething();
            DecoratedAc.DoSomethingElse();


            DecoratedAc = new Post1Decorator(ac);
            DecoratedAc = new Pre2Decorator(DecoratedAc);
            DecoratedAc = new Pre1Decorator(DecoratedAc);

            DecoratedAc.DoSomething();
            DecoratedAc.DoSomethingElse();
        }
    }
}
