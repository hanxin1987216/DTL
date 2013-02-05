/***************************************************************************************************
 
 C++ Network Library, Copyright (c) Datatom Software, Inc.(2012)

Author:
	韩欣 (han.xin@datatom.com)
Creating Time:
	2012-8-10
***************************************************************************************************/
#ifndef __DTL_SINGLETON_INC
#define __DTL_SINGLETON_INC

#include <stdlib.h>

/**
  * usage: SingleTemplate<your_class_name>::instance().m_member;
**/

template <typename Type>
class SingleTemplate
{
public:
	static Type& instance() // Unique point of access
	{
		if (s_instance == 0)
		{
			s_instance = new(Type)();
			atexit(destroy);
		}
		return *s_instance;
	}
protected:
	SingleTemplate() {}
	virtual ~SingleTemplate() {}
private:
	static void destroy() // Destroy the only instance
	{
		if (s_instance != 0)
		{
			delete(s_instance);
			s_instance = 0;
		}
	}
	static Type* volatile s_instance; // The one and oly instance
};

template <typename Type>
Type* volatile SingleTemplate<Type >::s_instance = 0;

#endif	//__DTL_SINGLETON_INC

