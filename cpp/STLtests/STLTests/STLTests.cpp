// STLTests.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <vector>
#include <map>
#include <set>
#include <list>
#include <queue>
#include <iostream>
#include <string>

class TestLookup
{
public:
	enum LookupVals { ONE,TWO,THREE,FOUR };
private:
	int m_i;
	LookupVals m_lv;
public:

	TestLookup(int i,LookupVals lv) :	m_i(i),
										m_lv(lv)
	{
	}
	int getVal()
	{
		return m_i;
	}

	LookupVals getLV()
	{
		return m_lv;
	}

};

struct strCopyTst
{
	std::string myString;
};

std::auto_ptr<strCopyTst> get_strCopyTst()
{
	std::auto_ptr<strCopyTst> sct(new strCopyTst);
	sct->myString = "woohoo";
	return sct;
}

int _tmain(int argc, _TCHAR* argv[])
{
	// VECTOR
	std::vector<int> byteVec;
	std::vector<int>::iterator byteVecIter;

	// adding to the end with .push_back(xx)
	byteVec.push_back(1);
	byteVec.push_back(2);
	byteVec.push_back(3);

	// returning the size with .size()
	std::cout << byteVec.size() << std::endl;

	byteVec.push_back(43);

	std::cout << byteVec.size() << std::endl;

	// forward iteration..
	// note here that end() actually is not the end, but
	// ONE past it :)
	for(byteVecIter = byteVec.begin();
		byteVecIter < byteVec.end();
		byteVecIter++)
	{
		std::cout << *byteVecIter << std::endl;
	}

	byteVec.clear();

	std::cout << "after clear::" << byteVec.size() << std::endl;


	// now do pointers to objects for another test..
	struct X
	{
		X(int p_i) : i(p_i)
		{
		}
		int i;
	};

	std::vector<X*> XVec;
	std::vector<X*> XVec2;
	std::vector<X*>::iterator XVecIter;

	// adding to the end with .push_back(xx)
	XVec.push_back(new X(1));
	XVec.push_back(new X(2));
	XVec.push_back(new X(3));

	// returning the size with .size()
	std::cout << XVec.size() << std::endl;

	XVec.push_back(new X(43));

	std::cout << XVec.size() << std::endl;

	// forward iteration..
	// note here that end() actually is not the end, but
	// ONE past it :)
	for(XVecIter = XVec.begin();
		XVecIter < XVec.end();
		XVecIter++)
	{
		std::cout << (*XVecIter)->i << std::endl;
		XVec2.push_back(*XVecIter);
	}

	XVec.clear();

	for(XVecIter = XVec2.begin();
		XVecIter < XVec2.end();
		XVecIter++)
	{
		delete (*XVecIter);
	}

	//byteVec.


	// MAP................

	typedef std::map<TestLookup::LookupVals,TestLookup *> TestMap;
	typedef std::pair<TestLookup::LookupVals,TestLookup *> TestMap_pair;
	TestMap tst_map;
	TestMap tst_map2;
	TestMap::iterator tst_map_iter;
	TestMap::iterator tst_map_iter2;

    tst_map.erase(TestLookup::ONE);
    tst_map.erase(TestLookup::TWO);
    tst_map.erase(TestLookup::THREE);
    tst_map.erase(TestLookup::FOUR);

	TestLookup * tl = 0;

	for(int i = 1; i < 4; i++)
	{
		switch(i)
		{
		case 1:
			tl = new TestLookup(i,TestLookup::ONE);
			break;
		case 2:
			tl = new TestLookup(i,TestLookup::TWO);
			break;
		case 3:
			tl = new TestLookup(i,TestLookup::THREE);
			break;
		case 4:
			tl = new TestLookup(i,TestLookup::FOUR);
			break;
		}
		tst_map.insert(TestMap_pair(tl->getLV(),tl));
	}

    tst_map2.insert(tst_map.begin (),tst_map.end());

	std::cout << "Map tests=============" << std::endl;
	tst_map_iter = tst_map2.find(TestLookup::FOUR);
	if(tst_map_iter != tst_map2.end())
	{
		std::cout << tst_map_iter->second->getVal() << std::endl;
	}
	else
	{
		std::cout << "FOUR not found" << std::endl;
	}
	tst_map_iter = tst_map2.find(TestLookup::THREE);

	std::cout << tst_map_iter->second->getVal() << std::endl;
	tst_map_iter = tst_map2.find(TestLookup::TWO);
	std::cout << tst_map_iter->second->getVal() << std::endl;
	tst_map_iter = tst_map2.find(TestLookup::ONE);
	std::cout << tst_map_iter->second->getVal() << std::endl;


   


	typedef std::set<TestLookup *> TestSet;
	TestSet tst_set;
	TestSet::iterator tst_set_iter;


	TestLookup * t_1 = 0;
	TestLookup * t_2 = 0;
	TestLookup * t_3 = 0;
	TestLookup * t_4 = 0;

	t_1 = new TestLookup(1,TestLookup::ONE);
	tst_set.insert(t_1);
	t_2 = new TestLookup(2,TestLookup::TWO);
	tst_set.insert(t_2);
	t_3 = new TestLookup(3,TestLookup::THREE);
	tst_set.insert(t_3);
	t_4 = new TestLookup(4,TestLookup::FOUR);
	tst_set.insert(t_4);

	tst_set_iter = tst_set.find(t_4);
	if(tst_set_iter != tst_set.end())
	{
		tst_set.erase(tst_set_iter);
	}

	std::cout << "Set tests=============" << std::endl;
	tst_set_iter = tst_set.find(t_4);
	if(tst_set_iter != tst_set.end())
	{
		std::cout << (*tst_set_iter)->getVal() << std::endl;
	}
	else
	{
		std::cout << "FOUR not found" << std::endl;
	}
	tst_set_iter = tst_set.find(t_3);
	std::cout << (*tst_set_iter)->getVal() << std::endl;
	tst_set_iter = tst_set.find(t_2);
	std::cout << (*tst_set_iter)->getVal() << std::endl;
	tst_set_iter = tst_set.find(t_1);
	std::cout << (*tst_set_iter)->getVal() << std::endl;

    for(tst_set_iter = tst_set.begin();
        tst_set_iter != tst_set.end();
        tst_set_iter++)
    {
        std::cout << (*tst_set_iter)->getVal() << std::endl;
    }

	// test string copy as part of class..
	// is std::string treated as plain old data??
	strCopyTst orig1;
	orig1.myString = "woohoo";
	std::cout << orig1.myString.data() << std::endl;

	strCopyTst *cpy1 = new strCopyTst(orig1);

	// yup!
	std::cout << cpy1->myString.data() << std::endl;


	std::cout << "queue..." << std::endl;

	std::queue<TestLookup*> myQ;
	myQ.push(t_1);
	myQ.push(t_2);
	myQ.push(t_3);
	TestLookup *t_x = 0;

    std::cout << "non delete test.." << std::endl;
    for(int x = 0; x < 5; x++)
    {
        t_x = myQ.front();
		std::cout << t_x->getVal() << std::endl;
        if(x == 2)
        {
            myQ.pop();
        }
    }
    while(myQ.size () > 0)
    {
        myQ.pop();
    }

	myQ.push(t_1);
	myQ.push(t_2);
	myQ.push(t_3);


    std::cout << "delete test.." << std::endl;
	while( ! myQ.empty())
	{
		t_x = myQ.front();
		myQ.pop();
		std::cout << t_x->getVal() << std::endl;
	}

	std::auto_ptr<strCopyTst> tst = get_strCopyTst();
	std::cout << "auto_ptr passed by value out of function:" << tst->myString.data() << std::endl;
	
    typedef std::map<std::string,std::set<std::string>> TestMapVec;
	TestMapVec tst_mapvec;
	typedef TestMapVec::iterator TestMapVecIter;
    typedef std::set<std::string>::iterator strVecIter;
//	TestMap::iterator tst_map_iter2;

    tst_mapvec["one"].insert("one_a");
    tst_mapvec["one"].insert("one_b");
    tst_mapvec["two"].insert("two_a");

    // print all map keys..
    for(TestMapVecIter currKey = tst_mapvec.begin ();
        currKey != tst_mapvec.end();
        currKey++)
    {
        std::cout << "keyval[" << currKey->first << "]" << std::endl;
    }

    std::cout << "one" << std::endl;
    for(strVecIter currVec = tst_mapvec["one"].begin();
        currVec != tst_mapvec["one"].end();
        currVec++)
    {

        std::cout << "    " << *currVec << std::endl;
    }
    std::cout << "two" << std::endl;
    for(strVecIter currVec = tst_mapvec["two"].begin();
        currVec != tst_mapvec["two"].end();
        currVec++)
    {

        std::cout << "    " << *currVec << std::endl;
    }

    std::cout << "one ";
    if(tst_mapvec.find("one") == tst_mapvec.end())
    {
        std::cout << "not ";
    }
    std::cout << "found" << std::endl;

    std::cout << "two ";
    if(tst_mapvec.find("two") == tst_mapvec.end())
    {
        std::cout << "not ";
    }
    std::cout << "found" << std::endl;

    std::cout << "three ";
    if(tst_mapvec.find("three") == tst_mapvec.end())
    {
        std::cout << "not ";
    }
    std::cout << "found" << std::endl;

    std::cout << "one_a ";
    if(tst_mapvec["one"].find("one_a") == tst_mapvec["one"].end())
    {
        std::cout << "not ";
    }
    std::cout << "found" << std::endl;

    std::cout << "one_b ";
    if(tst_mapvec["one"].find("one_b") == tst_mapvec["one"].end())
    {
        std::cout << "not ";
    }
    std::cout << "found" << std::endl;

    std::cout << "one_c ";
    if(tst_mapvec["one"].find("one_c") == tst_mapvec["one"].end())
    {
        std::cout << "not ";
    }
    std::cout << "found" << std::endl;


    struct ReferenceTest
    {
        int i;
        int j;
    };

	typedef std::map<int,ReferenceTest> TestRefMap;
	typedef std::pair<int,ReferenceTest> TestRefMap_pair;
	TestRefMap tst_refmap;
	TestRefMap tst_refmap2;
	TestRefMap::iterator tst_refmap_iter;
	TestRefMap::iterator tst_refmap_iter2;

    tst_refmap.erase(1);
    tst_refmap.erase(2);
    tst_refmap.erase(3);
    tst_refmap.erase(4);

	ReferenceTest rt;

	for(int i = 1; i < 5; i++)
	{
		rt.i = i;
		rt.j = i;

		tst_refmap.insert(TestRefMap_pair(rt.i,rt));
	}

    tst_refmap2.insert(tst_refmap.begin (),tst_refmap.end());

    for(int i = 1; i < 5; i++)
    {
        ReferenceTest &ref = tst_refmap2[i];
        ref.j = ref.j+10;
    }

    for(int i = 1; i < 5; i++)
    {
        tst_refmap_iter2 = tst_refmap2.find(i);
        std::cout << "i[" << tst_refmap_iter2->second.i << "] j[" << tst_refmap_iter2->second.j << "]" << std::endl;
    }

    std::cout << "pointers stored in maps and deleting them" << std::endl;
	typedef std::map<int,ReferenceTest*> TestRef2Map;
	typedef std::pair<int,ReferenceTest*> TestRef2Map_pair;
	TestRef2Map tst_ref2map;
	TestRef2Map tst_ref2map2;
	TestRef2Map::iterator tst_ref2map_iter;
	TestRef2Map::iterator tst_ref2map_iter2;

    ReferenceTest   *pRt_ary[5];

	for(int i = 0; i < 5; i++)
	{
        pRt_ary[i] = new ReferenceTest;
        pRt_ary[i]->i = i;
        pRt_ary[i]->j = i;

        tst_ref2map.insert(TestRef2Map_pair(i,pRt_ary[i]));
	}

    for(int i = 0; i < 5; i++)
    {
        tst_ref2map_iter2 = tst_ref2map.find(i);
        std::cout << "i[" << (tst_ref2map_iter2->second)->i << "] j[" << (tst_ref2map_iter2->second)->j << "]" << std::endl;
    }

    for(int i = 0; i < 5; i++)
    {
        tst_ref2map_iter2 = tst_ref2map.find(i);
        tst_ref2map.erase (tst_ref2map_iter2);
    }
    for(int i = 0; i < 5; i++)
    {
        delete pRt_ary[i];
    }
    

	std::list<int> mylist;
	for (int i = 1; i < 10; i++)
	{
		mylist.push_back(i);
	}

	for( std::list<int>::iterator lst_itr = mylist.begin();
		 lst_itr != mylist.end(); 
		 lst_itr++)
	{
		std::cout << "mylist[" << *lst_itr << "] ";
	}
	std::cout << std::endl;

	std::list<int> mylist_tmp;
	for( std::list<int>::iterator lst_itr = mylist.begin();
		lst_itr != mylist.end(); 
		lst_itr++)
	{
		if(*lst_itr != 4)
		{
			mylist_tmp.push_back(*lst_itr);
		}
	}
	mylist.clear();
	mylist.insert(mylist.begin(),mylist_tmp.begin(),mylist_tmp.end());

	for( std::list<int>::iterator lst_itr = mylist.begin();
		lst_itr != mylist.end(); 
		lst_itr++)
	{
		std::cout << "mylist[" << *lst_itr << "] ";
	}
	std::cout << std::endl;


	return 0;
}

