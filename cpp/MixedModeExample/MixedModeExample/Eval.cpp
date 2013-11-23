
using namespace System;
using namespace System::Runtime::Serialization;
using namespace System::ServiceModel;

// alt-shift F10 to help fill out usings using new Intellisense..
// data contract (non primitive type passed via an OperationContract (a WCF service method)
namespace WCFExampleCPP {

	[DataContract]
	public ref class Eval
	{
	public:
		[DataMember]
		String^ Id;
		[DataMember]
		String^ Submitter;
		[DataMember]
		String^ Comments;
		[DataMember]
		DateTime TimeSubmitted;
	};
}