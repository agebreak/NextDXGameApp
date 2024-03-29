// Singleton class
#pragma once

template <typename T>
class Singleton
{
public:
	static T * GetInstance()
	{
		if (ms_Instance == NULL) ms_Instance = new T;
		return ms_Instance;
	};	
	static void ReleaseInstance()
	{
		delete ms_Instance;
		ms_Instance = NULL;
	};

private:
	static T * ms_Instance;
};

template<typename T> T* Singleton<T>::ms_Instance = 0;