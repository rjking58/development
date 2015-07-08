namespace SimpleTrace
{
    using System;
    using System.Collections.Generic;
    using System.Diagnostics;
    using System.IO;
    using System.Linq;
    using System.Text;
    using System.Threading.Tasks;

    public class RjkSimpleTrace
    {
        private const int UPDATEFREQ = 400;

        private static bool statInitialized = false;
        private static string statFileName;
        private static object statWriteLock = new object();
        private static object statInitlock = new object();

        private static object statLogEntriesLock = new object();
        private static List<string> statLogEntries = new List<string>();

        public RjkSimpleTrace(string fileName)
        {
            lock (statInitlock)
            {
                if (fileName != null && fileName.Length > 0)
                {
                    if (!statInitialized)
                    {
                        FileInfo fi = new FileInfo(fileName);

                        string fileInfoDirectory = fi.DirectoryName;
                        if (fileInfoDirectory.Length > 0)
                        {
                            DirectoryInfo di = new DirectoryInfo(fileInfoDirectory);
                            if (!di.Exists)
                            {
                                Directory.CreateDirectory(fileInfoDirectory);
                            }
                        }

                        statFileName = fileName;

                        statInitialized = true;

                        this.WriteLine("initialized  RJKSimpleTrace 0.3");
                    }
                }
            }
        }

        public RjkSimpleTrace()
        {
            if (!statInitialized)
            {
                throw new InvalidOperationException("must be constructed first time with a filename");
            }
        }

        private void UpdateLogCache(string outputLine)
        {
            bool updateFile = false;

            lock (statLogEntriesLock)
            {
                statLogEntries.Add(outputLine);
                updateFile = statLogEntries.Count > UPDATEFREQ;
                if (updateFile)
                {
                    this.FlushCache();
                }
            }
        }

        public void FlushCache()
        {
            // not locked because the caller is locked.  Be careful here.
            StreamWriter statSw = null;
            statSw = new StreamWriter(statFileName, true);
            if (statSw != null)
            {
                foreach (string entry in statLogEntries)
                {
                    statSw.WriteLine(entry);
                }

                statLogEntries.Clear();
                statSw.Flush();
            }

            statSw.Close();
        }

        public void WriteLine(string outputLine)
        {
#if false
            lock (statWriteLock)
            {
                StreamWriter statSw = null;
                statSw = new StreamWriter(statFileName, true);
                if (statSw != null)
                {
                    StackTrace st = new StackTrace(true);
                    StackFrame sf = st.GetFrame(1);

                    DateTime currTime = DateTime.Now;
                    string timeStamp = string.Format(
                                                "{0}/{1}/{2} {3,2:D2}:{4,2:D2}.{5,4:D4}",
                                                currTime.Month,
                                                currTime.Day,
                                                currTime.Year,
                                                currTime.Hour,
                                                currTime.Minute,
                                                currTime.Millisecond);
                    string strippedFileName = string.Empty;
                    if (sf.GetFileName() != null)
                    {
                        FileInfo fi = new FileInfo(sf.GetFileName());
                        strippedFileName = fi.Name;
                    }

                    statSw.WriteLine(string.Format(
                                                "{0}[{1}] {2} : {3}",
                                                strippedFileName,
                                                sf.GetFileLineNumber(),
                                                timeStamp,
                                                outputLine));
                    statSw.Flush();
                }

                statSw.Close();
            }
#else
#if true
            StackTrace st = new StackTrace(true);
            StackFrame sf = st.GetFrame(1);

            DateTime currTime = DateTime.Now;
            string timeStamp = string.Format(
                                        "{0}/{1}/{2} {3,2:D2}:{4,2:D2}:{5,2:D2}.{6,4:D4}",
                                        currTime.Month,
                                        currTime.Day,
                                        currTime.Year,
                                        currTime.Hour,
                                        currTime.Minute,
                                        currTime.Second,
                                        currTime.Millisecond);
            string strippedFileName = string.Empty;
            if (sf.GetFileName() != null)
            {
                FileInfo fi = new FileInfo(sf.GetFileName());
                strippedFileName = fi.Name;
            }

            this.UpdateLogCache(string.Format(
                                    "{0}[{1}] {2} TID[{3}] : {4}",
                                    strippedFileName,
                                    sf.GetFileLineNumber(),
                                    timeStamp,
                                    System.Threading.Thread.CurrentThread.ManagedThreadId,
                                    outputLine));
#endif
#endif
        }
    }
}

