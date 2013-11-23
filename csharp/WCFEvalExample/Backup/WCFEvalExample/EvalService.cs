using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.ServiceModel;

namespace WCFEvalExample
{
    [ServiceBehavior(InstanceContextMode=InstanceContextMode.Single)]
    public class EvalService : IEvalService
    {
        #region IEvalService Members
        List<Eval> m_evals = new List<Eval>();
        public void SubmitEval(Eval eval)
        {
            eval.Id = Guid.NewGuid().ToString();
            m_evals.Add(eval);
        }

        public List<Eval> GetEvals()
        {
            return m_evals;
        }

        public void RemoveEval(string id)
        {
            m_evals.Remove(m_evals.Find(e => e.Id.Equals(id)));
        }

        #endregion
    }
}
