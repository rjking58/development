using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

using System.ServiceModel;

namespace BasicService_HOSTING_NAMEDPIPE
{
    public class ServiceHost<T> : ServiceHost
    {
        public ServiceHost()
            : base(typeof(T))
        {
        }
        public ServiceHost(params string[] baseaddresses)
            : base(typeof(T), Convert(baseaddresses))
        {
        }
        public ServiceHost(params Uri[] baseaddresses)
            : base(typeof(T), baseaddresses)
        {
        }

        static Uri[] Convert(string[] baseaddresses)
        {
            Converter<string, Uri> convert = delegate(string address)
            {
                return new Uri(address);
            };

            return Array.ConvertAll(baseaddresses,convert);
        }
    }
}
