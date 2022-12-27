#pragma once
#include "array_sequence.hpp"

template<typename Type>
class Main_container {
public:

	virtual int add(Type k) = 0;

	virtual int delet(Type k) = 0;

	virtual int update(Type k, int q = 1) = 0;

	virtual bool find(Type k)  = 0;

	virtual int get(Type k, Type& buf) = 0;

	virtual int Print() = 0;

	virtual ArraySequence<Type> getelement() = 0;

};
