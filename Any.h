#pragma once
#ifndef MY_ANY_H
#define MY_ANY_H

#include"config.h"
_MGE_BEGIN
/*
//any不拥有资源,单纯弱引用.
struct Any {
	void * object_ptr;
	explicit  Any(void* ptr=nullptr) :object_ptr(ptr) {}
	Any(const Any& a) :object_ptr(a.object_ptr) {}
	Any& operator=(const Any&a) {
		object_ptr = a.object_ptr;
		return *this;
	}
	Any& operator=(void *ptr) {
		object_ptr = ptr;
		return *this;
	}

	~Any() { }
};
template<class T>
T&
any_cast(const Any&a) {
	return *static_cast<T*>(a.object_ptr);
}


*/
_MGE_END
#endif // !MY_ANY_H
