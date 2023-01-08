#pragma once
#include <string>
#include "avl.hpp"
#include "Pair.hpp"
#include "array_sequence.hpp"
#include "main_container.hpp"

template<typename Type>
class Sorted_sequence2 : public Main_container<Type> {
protected:
	ArraySequence<Type>* sc;

public:
	Sorted_sequence2() {
		sc = new ArraySequence<Type>;
	}
	int bin_search(Type k) {
		int left = 0, right = this->sc->GetLength();
		while (left <= right) {
			int mid = (left + right) / 2;
			Type a = this->sc->Get(mid);
			if (a > k) {
				right = mid - 1;
			}
			else {
				left = mid + 1;
			}
		}

		Type b = this->sc->Get(left);
		if (b == k) {
			return left;
		}
		else {
			return -1;
		}
	}

	int add(Type k) override {
		if (this->sc->GetLength() == 0) {
			this->sc->Append(k);
			return 0;
		}
		int pos = this->sc->GetLength();
		for (int i = 0; i < this->sc->GetLength(); ++i) {
			Type a = this->sc->Get(i);
			if (a > k) {
				pos = i;
				break;
			}
		}
		this->sc->InsertAt(k, pos);
		return 0;
	}

	int delet(Type k) override {
		return 0;
	}

	int update(Type k, int q = 1) override {
		int pos = 0;
		for (int i = 0; i < this->sc->GetLength(); ++i) {
			Type a = this->sc->Get(i);
			if (a == k) {
				pos = i;
				break;
			}
		}
		this->sc->Set(k, pos);
		return 0;
	}

	bool find(Type k) override {
		if (this->sc->GetLength() == 0) {
			return false;
		}
		bool flag = false;
		for (int i = 0; i < this->sc->GetLength(); ++i) {
			Type a = this->sc->Get(i);
			if (a == k) {
				flag = true;
				break;
			}
		}
		return flag;
	}

	int get(Type k, Type& buf) override {
		int pos = 0;
		for (int i = 0; i < this->sc->GetLength(); ++i) {
			Type a = this->sc->Get(i);
			if (a == k) {
				buf = a;
				break;
			}
		}
		return 0;
	}


	int get_length() override {
		return this->sc->GetLength();
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
		return this->sc->Get(index);
	}

	ArraySequence<Type> getelement() override {
		return *(this->sc);
	}

};
