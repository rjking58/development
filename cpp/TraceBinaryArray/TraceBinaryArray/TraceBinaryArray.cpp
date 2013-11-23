// TraceBinaryArray.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <iostream>
#include <sstream>
#include <iomanip>


//void trace_charary(std::ostream &output,
//                   const char * ary,
//                   int          ary_len,
//                   int          line_len)
//{
//    if(     (ary != 0)
//        &&  (ary_len > 0))
//    {
//
//        std::ostringstream binaryRepresentation;
//        std::ostringstream strRepresentation;
//
//        output << "0000: ";
//        int currchar = 0;
//        for(;
//            currchar < ary_len;
//            currchar++)
//        {
//            char the_char = ary[currchar];
//            char the_masked_char = the_char & 0x7f;
//            binaryRepresentation << std::hex << std::setw(2) << std::setfill('0') << (int) the_char << " ";
//            if(the_masked_char >= 0x21 && the_masked_char <= 0x7f)
//            {
//                strRepresentation << the_char;
//            }
//            else
//            {
//                strRepresentation << ".";
//            }
//       
//            // output end of line if we are done..
//            if(     ((currchar+1) % line_len) == 0
//                &&  (currchar != 0)             )
//            {
//                output << binaryRepresentation.str();
//                output << "  ";
//                output << strRepresentation.str();
//                output << std::endl;
//                output << std::hex << std::setw(4) << std::setfill('0') << currchar << ": ";
//
//                strRepresentation.str(std::string());
//                binaryRepresentation.str(std::string());
//
//            }
//        }
//        int remaining = (currchar) % line_len;
//        if(remaining != 0)
//        {
//            int toFill = line_len - remaining;
//            output << binaryRepresentation.str();
//            for(int fillcnt = 0;
//                fillcnt < toFill;
//                fillcnt++)
//            {
//                output << "   ";
//            }
//            output << "  ";
//            output << strRepresentation.str();
//        }
//        output << std::endl;
//    }
//}


void trace_charary( std::wostringstream &output,
                                    const char * ary,
                                    int          ary_len,
                                    int          line_len)
{
    if(     (ary != 0)
        &&  (ary_len > 0))
    {

        std::wostringstream binaryRepresentation;
        std::wostringstream strRepresentation;

        output << "0000: ";
        int currchar = 0;
        for(;
            currchar < ary_len;
            currchar++)
        {
            char the_char = ary[currchar];
            char the_masked_char = the_char & 0x7f;
            binaryRepresentation << std::hex  << std::setw(2) << std::setfill(L'0')  << (unsigned char) the_char << L" ";
            if(the_masked_char >= 0x21 && the_masked_char <= 0x7f)
            {
                strRepresentation << the_char;
            }
            else
            {
                strRepresentation << L".";
            }
       
            // output end of line if we are done..
            if(     ((currchar+1) % line_len) == 0
                &&  (currchar != 0)             )
            {
                output << binaryRepresentation.str();
                output << L"  ";
                output << strRepresentation.str();
                output << std::endl;
                output << std::hex  << std::setfill(L'0') << std::setw(4) << (currchar + 1) << L": ";

                strRepresentation.str(std::wstring());
                binaryRepresentation.str(std::wstring());

            }
        }
        int remaining = (currchar) % line_len;
        if(remaining != 0)
        {
            int toFill = line_len - remaining;
            output << binaryRepresentation.str();
            for(int fillcnt = 0;
                fillcnt < toFill;
                fillcnt++)
            {
                output << L"   ";
            }
            output << L"  ";
            output << strRepresentation.str();
        }
        output << std::endl;
    }
}

int _tmain(int argc, _TCHAR* argv[])
{

    char myary[] = {'a', 
                    0xf1,0xf2,0xf3,0xf4,0x05,0x06,0x07,0x08,0x09,0x0a,0x0b,0x0c,0x0d,0x0e,0x0f,    
                    0x11,0x12,0x13,0x14,0x15,0x16,0x17,0x18,0x19,0x1a,0x1b,0x1c,0x1d,0x1e,0x1f,    
                    'b', 'c', 'd', 'e', 'f', 'g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z', 
                    0x00};
    std::string myary_str = myary;
    int myary_len = myary_str.length();


    for(int curr_line_len = 10;
        curr_line_len < 28;
        curr_line_len++)
    {
        std::wostringstream output;
        trace_charary(output,
                      myary,
                      myary_len,
                      curr_line_len);
        output << std::endl;
        std::wcout << output.str().c_str();
    }
    

	return 0;
}



