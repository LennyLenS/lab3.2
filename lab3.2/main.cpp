#include <iostream>
#include <fstream>
#include <random>
#include <ctime>
#include <chrono>
#include <thread>
#include <mutex>
#include <queue>
#include <regex>
#include "array_sequence.hpp"

#include "Pair.hpp"
#include "set.hpp"

using namespace std;

typedef struct parametrs{
	bool help = false;
	bool quit = false;
	bool test = false;
	bool error = false;
	bool iset = false;

	ArraySequence<string>* vec = nullptr;
	bool file = false;
	string file_name = "";
}parametrs;

parametrs parsing(string s) {
	parametrs buf;
	static const regex r("^(help|((sort|test){1}\\s*-(as|ls)\\s*(-qs|-bs|-sh|-is|-cs|\\s)*\\s*(-range\\s*(\\d+)\\s*(\\d+))?\\s*(-step\\s*(\\d+))?)|quit)$");
	smatch mat;

	if (regex_search(s, mat, r)) {
		
	}
	else {
		buf.error = true;
	}

	return buf;
}

int main() { 
	srand(time(0));
	queue<parametrs> IO_files, requests;
	std::mutex requests_mutex;
	std::mutex IO_files_mutex;

	Set<Pair<int, int> > iset;
	Pair<int, int> b;
	for (int i = 0; i < 5; ++i) {
		Pair<int, int> a(rand(), rand());
		iset.add(a);
		b = a;
	}

	iset.Print();

	b.value *= 2;

	iset.update(b);
	cout << "\n";

	iset.Print();

	thread console([&]() {
		
	});

	thread files([&]() {
		
	});

	thread calc1([&]() {
		
	});

	thread calc2([&]() {
			
	});

	console.join();
	files.join();
	calc1.join();
	calc2.join();

	return 0;
}