using System;
using System.Collections.Generic;
using System.Text;

namespace CardsDeck {
    interface ICards {
        /// <summary>
        /// Gets one card from deck
        /// </summary>
        /// <returns></returns>
        string GetCard();
        /// <summary>
        /// shuffles cards back to deck
        /// </summary>
        void Shuffle();
    }
}
