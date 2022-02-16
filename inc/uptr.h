#include<iostream>

template <class T>
class Uptr{
	private:
	T* ptr;

	public:
	Uptr():ptr(new T()) {
#ifdef DEBUG_INFO_CONSTRUCTOR
		std::cout<<"Constructed"<<std::endl;
#endif
	}


	~Uptr() {
#ifdef DEBUG
		std::cout<<"Destructed"<<std::endl;
		if( ptr == nullptr)
			std::cout<<"Null ptr found during desturction"<<std::endl;
#endif
		delete ptr;
	}


	Uptr(const Uptr&) = delete ;
	Uptr& operator =(const Uptr&) = delete;


	T* get(){
		return ptr;
	}

	T operator* (){
		return *ptr;
	}

	T* operator->(){
		return ptr;
	}

	Uptr(Uptr&& u):ptr(u.ptr) {
#ifdef DEBUG_INFO_CONSTRUCTOR
		std::cout<<"Move Consructed"<<std::endl;
#endif
		u.ptr = nullptr;
			
	}

	Uptr& operator= (Uptr&& u){
#ifdef DEBUG_INFO_CONSTRUCTOR
		std::cout<<"Move Assigned"<<std::endl;
#endif
		if( this == &u)
			return *this;
		if( ptr)
			delete ptr;

		ptr = u.ptr;
		u.ptr = nullptr;

		return *this;
	}

	template<class U>
	Uptr<T>& operator=(Uptr<U>&& u) {

		delete ptr;
		ptr = u.get();
		u.get() = nullptr;

		return *this;
	}
};

