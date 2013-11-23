#include <iostream.h>


class Tracked;

class TrackedMemento
{
friend Tracked;
public:
	TrackedMemento()
	{
	}
	~TrackedMemento()
	{
	}
private:
	// this returns the state to the creating object so that it can 
	// re-instate its previous state.
	int GetState(void)
	{
		return savedState;
	}
	// this saves the state from the creating object 
	void SaveState(int state)
	{
		savedState = state;
	}

	int savedState;

};


class Tracked
{
public:
	Tracked() : mMyState(0)
	{
	}
	void PrintState(void)
	{
		cout << "My state is" << mMyState << endl;
	}
	void ChangeState(void)
	{
		mMyState++;
	}

	// make a memento for future use.
	TrackedMemento * CreateMemento()
	{
		TrackedMemento *TM;

		// new memento...
		TM = new TrackedMemento;
		// save off our state.
		TM->SaveState(mMyState);

		return TM;
	}
	// using the memento, re-instate a previous state.
	void SetMemento(TrackedMemento *TM)
	{
		// use the memento to restore our previous state.
		mMyState = TM->GetState();
	}

private:
	int mMyState;
};




void main(void)
{
	Tracked			TrackedObject;
	TrackedMemento	*TMArray[10];
	int			   	x;

	for (x = 0 ; x < 10 ; x++)
	{
		cout << "CREATING MEMENTO'S" << endl;
		cout << "State for memento :" << x << ": = ";
		TrackedObject.PrintState();
		cout << endl;
		TMArray[x] = TrackedObject.CreateMemento();
		TrackedObject.ChangeState();
	}

	for (x = 9 ; x >= 0; x--)
	{
		cout << "USING MEMENTO'S" << endl;
		TrackedObject.SetMemento(TMArray[x]);
		cout << "State for memento :" << x << ": = ";
		TrackedObject.PrintState();
		cout << endl;
	}

}