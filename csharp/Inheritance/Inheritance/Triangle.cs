using System;
using System.Collections.Generic;
using System.Text;

namespace Inheritance
{
    public class Triangle : TwoDShape
    {
        private String m_style;

        public Triangle(double width, double height, string style) : base (width,height)
        {
            m_style = style;
        }

        // copy constructor, c# style.
        public Triangle(Triangle obj)
            : base(obj)
        {
            m_style = obj.m_style;
        }

        public String Style
        {
            get { return m_style; }
            set { m_style = value; }
        }

        public double area()
        {
            return Width * Height;
        }

        public void showStyle()
        {
            Console.WriteLine("Triangle is " + m_style);
        }
    }
}
