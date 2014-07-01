using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace PluralTemplatesCPP
{

    template <class T>
    T max(T& t1, T& t2)
    {
        return t1 < t2 ? t2 : t1;
    }
    class Program
    {
        static void Main(string[] args)
        {

        }
    }
}
