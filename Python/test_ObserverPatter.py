import ObserverPattern
import pytest


def test_SubscriptionSemantics():
    subj = ObserverPattern.ConcreteSubject1('subj')
    obsv = ObserverPattern.ConcreteObserver1('obsv')
    assert subj.GetSubscribersCount() == 0
    subj.Subscribe(obsv)
    assert subj.GetSubscribersCount() == 1
    subj.Subscribe(obsv)
    assert subj.GetSubscribersCount() == 1    
    subj.Unsubscribe(obsv)
    assert subj.GetSubscribersCount() == 0
    subj.Unsubscribe(obsv)
    assert subj.GetSubscribersCount() == 0

def test_ValPropagation_oneInstance():
    subj = ObserverPattern.ConcreteSubject1('subj')
    obsv = ObserverPattern.ConcreteObserver1('obsv')
    assert subj.GetSubscribersCount() == 0
    subj.Subscribe(obsv)
    assert subj.GetSubscribersCount() == 1
    subj.SetVal(2)
    assert obsv.GetVal() == 2

    #make sure resubscribe does nothing..
    subj.Subscribe(obsv)
    assert obsv.GetVal() == 2
    subj.SetVal(4)
    assert obsv.GetVal() == 4

def test_ValPropagation_multiInstance():
    subj = ObserverPattern.ConcreteSubject1('subj')
    obsv = ObserverPattern.ConcreteObserver1('obsv')
    obsv2 = ObserverPattern.ConcreteObserver1('obsv2')
    obsv3 = ObserverPattern.ConcreteObserver1('obsv3')
    assert subj.GetSubscribersCount() == 0
    subj.Subscribe(obsv)
    subj.Subscribe(obsv2)
    subj.Subscribe(obsv3)

    assert subj.GetSubscribersCount() == 3
    subj.SetVal(2)
    assert obsv.GetVal() == 2
    assert obsv2.GetVal() == 2
    assert obsv3.GetVal() == 2

    subj.SetVal(7)
    assert obsv.GetVal() == 7
    assert obsv2.GetVal() == 7
    assert obsv3.GetVal() == 7
