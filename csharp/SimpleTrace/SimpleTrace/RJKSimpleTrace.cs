using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SimpleTrace
{
    public class RJKSimpleTrace
    {
        static bool s_initialized = false;
        static StreamWriter s_sw = null;
        static Object s_writeLock = new object();
        static Object s_initlock = new object();
        public RJKSimpleTrace(string filename)
        {
            lock (s_initlock)
            {
                if (!s_initialized)
                {
                    FileInfo fi = new FileInfo(filename);

                    string fDir = fi.DirectoryName;
                    if(fDir.Length > 0)
                    {
                        DirectoryInfo di = new DirectoryInfo(fDir);
                        if( ! di.Exists)
                        {
                            Directory.CreateDirectory(fDir);
                        }
                    }
                    s_sw = new StreamWriter(filename, true);

                    
                    s_initialized = true;
                }
            }
        }

        public RJKSimpleTrace()
        {
            if(!s_initialized)
            {
                throw new InvalidOperationException("must be constructed first time with a filename");
            }
        }

        public void closeTrace()
        {
            lock(s_writeLock)
            {
                if(s_sw != null)
                {
                    s_sw.Close();
                    s_sw = null;
                    s_initialized = false;
                }
            }
        }
        public void WriteLine(string outputLine)
        {
            lock(s_writeLock)
            {
                if(s_sw != null)
                {
                    StackTrace st = new StackTrace(true);
                    StackFrame sf = st.GetFrame(1);

                    s_sw.WriteLine(string.Format(   "{0}[{1}] : {2}",
                                                    sf.GetFileName(),
                                                    sf.GetFileLineNumber(),
                                                    outputLine));
                    s_sw.Flush();
                }
            }
        }
    }
}
