
const long memsize = 100000L;


// implemented this way incase we need to enhance intelligence
// in memory fetches.

class MixMachineMemory
{
	long GetAddr(long Addr)
	{
		return memory[Addr];
	}
private:
	long memory[memsize];
};

class Register
{
public:
	virtual void LoadReg(int startReg,int EndReg, int sign, long reg_val) = 0;
	virtual long GetReg(int startReg=1,int EndReg=5, int sign=TRUE) = 0;
};

class ArithmeticRegister : public Register
{
public:
	ArithmeticRegister();
	void LoadReg(int startReg,int EndReg, int sign, long reg_val)
	{
	}
	long GetReg(int startReg=1,int EndReg=5, int sign=TRUE)
	{
		return 1;
	}

private:
	union Registers
	{
		struct Discreet
		{
		  int unused:1;
		  int sign:1;
		  int r1:6;
		  int r2:6;
		  int r3:6;
		  int r4:6;
		  int r5:6;
		}; 
		long entire_register;

	} regs;
	
};

class IndexRegister : public Register
{
public:
	IndexRegister();
	void LoadReg(int startReg,int EndReg, int sign, long reg_val)
	{
	}
	long GetReg(int startReg=4,int EndReg=5, int sign=TRUE)
	{
		return 1;
	}

private:
	union Registers
	{
		struct Discreet
		{
		  int sign:1;
		  int r4:6;
		  int r5:6;
		}; 
		long entire_register;

	} regs;
	
};

class JRegister: public Register
{
public:
	IndexRegister();
	void LoadReg(int startReg,int EndReg, int sign, long reg_val)
	{
	}
	long GetReg(int startReg=4,int EndReg=5, int sign=TRUE)
	{
		return 1;
	}

private:
	union Registers
	{
		struct Discreet
		{
		  int r4:6;
		  int r5:6;
		}; 
		long entire_register;

	} regs;
	
};



class MixCPU
{
public:
	MixCPU()
	{
		A	= new ArithmeticRegister;
		X	= new ArithmeticRegister;
		I1	= new IndexRegister;
		I2	= new IndexRegister;
		I3	= new IndexRegister;
		I4	= new IndexRegister;
		I5	= new IndexRegister;
		I6	= new IndexRegister;
		J	= new JRegister;
	}		
	~MixCPU()
	{
		delete A;	
		delete X;	
		delete I1;	
		delete I2;	
		delete I3;	
		delete I4;	
		delete I5;	
		delete I6;	
		delete J;	
	}		
private:
	Register	*A;
	Register	*X;
	Register	*I1;
	Register	*I2;
	Register	*I3;
	Register	*I4;
	Register	*I5;
	Register	*I6;
	Register	*J;
};

