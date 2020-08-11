import myFunc
import pytest

#for currTestVal in range(0,10,1) :
#    funcReturn = myFunc.myfunc(currTestVal)
#    print(funcReturn)

def test_GoodAnswer():
    for currTestVal in range(0,10,1) :
        funcReturn = myFunc.myfunc(currTestVal)
        assert funcReturn == currTestVal+2

#this should fail!
def test_BadAnswer():
    funcReturn = myFunc.myfunc(3)
    assert funcReturn == 4    