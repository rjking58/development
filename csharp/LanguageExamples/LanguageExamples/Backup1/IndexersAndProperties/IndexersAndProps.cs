using System;
using System.Collections.Generic;
using System.Text;

namespace IndexersAndProperties
{
    class FailSoftArray
    {
        int[] a;
        private uint m_length;
        public uint Length
        {
            get
            {
                return m_length;
            }
        }
        private bool m_errflag;
        public bool Errflag
        {
            get
            {
                return m_errflag;
            }
        }
        private bool m_badsize;
        public bool Badsize
        {
            get
            {
                return m_badsize;
            }
        }

        public FailSoftArray(uint size)
        {
            if (size > 0 && size < 2000)
            {
                a = new int[size];
                m_length = size;
                m_badsize = false;
            }
            else
            {
                m_badsize = true;
            }
        }

        public int this[uint index]
        {
            get
            {
                if (!m_badsize)
                {
                    if (ok(index))
                    {
                        m_errflag = false;
                        return a[index];
                    }
                    else
                    {
                        m_errflag = true;
                        return 0;
                    }
                }
                else
                {
                    return 0;
                }
            }
            set
            {
                if (!m_badsize)
                {
                    if (ok(index))
                    {
                        a[index] = value;
                        m_errflag = false;
                    }
                    else
                    {
                        m_errflag = true;
                    }
                }
                else
                {
                    m_errflag = true;
                }

            }
        }

        private bool ok(uint index)
        {
            if (index >= 0 & index < Length)
                return true;
            else
                return false;
        }
    }



    class IndexersAndProps
    {
        static void Main(string[] args)
        {
            FailSoftArray fs = new FailSoftArray(5);
            Console.WriteLine("fs.Badsize(" +  fs.Badsize + ")" );
            FailSoftArray fs2 = new FailSoftArray(3335);
            Console.WriteLine("fs2.Badsize(" + fs2.Badsize + ")");

            int x;



            Console.WriteLine("Fail quietly");

            for (uint i = 0;
                i < (fs.Length * 2);
                i++)
            {
                fs[i] = (int) (i* 10);
            }
            for (uint i = 0;
                i < (fs.Length * 2);
                i++)
            {
                x = fs[i];
                Console.WriteLine("i(" + i + ")" + "  fs[" + i + "](" + x + ")" );
            }

        }
    }
}
