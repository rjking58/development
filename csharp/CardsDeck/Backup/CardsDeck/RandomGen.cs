#region Assembly References
using System;
using System.Collections.Generic;
using System.Text;
#endregion

namespace CardsDeck {
    /// <summary>
    /// System.Random generates deterministic random number
    /// So this new class ensures an undetermined random number generation
    /// </summary>
    public class RandomGen {
        #region Private Members
            private Random rand;
        #endregion

        #region Ctor
        public RandomGen() {
                rand = new Random();
            }
        #endregion

        #region public Methods
        /// <summary>
        /// Get Random number will always generate a random number with given max number
        /// and it is undeterministic as it is genrated from timestap which is unique
        /// </summary>
        /// <param name="max"></param>
        /// <returns></returns>
        public int Next(int max) {
            long num = 0;
            //genrate random for max int value to get unique number
            int res = rand.Next(int.MaxValue);
            //geenrate a number with in max value
            Math.DivRem(res, max, out num);
            //add one to avoid zero and support upto max number
            return (int)num + 1;
        }
        #endregion
    }
}
