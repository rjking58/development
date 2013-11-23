// Copyright 1995-2000 Oracle Corporation
// All rights reserved Worldwide

class F
{
public:
   F(long m) : mI(m) {}
   
   operator long() { return mI; }
   long operator+(long m) const { return mI + m; }
private:
   long mI;
};

template <class T> inline int operator+(F a, T b)
{
   return int(a + long(b));
}

int main()
{
   F a(1);
   
   int b = a + 1;
   return 0;
}
