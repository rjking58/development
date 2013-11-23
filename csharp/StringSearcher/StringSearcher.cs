using System;
using System.Collections;

namespace StringSearcher
{

	/// <summary>
	/// Summary description for StringSearcher.
	/// </summary>
	/// 
    // basic usage notes..
    // string to be searched is added to this class via the constructor alone.
    // basic string search syntax:
    // '(' start of return string
    // ')' end of return string
    // '.' match any character(s)
    // '\(' normal open paren
    // '\)' normal close paren
    // '\.' normal period
    // '\\' normal backslash
    // look for a string starting with abc, then any characters, ending in xyz.. return all
    // characters between the abc and xyz
    // "abc(.)xyz"
    // look for string starting with abc, ending in xyz, and return everything between
    // ab and z
    // "ab(c.xy)z"
   

	public class StringSearcher
	{
        private String mStringToSearch;
        ArrayList mFoundSpecs = new ArrayList(100);
        // special chars
        const char dot = '.';
        const char backslash = '\\';
        const char open_paren = '(';
        const char close_paren = ')';

		public StringSearcher(String stringToSearch)
		{
            mStringToSearch = stringToSearch;
			//
			// TODO: Add constructor logic here
			//
            // parse our string..

		}

	}
}
