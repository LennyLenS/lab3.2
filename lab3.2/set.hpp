#ifndef SET_HPP
#define SET_HPP
#include <string>
#include <vector>
#include "avl.hpp"

template<typename Type>
class Set {
protected:
	AVL<Type>* set;

public:
	Set() {
		set = new AVL<Type>;
	}

	int add(Type k) {
		if (!this->set->find(k)) {
			this->set->add(k);
		}
		return 0;
	}
	
	bool find(Type k) {
		return this->set->find(k);
	}

	int delet(Type k) {
		this->set->delet(k);
		return 0;
	}

	int map(Type(*f)(Type)) {
		this->set->map(f);
		return 0;
	}

	int reduce(Type(*f)(Type, Type)) {
		return this->set->reduce(f);
	}

	Set<Type>* where(bool(*f)(Type)) {
		Set<Type>* n_set = new Set<Type>;
		n_set->set->where(f);
		return n_set;
	}

	int Print2() {
		this->set->Print2();
		return 0;
	}

	std::string Print() {
		return this->set->Print();
	}

	int sum(Set<Type>* a) {
		std::vector<Type> val = a->set->getelement();
		for (int i = 0; i < val.size(); ++i) {
			if (!this->set->find(val[i])) {
				this->set->add(val[i]);
			}
		}
		return 0;
	}

	int Intersection(Set<Type>* a) {
		std::vector<Type> val = a->set->getelement();
		AVL<Type>* new_tree = new AVL<Type>;
		for (int i = 0; i < val.size(); ++i) {
			if (this->set->find(val[i])) {
				new_tree->add(val[i]);
			}
		}
		this->set = new_tree;
		return 0;
	}

	int Subtraction(Set<Type>* a) {
		std::vector<Type> val = this->set->getelement();
		AVL<Type>* new_tree = new AVL<Type>;
		for (int i = 0; i < val.size(); ++i) {
			if (!(a->find(val[i]))) {
				new_tree->add(val[i]);
			}
		}
		this->set = new_tree;
		return 0;
	}
};


#endif