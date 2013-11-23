
#include <windows.h>
#include "IEvalService.cpp"

using namespace System;
using namespace System::Collections::Generic;
using namespace System::Runtime::Serialization;
using namespace System::ServiceModel;

#include "MixedModeExample.h"
#include <msclr\marshal_cppstd.h>


namespace WCFExampleCPP {

	[ServiceBehavior(InstanceContextMode=InstanceContextMode::Single)]
	public ref class EvalService : IEvalService
	{
	public:
		EvalService()
		{
			//m_evals = gcnew List<Eval^>();
		}
		virtual void SubmitEval(Eval^ eval)
		{
			NativeEval n_eval;
			String^ id = eval->Id;

			String ^ mngd_id = Guid::NewGuid().ToString();
			n_eval.m_Id = msclr::interop::marshal_as<std::string>(mngd_id);

			String^ Submitter = eval->Submitter;
			if(Submitter != nullptr)
			{
				n_eval.m_Submitter = msclr::interop::marshal_as<std::string>(Submitter);
			}
			String ^ Comments = eval->Comments;
			if(Comments != nullptr)
			{
				n_eval.m_Comments = msclr::interop::marshal_as<std::string>(Comments);
			}

			// ===========================================================
			// ==== NATIVE CALL
			// ===========================================================
			SubmitEvalNative(n_eval);
		}

		virtual List<Eval^>^ GetEvals()
		{
			List<Eval^>^ local_evals = gcnew List<Eval^>();

			// ===========================================================
			// ==== NATIVE CALL
			// ===========================================================
			std::map<std::string,NativeEval> *evals = GetEvalsNative();

			for(std::map<std::string,NativeEval>::iterator currEval = evals->begin();
				currEval != evals->end();
				currEval++)
			{
				Eval^ evl = gcnew Eval();

				evl->Id = msclr::interop::marshal_as<String^>(currEval->second.m_Id);
				evl->Submitter = msclr::interop::marshal_as<String^>(currEval->second.m_Submitter);
				evl->Comments = msclr::interop::marshal_as<String^>(currEval->second.m_Comments);
				local_evals->Add(evl);
			}
			delete evals;

			return local_evals;
		}
		virtual void RemoveEval(String^ mngd_id)
		{

			std::string id = msclr::interop::marshal_as<std::string>(mngd_id);
			RemoveEvalNative(id);

		}

	private:
		List<Eval^>^ m_evals;
	};
}