
#include <windows.h>

using namespace System;
using namespace System::Text;


#include "MixedModeExample.h"

#include <stdlib.h>
#include <string.h>


#include <msclr\marshal_cppstd.h>
#include <list>


#pragma managed
namespace MixedModeIF
{
	public ref class MixedModeIF
	{

	public: 

		static void DoASubmit()
		{
			String^ mngd_id = "1234";
			String^ mngd_submitter = "rjk";
			String^ mngd_comments = "woof woof";

			NativeEval n_eval;
			n_eval.m_Id = msclr::interop::marshal_as<std::string>(mngd_id);
			n_eval.m_Submitter = msclr::interop::marshal_as<std::string>(mngd_submitter);
			n_eval.m_Comments = msclr::interop::marshal_as<std::string>(mngd_comments);

			SubmitEvalNative(n_eval);

			mngd_id = "8901";
			mngd_submitter = "rjk";
			mngd_comments = "bark bark";

			n_eval.m_Id = msclr::interop::marshal_as<std::string>(mngd_id);
			n_eval.m_Submitter = msclr::interop::marshal_as<std::string>(mngd_submitter);
			n_eval.m_Comments = msclr::interop::marshal_as<std::string>(mngd_comments);



			SubmitEvalNative(n_eval);

			std::map<std::string,NativeEval> *evals = GetEvalsNative();
			for(std::map<std::string,NativeEval>::iterator currEval = evals->begin();
				currEval != evals->end();
				currEval++)
			{
				mngd_id = msclr::interop::marshal_as<String^>(currEval->second.m_Id);
				mngd_submitter = msclr::interop::marshal_as<String^>(currEval->second.m_Submitter);
				mngd_comments = msclr::interop::marshal_as<String^>(currEval->second.m_Comments);
				
				Console::WriteLine("ID:" + mngd_id);
				Console::WriteLine("Submitter:" + mngd_submitter);
				Console::WriteLine("Comments:" + mngd_comments);

			}
			delete evals;
		}

		//static List<

	};
}
