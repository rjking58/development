import logging

FORMAT = "%(asctime)-15s [%(lineno)d]  %(message)s"
logging.basicConfig(filename='ObserverPatternLog.txt', level=logging.WARNING,format=FORMAT )
logging.LogRecord
logging.debug("===================================================")
logging.debug("===================================================")
logging.debug("START DEBUG SESSION")
logging.debug("===================================================")
logging.debug("===================================================")

class Interface_ObserverA :
    def GetName(self):
        pass
    def DoAction1(self,val):
        pass

class Interface_Observer_Subject:
    def __init__(self) :   # constructor implementation
        logging.debug("Interface_Observer_Subject::__init__ ENTRY")
        self.__subscribers = {}
        logging.debug("Interface_Observer_Subject::__init__ EXIT")

    def GetSubscribers(self):
        logging.debug("Interface_Observer_Subject::GetSubscribers ENTRY")
        return self.__subscribers
        logging.debug("Interface_Observer_Subject::GetSubscribers EXIT")

    def GetSubscribersCount(self):
        return len(self.__subscribers)

    def ShowSubs(self):
        print(self.__subscribers)

    def Subscribe(self,obj : Interface_ObserverA ):     #type hint to make sure this interface is fully respected
        pass

    def Unsubscribe(self,obj : Interface_ObserverA ):   #type hint to make sure this interface is fully respected
        pass


class ConcreteObserver1(Interface_ObserverA):
    def __init__(self,pName) :   # constructor implementation
        logging.debug("ConcreteObserver1::__init__ ENTRY pName[%s]" % pName)
        self.__val = 0
        self.__Name = pName
        logging.debug("ConcreteObserver1::__init__ EXIT pName[%s]" % pName)

    def GetName(self):
        return self.__Name

    def DoAction1(self,val):
        self.__val = val
        logging.debug("ConcreteObserver1::DoAction1 ENTRY __Name[%s] val[%d]" % (self.__Name,val))
        print("__Name[%s] called with val[%d]" % (self.__Name,val))
        logging.debug("ConcreteObserver1::DoAction1 EXIT")
    
    def GetVal(self):
        return self.__val

class ConcreteSubject1 (Interface_Observer_Subject):
    def __init__(self,pName) :   # constructor implementation
        logging.debug("ConcreteSubject1::__init__ ENTRY pName[%s]" % pName)
        Interface_Observer_Subject.__init__(self)       #in Python, base class constructors are NOT automagically called
        self.__Name = pName
        self.__val = 0
        logging.debug("ConcreteSubject1::__init__ EXIT pName[%s]" % pName)

    def Subscribe(self,obj : Interface_ObserverA ):
        logging.debug("ConcreteSubject1::Subscribe ENTRY")
        logging.debug("ConcreteSubject1::Subscribe  trying to add obj[%s]" % obj.GetName())
        subs = self.GetSubscribers()
        if not obj in subs :
            subs[obj] = obj
        logging.debug("ConcreteSubject1::Subscribe EXIT")

    def Unsubscribe(self,obj : Interface_ObserverA ):   #type hint to make sure this interface is fully respected
        logging.debug("ConcreteSubject1::Unsubscribe ENTRY")
        logging.debug("ConcreteSubject1::Subscribe  trying to remove obj[%s]" % obj.GetName())
        subs = self.GetSubscribers()
        if obj in subs:
            subs.pop(obj)
        logging.debug("ConcreteSubject1::Unsubscribe EXIT")

    def __NotifySubs(self):
        logging.debug("ConcreteSubject1::__NotifySubs ENTRY")
        subs = self.GetSubscribers()
        for currObj in subs:
            subs[currObj].DoAction1(self.__val)
        logging.debug("ConcreteSubject1::__NotifySubs EXIT")

    def SetVal(self,pVal:float):
        logging.debug("ConcreteSubject1::SetVal ENTRY pVal[%d]" % pVal)
        doNotify = False
        if pVal != self.__val:
            doNotify = True
        self.__val = pVal
        if doNotify:
            self.__NotifySubs()
        logging.debug("ConcreteSubject1::SetVal EXIT")



cs1 = ConcreteSubject1('subject 1')
co1 = ConcreteObserver1('observerA 1')
co2 = ConcreteObserver1('observerA 2')
co3 = ConcreteObserver1('observerA 3')
cs1.Subscribe(co1)
cs1.SetVal(11)
cs1.Subscribe(co2)
cs1.SetVal(22)
cs1.Subscribe(co3)
cs1.SetVal(33)
cs1.Unsubscribe(co1)
cs1.SetVal(44)
cs1.Unsubscribe(co2)
cs1.SetVal(55)
cs1.Unsubscribe(co3)
cs1.SetVal(66)
