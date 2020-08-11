
# ############################################
# constructor demo.
# ############################################
class CSimple :
    def __init__(self,p_Name) :   # constructor implementation
        self.m_Name = p_Name
    def isName(self) :              #simple public method
        print(self.m_Name)

CSimple_1 = CSimple("bob")
CSimple_2 = CSimple("fred")

CSimple_1.isName()
CSimple_2.isName()


# ############################################
#private implementation example
# ############################################
class PubPrivBase :
    def doAction(self) :
        print("doAction")
        self.__doAction()
    
    def __doAction(self) :
        print('__doAction')

class PubPrivSub(PubPrivBase) :
    def doOtherAction(self) :
        print("doOtherAction")
        self.doAction()         #inherited method.
        #self.__doAction()      #the Python style is TRUE private.. no access from sub classes.  uncomment this to see a failure..


ppb1 = PubPrivSub()
ppb1.doAction()
ppb1.doOtherAction()


# ############################################
#template implementation.. contains abstract method 'processAction2'  and an algorithm that depends on calling it
# ############################################
class TemplateClassBase :
    def simpleProcess(self) :
        print("TemplateClassBase:process action 1")
        print("TemplateClassBase:process action 2")
        self.processAction2()
        print("TemplateClassBase:process action 3")
    def processAction2(self) :
        pass

# ############################################
#template implementation.. sub class that gives concrete implementation to base class abstract method
# ############################################
class TemplateClassSub1(TemplateClassBase) :
    def processAction2(self) :
        print("TemplateClassSub1:processAction2 for SUB1")

# ############################################
#template implementation.. sub class that gives concrete implementation to base class abstract method
# ############################################
class TemplateClassSub2(TemplateClassBase) :
    def processAction2(self) :
        print("TemplateClassSub2:processAction2 for SUB2!!!")

# build an array with each class.. call the process..
instances = [TemplateClassSub1(),TemplateClassSub2()]
for inst in instances :
    inst.simpleProcess()
    print()




