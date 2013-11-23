using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace BinSearch
{
    class Program
    {
        
        static void Main(string[] args)
        {
            TR_UnitTest tr = new TR_UnitTest();
            BinSearchForBoundary bbt = new BinSearchForBoundary(tr);
            
            List<int>   compares = new List<int>();
            int overallTotal = 0;
            int charCount = 0;
            for(int entries = 1;
                entries < 5000;
                entries++)
            {
                for(int boundary = -1;
                    boundary < entries;
                    boundary++)
                {
                    int foundBound = 0;
                    tr.Last_entry_that_fits = boundary;
                    Console.Write(".");
                    charCount++;
                    if(charCount >= 40)
                    {
                        Console.WriteLine();
                        charCount = 0;
                    }
                    tr.CompareCount = 0;
                    if(bbt.BinarySearchBoundary(ref foundBound, entries))
                    {
                        if(foundBound != boundary)
                        {
                            Console.WriteLine("boundary is wrong");
                            throw new System.ArgumentOutOfRangeException();
                        }
                    }
                    else
                    {
                        if(boundary != -1 )
                        {
                            Console.WriteLine("BAD BAD BAD");
                            throw new System.ArgumentOutOfRangeException();
                        }
                    }
                    compares.Add(tr.CompareCount);
                }
                Console.WriteLine();
                Console.WriteLine("for this many elements:" + entries);
                Console.WriteLine("cases checked:" + compares.Count);
                int minCompares = 100000;
                int maxCompares = 0;
                double totalCompares = 0.0;
                foreach(int val in compares)
                {
                    totalCompares += val;
                    if(val < minCompares)
                    {
                        minCompares = val;
                    }
                    if(val > maxCompares)
                    {
                        maxCompares = val;
                    }
                }
                double avgCompare = totalCompares/compares.Count;
                Console.WriteLine("avg # of compares:" + avgCompare);
                Console.WriteLine("min # of compares:" + minCompares);
                Console.WriteLine("max # of compares:" + maxCompares);
                overallTotal += compares.Count;
                compares.Clear();
            }
            Console.WriteLine("overall:" + overallTotal);
        }

    }
    
    /// <summary>
    /// Used by the BinSearchForBoundary class to do its boundary test.
    /// </summary>
    interface TestRoutine
    {
        /// <summary>
        /// test an index of some abstract array to see if it and members
        /// that come before it are acceptable.  Returns true if this is true, 
        /// returns false if this is not..
        ///
        /// a concrete case (the one actually implemented) is as follows:
        /// the list
        /// </summary>
        /// <param name="indexToTest"></param>
        /// <returns></returns>
        bool TestEntry(int indexToTest);
    }
    
    class TR_UnitTest : TestRoutine
    {

        private int m_last_entry_that_fits = 0;
        private int m_compareCount = 0;

        public int Last_entry_that_fits
        {
            get 
            { 
                return m_last_entry_that_fits; 
            }
            set 
            { 
                m_last_entry_that_fits = value; 
            }
        }

        public int CompareCount
        {
            get 
            { 
                return m_compareCount; 
            }
            set 
            { 
                m_compareCount = value; 
            }
        }
        
        #region TestRoutine Members

        public bool TestEntry(int indexToTest)
        {
            m_compareCount++;            return indexToTest <= m_last_entry_that_fits;
        }

        #endregion
    }
    
    class BinSearchForBoundary
    {
        private TestRoutine m_tr = null;

        public BinSearchForBoundary(TestRoutine tr)
        {
            m_tr = tr;
        }
    
        /// <summary>
        /// find the last valid entry... combines a binary search with a final linear search..
        /// what we are looking for is how many elements in an array will 'fit' into a given 
        /// memory space..  so each test adds all the elements from the beginning of the 
        /// array to the test point.. if we don't fit, the test is false, if we do, the test is true..
        /// if NONE fit, then this routine returns a false and the found_index is not valid.
        /// In all the cases tested worst case performance in this algorithm 
        /// is log2(n) + 2 test builds of the list, which provides scaling as the
        /// set grows.  Averaged performance is in the range of log2(n) + .5, which is excellent.
        /// 
        /// Special cases are tested first to determine if we even need to do a search.
        /// </summary>
        /// <param name="found_index"></param>
        /// <returns>true if we found a good boundary, false if we can't find a good match</returns>
        public bool BinarySearchBoundary(ref int found_index, int num_of_entries)
        {
            bool FoundBoundary = true;
            
            // special length cases first
            if(num_of_entries == 1)
            {
                // special case 1
                // if we don't fit, there is no place to fit.
                FoundBoundary = m_tr.TestEntry(0);
                if(FoundBoundary)
                {
                    found_index = 0;
                }
            }
            else if (num_of_entries == 2)
            {
                if(m_tr.TestEntry(0))
                {
                    FoundBoundary = true;
                    if(m_tr.TestEntry(1))
                    {
                        found_index = 1;
                    }
                    else
                    {
                        found_index = 0;
                    }
                }
                else
                {
                    FoundBoundary = false;
                }
                // test 1, then 2.
                // if 1 doesn't fit, no place to fit.. if 2 doesn't fit, use 1.
            }
            else
            {
                // special position cases next.
                // try the last element.. if we fit no more searching is required. (SUCCESS)
                if(m_tr.TestEntry(num_of_entries - 1))
                {
                    FoundBoundary = true;
                    found_index = num_of_entries - 1;
                }
                else
                {
                    if(! m_tr.TestEntry(0))
                    {
                        // try the first element.. if we don't fit then no more searching is required. (FAIL)
                        FoundBoundary = false;
                    }
                    else
                    {
                    
                        // do the binary search thingee.
                        int     begRange = 0;
                        int     midPoint = 0;
                        int     endRange = num_of_entries - 1;
                        int     nextCheck = 0;
                        bool    begMoved = false;
                        while ((endRange - begRange) > 1)
                        {
                            begMoved = false;
                            midPoint = begRange + ( (endRange - begRange)/2 );
                            
                            if(m_tr.TestEntry(midPoint))
                            {
                                // it fits, so look HIGHER
                                begRange = midPoint + 1;
                                begMoved = true;
                            }
                            else
                            {
                                // it DOESN'T fit, so look LOWER
                                endRange = midPoint - 1;
                                begMoved = false;
                            }
                        }
                        // end of search
                        // check the end we last moved, then linear search from there..
                        if(begMoved)
                        {
                            nextCheck = begRange;
                        }
                        else
                        {
                            nextCheck = endRange;
                        }
                        if(m_tr.TestEntry(nextCheck))
                        {
                            // we found a valid entry, so look HIGHER
                            int last_valid = nextCheck;
                            nextCheck++;
                            while(m_tr.TestEntry(nextCheck))
                            {
                                last_valid = nextCheck;
                                nextCheck++;
                            }
                            found_index = last_valid;
                        }
                        else
                        {
                            // we found an invalid entry, so look LOWER
                            nextCheck--;
                            while(! m_tr.TestEntry(nextCheck))
                            {
                                nextCheck--;
                            }
                            found_index = nextCheck;
                        }
                    }
                }
            }
            return FoundBoundary;
        }
    }
}
