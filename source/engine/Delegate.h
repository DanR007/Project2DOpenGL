#pragma once


class Actor;



struct NIL {};
class IArguments { public: virtual ~IArguments() {} };
template< class T1 = NIL>
class Arguments : public IArguments
{
public: 
	Arguments() {}
public: 
	Arguments(T1 i_arg1) :
	arg1(i_arg1) {}
public: 
	T1 arg1;
};


class IContainer 
{ 
	public: 
		virtual void Call(IArguments*) = 0; 
		virtual void* getObj() { return nullptr; }
};
template< class Obj, class M > class Container : public IContainer {};

//  контейнер, хранящий функцию и вызывающий её.
template< class Obj >
class Container< Obj, void (Obj::*)(void) > : public IContainer
{
	typedef void (Obj::* M)(void);
public: 
	Container(Obj* c, M m) : _object(c), _method(m) {}
private: 
	Obj* _object;
	M _method;

public: 
	Obj* getObj() { return _object; }
	void Call(IArguments* i_args)
	{
		(_object->*_method)();
	}
};

template<class Obj, class A1>
class Container <Obj, void (Obj::*)(A1)> :public IContainer
{
	typedef void (Obj::* M)(A1);
	typedef Arguments<A1> A;
public:
	Container(Obj* object, M method) :_method(method), _object(object) {}
	void Call(IArguments* arg)
	{
		A* a = dynamic_cast<A*>(arg);
		if (a)
		{
			(_object->*_method)(a->arg1);
		}
	}
	Obj* getObj() { return _object; }
private:
	M _method;
	Obj* _object;
};
//  класс делегата.
class Delegate
{
	public:
	Delegate() : m_container(0) {}
	~Delegate() 
	{ 
		if (m_container) 
		{ 
			delete m_container; 
		}
	}

	template< class T, class U > 
	void Connect(T* i_class, U i_method)
	{
		if (m_container) 
		{
			delete m_container;
		}

		m_container = new Container< T, U >(i_class, i_method);
	}

	template<class T> 
	bool compareClass(const T* compare_object)
	{
		if(compare_object)
		{
			return compare_object == m_container->getObj();
		}

#ifdef DEBUG
		std::cerr << "Compare object is nullptr" << std::endl;
#endif
		return false;
	}

	void operator()()
	{
		if (m_container)
		{
	#ifdef __linux__
			auto arg = Arguments<>();
			m_container->Call(&arg);
	#else //not __linux__
			m_container->Call(&Arguments<>());
	#endif//__linux__
		}
	}

	template< class T1 > void operator()(T1 i_arg1)
	{
		if(m_container)
		{
	#ifdef __linux__
			auto arg = Arguments<T1>(i_arg1);
			m_container->Call(&arg);
	#else //not __linux__
			m_container->Call(&Arguments< T1 >(i_arg1));
	#endif//__linux__
		}
	}

	private:
	IContainer* m_container;
};

