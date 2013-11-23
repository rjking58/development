// This is the main DLL file.

#include "stdafx.h"
#include "BinaryXfer.h"
#include <list>

using namespace System::Runtime::InteropServices;

namespace BinaryXfer 
{

#pragma pack(push)
#pragma pack(1)
    struct MySimpleCPP
    {
        char    m_byte;
        short   m_short;
        long    m_long;
    };
#pragma pack(pop)

    struct FullData
    {
        char    m_byte;
        short   m_short;
        long    m_long;

        short    m_str1len;
        char    *m_str1;
        short    m_str2len;
        char    *m_str2;
    };
    class TransferBufferBuilder
    {
    private:
        std::list<FullData> &m_toXfer;

        void AddStruct( char **currBuffLoc,
                        std::list<FullData>::iterator &currFullData)
        {
            // ///////////////////////////////////////////////////////
            // struct data.
            // ///////////////////////////////////////////////////////
            // put struct data into buffer.
            MySimpleCPP *AsStruct = (MySimpleCPP *) (*currBuffLoc);

            AsStruct->m_byte  = currFullData->m_byte;
            AsStruct->m_short = currFullData->m_short;
            AsStruct->m_long  = currFullData->m_long;
            
            // skip over just written struct data..
            (*currBuffLoc) += sizeof(MySimpleCPP);

            // ///////////////////////////////////////////////////////
            // first string
            // ///////////////////////////////////////////////////////
            // length of first string
            *((short *)(*currBuffLoc)) = currFullData->m_str1len;
            (*currBuffLoc) += 2;

            // first string
            for(int byteOfst = 0; byteOfst < currFullData->m_str1len;byteOfst++)
            {
                (*currBuffLoc)[byteOfst] = currFullData->m_str1[byteOfst];
            }
            (*currBuffLoc) += currFullData->m_str1len;

            // ///////////////////////////////////////////////////////
            // second string
            // ///////////////////////////////////////////////////////
            // length of second string
            *((short *)(*currBuffLoc)) = currFullData->m_str2len;
            (*currBuffLoc) += 2;

            // second string
            for(int byteOfst = 0; byteOfst < currFullData->m_str2len;byteOfst++)
            {
                (*currBuffLoc)[byteOfst] = currFullData->m_str2[byteOfst];
            }
            (*currBuffLoc) += currFullData->m_str2len;
        }

    public:
        TransferBufferBuilder(std::list<FullData> &toXfer) : m_toXfer(toXfer)
        {
        }
        char *FetchTransferBuffer(int &totalsz)
        {
            char *  theBuffer = 0;
            totalsz = 4; // start out with space for the initial transfer count.
            // get total size..
            for(std::list<FullData>::iterator currFullData = m_toXfer.begin();
                currFullData != m_toXfer.end();
                currFullData++)
            {
                totalsz += sizeof(MySimpleCPP);     // size of struct data..
                totalsz += 4;                       // both string counts
                totalsz += currFullData->m_str1len; // string lengths..
                totalsz += currFullData->m_str2len; // string lengths..
            }
            // create buffer
            theBuffer = new char[totalsz];
            char * currBuffLoc = theBuffer;
            // lay down the count
            *((int *) currBuffLoc) = m_toXfer.size();
            currBuffLoc += sizeof(int);
            // lay down individual structures.
            for(std::list<FullData>::iterator currFullData= m_toXfer.begin();
                currFullData != m_toXfer.end();
                currFullData++)
            {
                AddStruct(&currBuffLoc,currFullData);
            }


            return theBuffer;
        }


            
    };
    class BinaryXferNative
    {
    private:
        std::list<FullData> m_toXfer;
    public:
        BinaryXferNative()
        {
            for(int currOfst = 0;
                currOfst < 100;
                currOfst++)
            {
                FullData strs;
                strs.m_byte = currOfst;
                strs.m_short = currOfst + 100;
                strs.m_long = currOfst + 1000;
                strs.m_str1len = 10;
                strs.m_str1 = new char[10];
                for (int ofst = 0;
                     ofst < 10;
                     ofst++)
                {
                    strs.m_str1[ofst] = ofst;
                }
                strs.m_str2len = 5;
                strs.m_str2 = new char[5];
                for (int ofst = 0;
                     ofst < 5;
                     ofst++)
                {
                    strs.m_str2[ofst] = ofst + 100;
                }

                m_toXfer.push_back(strs);
            }
        }
        char * GetSingleMySimple(int &totalsz)
        {
            FullData    strs;
            MySimpleCPP inst;
            inst.m_byte = 1;
            inst.m_short = 2;
            inst.m_long = 3;
            
            strs.m_str1len = 10;
            strs.m_str1 = new char[10];
            for (int ofst = 0;
                 ofst < 10;
                 ofst++)
            {
                strs.m_str1[ofst] = ofst;
            }
            strs.m_str2len = 5;
            strs.m_str2 = new char[5];
            for (int ofst = 0;
                 ofst < 5;
                 ofst++)
            {
                strs.m_str2[ofst] = ofst + 100;
            }

            char * retVal = ConvertSingleToBytestream(inst,strs,totalsz);
            return retVal;
        }

