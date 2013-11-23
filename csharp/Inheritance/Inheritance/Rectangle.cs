using System;
using System.Collections.Generic;
using System.Text;

namespace Inheritance
{
    public class Rectangle : TwoDShape
    {
        public Rectangle(double width,double height) : base (width,height)
        {
        }

        public Rectangle(Rectangle obj) : base(obj)
        {
        }

        public bool isSquare()
        {
            return (Width == Height);
        }

        public double area()
        {
            return Width * Height;
        }
    }
}
