// EnumerableUsage_CPP.cpp : main project file.

#include "stdafx.h"

using namespace System;
using namespace System::Collections::Generic;
using namespace System::Text;

// old school enumerator implementation (since C++ doesn't have yield return that I know of..)
ref class IntCollection : public IEnumerable<int>
{
private:
	array<int>^ intArray;

	ref class IntCollectionEnumerator : public IEnumerator<int>
	{
		int currOfst;
		array<int>^ m_IntArray;
	public:
		IntCollectionEnumerator(array<int>^ pIntArray) : currOfst(-1),m_IntArray(pIntArray)
		{}

		// Dispose!
		~IntCollectionEnumerator()
		{}

		virtual property int Current_Generic
		{
			virtual int get() sealed = System::Collections::Generic::IEnumerator<int>::Current::get
			{
				return m_IntArray[currOfst];
			}
		}

		virtual property Object^ Current_NonGeneric
		{
			virtual Object^ get() sealed = System::Collections::IEnumerator::Current::get
			{
				return Current_Generic;
			}
		}

		virtual void Reset()
		{
			currOfst = -1;
		}

		virtual bool MoveNext()
		{
			currOfst++;
			return (currOfst < m_IntArray->Length);
		}
	};
public:
	IntCollection()
    {
		intArray = gcnew array<int>(5) {4,7,11,33,42};
    }



    virtual System::Collections::Generic::IEnumerator<int>^ GetEnumerator_Generic() sealed = System::Collections::Generic::IEnumerable<int>::GetEnumerator
    {
		return gcnew IntCollectionEnumerator(intArray);
    }

	virtual System::Collections::IEnumerator^ GetEnumerator_NonGeneric() sealed = System::Collections::IEnumerable::GetEnumerator
    {
		return GetEnumerator_Generic();
    }

};


int main(array<System::String ^> ^args)
{
	IntCollection^ ie = gcnew IntCollection();

	for each (int i in ie)
	{
		Console::WriteLine(i);
	}

	Console::ReadLine();
	return 0;
}

