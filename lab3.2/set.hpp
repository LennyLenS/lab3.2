#pragma once
#include <string>
#include "avl.hpp"
#include "main_container.hpp"
template<typename Type>
class Set: public Main_container<Type> {
protected:
	AVL<Type>* set;

public:
	Set() {
		set = new AVL<Type>;
	}

	int add(Type k) override {

		if (!this->set->find(k)) {
			this->set->add(k);
		}
		return 0;
	}

	int delet(Type k) override {
		this->set->delet(k);
		return 0;
	}

	int update(Type k, int q = 1) override{
		this->set->delet(k);
		this->set->add(k);
		
		return 0;
	}

	bool find(Type k) override {
		return this->set->find(k);
	}

	int get(Type k, Type &buf) override {
		this->set->get(k, buf);
		return 0; 
	}

	int Print() override {
		this->set->Print();
		return 0;
	}

	ArraySequence<Type> getelement() override {
		return this->set->getelements(); 
	}

};
