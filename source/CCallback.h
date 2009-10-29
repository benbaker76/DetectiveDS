#ifndef __CCALLBACK_H__
#define __CCALLBACK_H__

template <class Class, typename ReturnType, typename Parameter>
class CCallback
{
public:
	typedef ReturnType (Class::*Method)(Parameter);

	CCallback(Class* classInstance, Method method)
	{
		m_classInstance = classInstance;
		m_method = method;
	};

	ReturnType operator()(Parameter parameter)
	{
		return (m_classInstance->*m_method)(parameter);
	};

	ReturnType execute(Parameter parameter)
	{
		return operator()(parameter);
	};

private:

	Class*  m_classInstance;
	Method  m_method;
};

#endif