        char * ConvertSingleToBytestream(MySimpleCPP    &inst,
                                         FullData        &strs,
                                         int            &totalsz)
        {
            char * retVal = 0;
            int MySimpleCPPsz = sizeof(MySimpleCPP);
            MySimpleCPPsz += 2;                        // reserve for the size word
            MySimpleCPPsz += strs.m_str1len;
            MySimpleCPPsz += 2;                        // reserve for the size word
            MySimpleCPPsz += strs.m_str2len;        
            
            retVal = new char[MySimpleCPPsz];
            totalsz = MySimpleCPPsz;

            MySimpleCPP *AsStruct = (MySimpleCPP *) retVal;

            AsStruct->m_byte  = inst.m_byte;
            AsStruct->m_short = inst.m_short;
            AsStruct->m_long  = inst.m_long;
            
            // wheee.. pointer arithmetic!
            char *retValOfst = retVal + sizeof(MySimpleCPP);

            *((short *)retValOfst) = strs.m_str1len;
            retValOfst += 2;
            for(int byteOfst = 0; byteOfst < strs.m_str1len;byteOfst++)
            {
                retValOfst[byteOfst] = strs.m_str1[byteOfst];
            }
            retValOfst += strs.m_str1len;

            *((short *)retValOfst) = strs.m_str2len;

            retValOfst += 2;
            for(int byteOfst = 0; byteOfst < strs.m_str2len;byteOfst++)
            {
                retValOfst[byteOfst] = strs.m_str2[byteOfst];
            }
            

            return retVal;
        }
        char * GetBulkTransferNative(int &totalsz)
        {
            TransferBufferBuilder bldr(m_toXfer);
            return bldr.FetchTransferBuffer(totalsz);
        }
    };
    public ref class BinaryXfer
    {
    public:
        static array<Byte>^ GetTheAry()
        {
            int totalsz = 0;
            BinaryXferNative bxn;
            char * nativePtr = bxn.GetSingleMySimple(totalsz);
            array<Byte> ^ managedPtr = gcnew array<Byte>(totalsz);
            
            // this is a by value type.. NOT a reference type.
            IntPtr nativeAsIntPtr((void *)nativePtr);

            Marshal::Copy(nativeAsIntPtr,managedPtr,0,totalsz);
            

            return managedPtr;
        }
        static array<Byte>^ GetBulkTransfer()
        {
            int totalsz = 0;
            BinaryXferNative bxn;
            char * nativePtr = bxn.GetBulkTransferNative(totalsz);
            array<Byte> ^ managedPtr = gcnew array<Byte>(totalsz);
            
            // this is a by value type.. NOT a reference type.
            IntPtr nativeAsIntPtr((void *)nativePtr);

            Marshal::Copy(nativeAsIntPtr,managedPtr,0,totalsz);
            

            return managedPtr;
        }

    };


}
