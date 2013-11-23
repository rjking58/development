using System;
using System.Collections.Generic;
using System.Text;

namespace AbstractSingleton
{
    enum RemoteType
    {
        STEALTH_USB,
        FUTURE1,
        UNDEFINED
    }
    
    enum DeviceDBType 
    {
        T,
        V,
    }
    
    abstract class RemoteCapabilities
    {
        public abstract bool AllowsStandardMacros   {get;}
        public abstract bool AllowsRotatingMacros   {get;}
        public abstract bool AllowsDelayMacros      {get;}
        public abstract bool AllowsSynthKeys        {get;}
        public abstract bool AllowsKeyMover         {get;}
        public abstract bool AllowsSynthMover       {get;}
        public abstract bool AllowsVolumePunchThru  {get;}
        public abstract byte DeviceDBTypeToDeviceType(DeviceDBType ddbt);
    }

    abstract class RemoteMemory
    {
        public abstract uint MacroMemoryLeft();
        public abstract uint UseMacroMemory(uint to_use);
        public abstract uint FreeMacroMemory(uint to_free);
        public abstract uint DeviceSlotsLeft();
        public abstract uint UseDeviceSlot(uint to_use);
        public abstract uint FreeDeviceSlot(uint to_free);
        public abstract uint MainMemoryLeft();
        public abstract uint UseMainMemory(uint to_use);
        public abstract uint FreeMainMemory(uint to_free);
    }
    
    abstract class RemoteAbstractFactory
    {   
        private static RemoteCapabilities m_rc = null;
        private static RemoteMemory m_rm = null;
        
        public static void SetupFactory(RemoteType rt)
        {   
            RemoteAbstractFactory fact = null;
            m_rc = null;
            m_rm = null;
            switch(rt)
            {
                case RemoteType.STEALTH_USB:
                    fact = new StealthUSBFactory();
                    break;
                case RemoteType.FUTURE1:
                    fact = new Future1Factory();
                    break;
                default:
                    throw new System.ArgumentOutOfRangeException(String.Format("RemoteType {0} not recognized",
                                                                               rt));
            }
            m_rc = fact.GetRemoteCapabilities();
            m_rm = fact.GetRemoteMemory();
        }
        public static RemoteCapabilities getRemoteCapabilitiesInstance()
        {
            if(m_rc == null)
            {
                throw new System.ArgumentException("must call SetRemoteType before calling getRemoteCapabilitiesInstance()");
            }
            return m_rc;
        }
        public static RemoteMemory getRemoteMemoryInstance()
        {
            if(m_rm == null)
            {
                throw new System.ArgumentException("must call SetRemoteType before calling getRemoteMemoryInstance()");
            }
            return m_rm;
        }
        
        public abstract RemoteCapabilities  GetRemoteCapabilities();
        public abstract RemoteMemory        GetRemoteMemory();
        
        class StealthUSBFactory : RemoteAbstractFactory
        {   
            public override RemoteCapabilities GetRemoteCapabilities()
            {
                return new StealthUSBRemoteCapabilities();
            }
    
            public override RemoteMemory GetRemoteMemory()
            {
                return new StealthUSBRemoteMemory();
            }
        }
        class Future1Factory : RemoteAbstractFactory
        {
        
            public override RemoteCapabilities GetRemoteCapabilities()
            {
                return new Future1RemoteCapabilities();
            }
        
            public override RemoteMemory GetRemoteMemory()
            {
                return new Future1RemoteMemory();
            }
        }
    
