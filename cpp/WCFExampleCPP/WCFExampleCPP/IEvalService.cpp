
// needed since this AIN'T C#!!
#include "Eval.cpp"

using namespace System;
using namespace System::Collections::Generic;
using namespace System::ServiceModel;

namespace WCFExampleCPP {

	[ServiceContract]
	public interface class IEvalService
	{
	public:
		[OperationContract]
		virtual void SubmitEval(Eval^ eval);
		[OperationContract]
		virtual List<Eval^>^ GetEvals();
		[OperationContract]
		virtual void RemoveEval(String^ id);
	};

}