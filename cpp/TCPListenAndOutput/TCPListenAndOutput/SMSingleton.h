#pragma once


// Implement singleton pattern's behaviour .
// A class which should behave as a singleton should parameterize this template 
// and use "instance" method to retrieve reference to the object: SMSingleton< SomeClass >::instance()
template<class T> 
class SMSingleton
{
private:

	// The reason of this structure is to create instance of a singleton object before main-function 
	// (or WinMain, or another entry point) will receive execution. 
	// Singleton object will be created with other global variables.
	struct creator
	{
		creator()
		{
			SMSingleton<T>::instance();
		}  
	};
	static creator s_singleton_creator;

public:
	static T& instance()
	{
		static T inst;
		return inst;
	}
};

template<class T> 
typename SMSingleton<T>::creator SMSingleton<T>::s_singleton_creator;