        class StealthUSBRemoteCapabilities : RemoteCapabilities
        {
            public override bool AllowsStandardMacros   
            {   
                get
                {
                    throw new System.NotImplementedException();
                }
            }
            public override bool AllowsRotatingMacros   
            {   
                get
                {
                    throw new System.NotImplementedException();
                }
            }
            public override bool AllowsDelayMacros      
            {   
                get
                {
                    throw new System.NotImplementedException();
                }
            }
            public override bool AllowsSynthKeys        
            {   
                get
                {   
                    throw new System.NotImplementedException();
                }
            }
            public override bool AllowsKeyMover         
            {   
                get
                {   
                    throw new System.NotImplementedException();
                }
            }
            public override bool AllowsSynthMover       
            {   
                get
                {
                    throw new System.NotImplementedException();
                }
            }
            public override bool AllowsVolumePunchThru  
            {   
                get
                {   
                    throw new System.NotImplementedException();
                }
            }
            public override byte DeviceDBTypeToDeviceType(DeviceDBType ddbt)
            {
                throw new System.NotImplementedException();
            }
        }
        class Future1RemoteCapabilities : RemoteCapabilities
        {
            public override bool AllowsStandardMacros   
            {   
                get
                {
                    throw new System.NotImplementedException();
                }
            }
            public override bool AllowsRotatingMacros   
            {   
                get
                {
                    throw new System.NotImplementedException();
                }
            }
            public override bool AllowsDelayMacros      
            {   
                get
                {
                    throw new System.NotImplementedException();
                }
            }
            public override bool AllowsSynthKeys        
            {   
                get
                {   
                    throw new System.NotImplementedException();
                }
            }
            public override bool AllowsKeyMover         
            {   
                get
                {   
                    throw new System.NotImplementedException();
                }
            }
            public override bool AllowsSynthMover       
            {   
                get
                {
                    throw new System.NotImplementedException();
                }
            }
            public override bool AllowsVolumePunchThru  
            {   
                get
                {   
                    throw new System.NotImplementedException();
                }
            }
            public override byte DeviceDBTypeToDeviceType(DeviceDBType ddbt)
            {
                throw new System.NotImplementedException();
            }
        }
        
        class StealthUSBRemoteMemory : RemoteMemory
        {
            public override uint MacroMemoryLeft()
            {
                throw new System.NotImplementedException();
            }
            public override uint UseMacroMemory(uint to_use)
            {
                throw new System.NotImplementedException();
            }
            public override uint FreeMacroMemory(uint to_free)
            {
                throw new System.NotImplementedException();
            }
            public override uint DeviceSlotsLeft()
            {
                throw new System.NotImplementedException();
            }
            public override uint UseDeviceSlot(uint to_use)
            {
                throw new System.NotImplementedException();
            }
            public override uint FreeDeviceSlot(uint to_free)
            {
                throw new System.NotImplementedException();
            }
            public override uint MainMemoryLeft()
            {
                throw new System.NotImplementedException();
            }
            public override uint UseMainMemory(uint to_use)
            {
                throw new System.NotImplementedException();
            }
            public override uint FreeMainMemory(uint to_free)
            {
                throw new System.NotImplementedException();
            }
        }
        class Future1RemoteMemory : RemoteMemory
        {
            public override uint MacroMemoryLeft()
            {
                throw new System.NotImplementedException();
            }
            public override uint UseMacroMemory(uint to_use)
            {
                throw new System.NotImplementedException();
            }
            public override uint FreeMacroMemory(uint to_free)
            {
                throw new System.NotImplementedException();
            }
            public override uint DeviceSlotsLeft()
            {
                throw new System.NotImplementedException();
            }
            public override uint UseDeviceSlot(uint to_use)
            {
                throw new System.NotImplementedException();
            }
            public override uint FreeDeviceSlot(uint to_free)
            {
                throw new System.NotImplementedException();
            }
            public override uint MainMemoryLeft()
            {
                throw new System.NotImplementedException();
            }
            public override uint UseMainMemory(uint to_use)
            {
                throw new System.NotImplementedException();
            }
            public override uint FreeMainMemory(uint to_free)
            {
                throw new System.NotImplementedException();
            }
        }
    }
    
    class Program
    {
        static void Main(string[] args)
        {
#if false        
            RemoteAbstractFactory.SetupFactory(RemoteType.UNDEFINED);
#endif
            RemoteAbstractFactory.SetupFactory(RemoteType.STEALTH_USB);
            RemoteAbstractFactory.SetupFactory(RemoteType.FUTURE1);
        }
    }
}
