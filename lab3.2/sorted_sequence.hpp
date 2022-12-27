#pragma once
#include <string>
#include "avl.hpp"
#include "Pair.hpp"
#include "main_container.hpp"

template<typename Type>
class Sorted_sequence: public Main_container<Type> {
protected:
	AVL<Pair<Type, int>>* sorted_sequence;

public:
	Sorted_sequence() {
		sorted_sequence = new AVL<Pair<Type, int> >;
	}

	int add(Type k) override{
		Pair<Type, int> buf(k, 1);
		if (!this->sorted_sequence->find(buf)) {
			this->sorted_sequence->add(buf);
		}
		else {
			Pair<Type, int> a;
			this->sorted_sequence->get(buf, a);
			buf.value++;
			update(buf.key, buf.value);
		}
		return 0;
	}

	int delet(Type k) override{
		Pair<Type, int> buf(k, 1);
		this->sorted_sequence->delet(buf);
		return 0;
	}

	int update(Type k, int q = 1) override{
		Pair<Type, int> buf(k, q);
		this->sorted_sequence->delet(buf);
		this->sorted_sequence->add(buf);

		return 0;
	}

	bool find(Type k) override{
		Pair<Type, int> buf(k, 1);
		return this->sorted_sequence->find(buf);
	}

	int get(Type k, Type& buf) override{
		Pair<Type, int> k1(k, 1);
		Pair<Type, int> ans(k, 1);
		this->sorted_sequence->get(k1, ans);
		buf = ans.key;
		return 0;
	}

	int Print() override{
		this->sorted_sequence->Print();
		return 0;
	}

	int get_length() override {
		ArraySequence<Type> buf = this->getelement();
		return buf.GetLength();
	}

	int is_empty() override {
		if (this->get_length() == 0) {
			return 1;
		}
		else {
			return 0;
		}
	}

	Type get_index(int index) override {
		ArraySequence<Type> buf = this->getelement();
		return buf.Get(index);
	}
	ArraySequence<Type> getelement() override{
		ArraySequence<Pair<Type, int> > buf = this->sorted_sequence->getelements();
		ArraySequence <Type> ans;
		for (int i = 0; i < buf.GetLength(); ++i) {
			for (int j = 0; j < buf.Get(i).value; ++j) {
				ans.Append(buf.Get(i).key);
			}
		}
		return ans;
	}

};
