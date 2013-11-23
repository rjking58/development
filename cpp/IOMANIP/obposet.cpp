

OME_BPOutputSet(	ExecFRecord 										& OutputRec,
						const DynamicValArray<ExecFColumnHandle>	& FEColHandles,
						const SimpIDynArray<KeyToCol>					& MainKeys,
						const KeyToCol										& DateKtC,
						int													FESuperSetCnt		)
	:	// interface data
		mOutputRec(OutputRec),
		mFEColHandles(FEColHandles),
		mMainKeys(MainKeys),
		mDateKtC(DateKtC),
		mFESuperSetCnt(FESuperSetCnt),
		
		//internal data
		mCurrTree(0),
		mVTIter(0)
	
{
	
}

BOOL LoadFromExecFSet()
{
	int	currFEOfst;
	int	MainKeyCnt = mMainKeys.GetNumItemsInArray();
	int	MainKeyOfst;
	Val	*currVal;
	BOOL	RecToWrite = FALSE;
	
	
	
	// set values from top of tree...
	if (mFirstRec)
	{
		mFirstRec = FALSE;
	}
	currVal = (*mVTIter)->GetData();
	
	for ( MainKeyOfst = 0;
			(MainKeyOfst < MainKeyCnt);
			MainKeyOfst++				  	)
	{
	
		
		mOutputRec.SetColumnDoubleVal(mMainKeys[MainKeyOfst]->ColHand, 
												currVal->
													GetDoubleKey
														(mMainKeys[MainKeyOfst]->KeyHand)
											  );
		
	}	

	// date...
	mOutputRec.SetColumnDateVal(	mDateKtC.ColHand, 
											currVal->GetDateKey(mDateKtC.KeyHand) );

	
	
	
		
	++mVTIter;  // next portion of tree..
	if(! mVTIter.Done())
	{
		RecToWrite = TRUE;
	}
	
	return RecToWrite;
	// store data into tree.
	while(! mVTIter.Done())
	{
		// current value pointed to by iterator..
		currVal = (*mVTIter)->GetData();
		
		// get column corresponding to bucketnum and stuff into tree FE array
		// corresponding to FE offset..
		cout	<< setw(3) << currVal->GetDoubleKey(mBucketNumKH)
				<< "("
				<< setw(2) << currVal->GetDateKey(mDateKH)->nMonth
				<< "/"
				<< currVal->GetDateKey(mDateKH)->nDay
				<< "/"
				<< currVal->GetDateKey(mDateKH)->nYear
				<< ") : ";
		
		for (currFEOfst = 0 ; currFEOfst < mFESuperSetCnt; currFEOfst++)
		{
			cout << setw(10) << currVal->GetVal(currFEOfst) << " ";
		}
		cout << endl;
		++mVTIter;
	}
	
	// outta here.
	return valueset;
	
}

void SetCurrValueSet(ValTree * valueset)
{
	mVTIter.SetNewTargetObjAndReset(valueset);
	mFirstRec = TRUE;
}

