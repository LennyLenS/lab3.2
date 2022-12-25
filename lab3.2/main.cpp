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
#include "list_sequence.hpp"
#include "Pair.hpp"
#include "set.hpp"

using namespace std;

typedef struct parametrs{
	bool help = false;
	bool quit = false;
	bool test = false;
	bool run = false;
	bool error = false;
	bool iset = false;
	bool sort_seq = false;
	bool words = false;
	bool letters = false;
	int quant = 50;

	string data = "";
	bool file = false;
	string file_name = "test.txt";
}parametrs;

parametrs parsing(string s) {
	parametrs buf;
	static const regex r("^(help|((run|test){1}\\s*-(iset|sortseq)\\s*(-w|-l){1}\\s*(-q)?\\s*(\\d+)?\\s*(-f\\s*(\\S*))?)|quit)$");
	smatch mat;
	if (regex_search(s, mat, r)) {


		if (s.find("help") != -1) {
			buf.help = true;
		}
		if (s.find("iset") != -1) {
			buf.iset = true;
		}
		if (s.find("sortseq") != -1) {
			buf.sort_seq = true;
		}
		if (s.find("-w") != -1) {
			buf.words = true;
		}
		if (s.find("-l") != -1) {
			buf.letters = true;
		}
		if (s.find("-f") != -1) {
			buf.file = true;
			if (mat[8].str() != "") {
				buf.file_name = mat[9].str();
			}
		}
		if (s.find("run") != -1) {
			buf.run = true;

			if (mat[7].str() != "") {
				buf.quant = stoi(mat[7].str());
			}
		}
		if (s.find("test") != -1) {
			buf.test = true;
			if (mat[7].str() != "") {
				buf.quant = stoi(mat[7].str());
			}
		}


		if (s.find("quit") != -1) {
			buf.quit = true;
		}
	}
	else {
		buf.error = true;
	}

	return buf;
}

ListSequence<string> split(string s) {
	ListSequence<string> a;
	string tmp = "";
	while (s != "") {
		if (s.find(" ") != -1) {
			tmp = s.substr(0, s.find(" "));
			s = s.substr(s.find(" ") + 1, s.size() - s.find(" ") - 1);
			a.Append(tmp);
		}
		else {
			a.Append(s);
			s = "";
		}
	}

	return a;
}

int add_to_set(int &num_page, int &max_words, int &cur_num_words, string s, Set<Pair<string, ArraySequence<int> > >& iset) {
	if (cur_num_words + 1 <= max_words) {
		ArraySequence<int> arr;
		arr.Append(num_page);
		Pair<string, ArraySequence<int> > buf(s, arr);
		if (iset.find(buf)) {
			//cout << "add_to_set: " << buf << endl;
			iset.update(buf); 
		}
		else {
			//cout << "add_to_set: " << buf << endl;
			iset.add(buf);
		}

		cur_num_words++;
		return 1;
	}
	else {
		cur_num_words = 0;
		num_page++;
		return 0;
	}
}

int run(parametrs buf) {
	ListSequence<string> vec = split(buf.data);
	if (buf.words) {
		Set<Pair<string, ArraySequence<int> > > iset;
		int num_page = 1;
		int cur_num_words = 0;
		int i = 0;
		while(i < vec.GetLength()){
			if (num_page == 1) {
				int max_words = 0.5 * buf.quant;
				i += add_to_set(num_page, max_words, cur_num_words, vec.Get(i), iset);
			}
			else if (num_page % 10 == 0) {
				int max_words = 0.75 * buf.quant;
				i += add_to_set(num_page, max_words, cur_num_words, vec.Get(i), iset);
			}
			else {
				int max_words = buf.quant;
				i += add_to_set(num_page, max_words, cur_num_words, vec.Get(i), iset);
			}
		}
		ListSequence<Pair<string, ArraySequence<int> > > ans = iset.getelement();
		//cout << "run: ";
		for (int i = 0; i < ans.GetLength(); ++i) {
			Pair<string, ArraySequence<int> > b = ans.Get(i);
			cout << b << " ";
		}
		//cout << "\n";
	}
	if (buf.letters) {

	}

	return 0;
}

void update(parametrs buf) {
	if (buf.run) {
		run(buf);
	}
	else if (buf.help) {
		cout << "	run - command for making alphabetical index. Possible flags: \n \
			-w for separate with words \n\
			-l for separate with letters \n\
			-q for quantity \n\
			-iset for using set \n \
			-sortseq for using sorted sequance \n \
			-f for reading from file\n \
	quit for finish programme\n";
	}
}


int Input_file(parametrs& buf) {
	int error = 0;
	std::ifstream in(buf.file_name); // окрываем файл для чтения
	if (in.is_open())
	{
		std::getline(in, buf.data);
	}
	else {
		error = 1;
	}
	in.close();

	return error;
}


int main() { 
	srand(time(0));
	queue<parametrs> I_files, requests;
	std::mutex requests_mutex;
	std::mutex I_files_mutex;
	
	Set<Pair<string, ArraySequence<int> > > iset;
	ArraySequence<int> arr;
	arr.Append(1);
	string s = "1";
	Pair<string, ArraySequence<int> > buf(s, arr);
	buf.value = arr;
	cout << buf.value << endl;
	iset.find(buf);
	cout << buf.value;
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
				if (buf.run) {
					//std::getline(cin, s);
					if (buf.file) {
						I_files_mutex.lock();
						I_files.push(buf);
						I_files_mutex.unlock();
					}
					else {
						string s;
						std::getline(cin, s);
						buf.data = s;
						requests_mutex.lock();
						requests.push(buf);
						requests_mutex.unlock();
					}
				}
				else {
					requests_mutex.lock();
					requests.push(buf);
					requests_mutex.unlock();
				}
			}
			if (buf.quit) {
				I_files_mutex.lock();
				I_files.push(buf);
				I_files_mutex.unlock();
				requests_mutex.lock();
				requests.push(buf);
				requests.push(buf);
				requests_mutex.unlock();
			}
			quit = buf.quit;
			//getline(cin, s);
		} while (!quit);
	});

	thread files([&]() {
		bool quit = false;
		do {
			parametrs buf;
			I_files_mutex.lock();
			if (!I_files.empty()) {
				buf = I_files.front();
				I_files.pop();
			}
			I_files_mutex.unlock();
			if (buf.run) {
				int error = Input_file(buf);
				if (error == 1)
					cout << "Can not open file " << buf.file_name << endl;
				else {
					requests_mutex.lock();
					requests.push(buf);
					requests_mutex.unlock();
				}
			}
			quit = buf.quit;
		} while (!quit);
	});

	thread calc1([&]() {
		bool quit = false;
		do {
			parametrs buf;
			requests_mutex.lock();
			if (!requests.empty()) {
				buf = requests.front();
				requests.pop();
			}
			requests_mutex.unlock();
			if (buf.run || buf.help) {
				update(buf);
			}
			quit = buf.quit;
		} while (!quit);
	});

	thread calc2([&]() {
		bool quit = false;
		do {
			parametrs buf;
			requests_mutex.lock();
			if (!requests.empty()) {
				buf = requests.front();
				requests.pop();
			}
			requests_mutex.unlock();
			if (buf.run || buf.help) {
				update(buf);
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