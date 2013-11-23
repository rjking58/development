using System;
using System.Collections.Generic;
using System.Text;

namespace Inheritance
{
    /// <summary>
    /// Base class that shows property implementation and copy construction in C++
    /// </summary>
    public class TwoDShape
    {

        private double m_width;

        public double Width
        {
            get { return m_width; }
            set { m_width = value; }
        }
        private double m_height;

        public double Height
        {
            get { return m_height; }
            set { m_height = value; }
        }

        public void showDim()
        {
            Console.WriteLine("Width and m_height are " +
                              m_width + " and " + m_height);
        }

        public TwoDShape(double width, double height)
        {
            m_width = width;
            m_height = height;
        }

        // copy constructor, c# style.
        public TwoDShape(TwoDShape obj)
        {
            m_width = obj.m_width;
            m_height = obj.m_height;
        }
    }

    class Program
    {
        static void Main(string[] args)
        {
            Triangle t1 = new Triangle(4.0,4.0,"isosceles");
            Triangle t2 = new Triangle(8.0,12.0,"right");
            Triangle t3 = new Triangle(t2);

            Console.WriteLine("info for t1: ");
            t1.showStyle();
            t1.showDim();
            Console.WriteLine("area is " + t1.area());

            Console.WriteLine();
            Console.WriteLine("info for t2: ");
            t2.showStyle();
            t2.showDim();
            Console.WriteLine("area is " + t2.area());

            Console.WriteLine();
            Console.WriteLine("info for t3: ");
            t3.showStyle();
            t3.showDim();
            Console.WriteLine("area is " + t3.area());


        }
    }
}
