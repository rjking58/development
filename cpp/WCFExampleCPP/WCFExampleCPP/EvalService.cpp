#include "IEvalService.cpp"

using namespace System;
using namespace System::Collections::Generic;
using namespace System::Runtime::Serialization;
using namespace System::ServiceModel;

namespace WCFExampleCPP {

	[ServiceBehavior(InstanceContextMode=InstanceContextMode::Single)]
	public ref class EvalService : IEvalService
	{
	public:
		EvalService()
		{
			m_evals = gcnew List<Eval^>();
		}
		virtual void SubmitEval(Eval^ eval)
		{
			eval->Id = Guid::NewGuid().ToString();
			m_evals->Add(eval);
		}

		virtual List<Eval^>^ GetEvals()
		{
			return m_evals;
		}
		virtual void RemoveEval(String^ id)
		{
			Eval^ foundEval = nullptr;
			int EvalCnt = m_evals->Count;
			for (int currEval = 0; 
				 currEval < EvalCnt;
				 currEval++)
			{
				Eval^ ev = m_evals[currEval];
				if(ev->Id == id)
				{
					Console::WriteLine("FOUNDIT");
					foundEval = ev;
				}
			}
			if( foundEval != nullptr)
			{
				m_evals->Remove(foundEval);
			}
		}

	private:
		List<Eval^>^ m_evals;
	};
}