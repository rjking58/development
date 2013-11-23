using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Runtime.Serialization;

namespace WCFEvalExample
{
    // alt-shift F10 to help fill out usings using new Intellisense..
    // data contract (non primitive type passed via an OperationContract (a WCF service method)
    [DataContract]
    public class Eval
    {
        [DataMember]
        public string Id;
        [DataMember]
        public string Submitter;
        [DataMember]
        public string Comments;
        [DataMember]
        public DateTime TimeSubmitted;
    }
}
