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
	thread console([&]() {
		bool quit = false;
		do {
			parametrs buf;
			string s;
			std::getline(cin, s);
			buf = parsing(s);
			if (buf.error) {
				cout << "Error in the request: " << s << "\n";
			}
			else {
				if (buf.sort) {
					int n;
					cin >> n;
					ArraySequence<int>* vec = new ArraySequence<int>();
					for (int i = 0; i < n; ++i) {
						int x;
						cin >> x;
						vec->Append(x);
					}
					buf.vec = vec;
					std::getline(cin, s);
				}
				requests_mutex.lock();
				requests.push(buf);
				requests_mutex.unlock();
			}
			quit = buf.quit;
			//getline(cin, s);
		} while (!quit);
	});

	thread files([&]() {
		
	});

	thread calc1([&]()
		{
			bool quit = false;
		do {
			parametrs buf;
			requests_mutex.lock();
			if (!requests.empty()) {
				buf = requests.front();
				requests.pop();
			}
			requests_mutex.unlock();
			if (buf.sort || buf.test || buf.help) {
				update(buf);
				if (buf.vec != nullptr)
					delete buf.vec;
			}
			quit = buf.quit;
		} while (!quit);
		});

	thread calc2([&]()
		{
			bool quit = false;
		do {
			parametrs buf;
			requests_mutex.lock();
			if (!requests.empty()) {
				buf = requests.front();
				requests.pop();
			}
			requests_mutex.unlock();
			if (buf.sort || buf.test || buf.help) {
				update(buf);
				if (buf.vec != nullptr)
					delete buf.vec;
			}
			quit = buf.quit;
		} while (!quit);
	});

	console.join();
	files.join();
	calc1.join();
	calc2.join();

	return 0;
}

class Petua {
private:
	typedef struct papa {
		int a;
	}papa;
	struct papa Find();
};

Petua::papa Petua::Find() {

}