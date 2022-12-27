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
#include "sorted_sequence.hpp"

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
	int quant = 25;

	string data = "";
	bool file = false;
	bool out_file = false;
	string file_name = "test.txt";
	string out_file_name = "out_test.txt";
}parametrs;

parametrs parsing(string s) {
	parametrs buf;
	static const regex r("^(help|((run|test){1}\\s*-(iset|sortseq)\\s*(-w|-l){1}\\s*(-q)?\\s*(\\d+)?\\s*(-fi\\s*(\\S*))?\\s*(-fo\\s*(\\S*))?)|quit)$");
	smatch mat;
	if (regex_search(s, mat, r)) {
		/*
		for (int i = 0; i < mat.length(); ++i) {
			cout << i << " " << mat[i].str() << "\n";
		}
		*/
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
		if (s.find("-fi") != -1) {
			buf.file = true;
			if (mat[8].str() != "") {
				buf.file_name = mat[9].str();
			}
		}
		if (s.find("-fo") != -1) {
			buf.out_file = true;
			if (mat[10].str() != "") {
				buf.out_file_name = mat[11].str();
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

string del_spaces(string s) {
	string new_s = "";
	int a = 0;
	for (int i = 0; i < s.length(); ++i) {
		if (s[i] != ' ') {
			new_s += s[i];
			a = 0;
		}
		else {
			if (a == 0) {
				new_s += ' ';
				a++;
			}
		}
	}
	return new_s;
}

int add_to_set(int &num_page, int &max_quant, int &cur_num_words, int size, string s, Set<Pair<string, ArraySequence<int> > >& iset) {
	if (cur_num_words + size <= max_quant) {
		ArraySequence<int> arr;
		arr.Append(num_page);
		Pair<string, ArraySequence<int> > buf(s, arr);
		if (iset.find(buf)) {
			Pair<string, ArraySequence<int> > buf2;
			iset.get(buf, buf2);

			for (int i = 0; i < buf.value.GetLength(); ++i) {
				bool flag = false;
				for (int j = 0; j < buf2.value.GetLength(); ++j) {
					if (buf2.value.Get(j) == buf.value.Get(i)) {
						flag = true;
						break;
					}
				}

				if (!flag) {
					buf2.value.Append(buf.value.Get(i));
				}
			}

			iset.update(buf2); 
		}
		else {
			//cout << "add_to_set: " << buf << endl;
			iset.add(buf);
		}

		cur_num_words += size;
		return 1;
	}
	else {
		cur_num_words = 0;
		num_page++;
		return 0;
	}
}

int run(parametrs buf, ArraySequence<Pair<string, ArraySequence<int> > > &ans1) {
	bool error = false;
	ListSequence<string> vec = split(del_spaces(buf.data));
	Set<Pair<string, ArraySequence<int> > > iset;
	if (buf.words) {
		int num_page = 1;
		int cur_num_words = 0;
		int i = 0;
		while(i < vec.GetLength()){
			if (num_page == 1) {
				int max_words = 0.5 * buf.quant;
				i += add_to_set(num_page, max_words, cur_num_words, 1, vec.Get(i), iset);
			}
			else if (num_page % 10 == 0) {
				int max_words = 0.75 * buf.quant;
				i += add_to_set(num_page, max_words, cur_num_words, 1, vec.Get(i), iset);
			}
			else {
				int max_words = buf.quant;
				i += add_to_set(num_page, max_words, cur_num_words, 1, vec.Get(i), iset);
			}
		}		
	}
	if (buf.letters) {
		int num_page = 1;
		int cur_num_letter = 0;
		int i = 0;
		while (i < vec.GetLength()){
			if (vec.Get(i).length() > buf.quant) {
				error = true;
				break;
			}
			int max_letter = 0;
			if (num_page == 1) {
				max_letter = 0.5 * buf.quant;
				int size = vec.Get(i).length();
				if (cur_num_letter != 0) {
					size += 1;
				}
				i += add_to_set(num_page, max_letter, cur_num_letter, size, vec.Get(i), iset);
			}
			else if (num_page % 10 == 0) {
				max_letter = 0.75 * buf.quant;
				int size = vec.Get(i).length();
				if (cur_num_letter != 0) {
					size += 1;
				}
				i += add_to_set(num_page, max_letter, cur_num_letter, size, vec.Get(i), iset);
			}
			else {
				max_letter = buf.quant;
				int size = vec.Get(i).length();
				if (cur_num_letter != 0) {
					size += 1;
				}
				i += add_to_set(num_page, max_letter, cur_num_letter, size, vec.Get(i), iset);
			}
		}
	}
	if (error) {
		cout << "Impossible to split words\n";
	}
	else if(!buf.out_file){
		ArraySequence<Pair<string, ArraySequence<int> > > ans = iset.getelement();
		for (int i = 0; i < ans.GetLength(); ++i) {
			Pair<string, ArraySequence<int> > b = ans.Get(i);
			cout << "Word " << b.key << " was found in: " << b.value << "\n";
		}
	}
	else {
		ArraySequence<Pair<string, ArraySequence<int> > > ans = iset.getelement();
		ans1 = ans;
	}
	return 0;
}

void update(parametrs buf, ArraySequence<Pair<string, ArraySequence<int> > > &ans) {
	if (buf.run) {
		run(buf, ans);
	}
	else if (buf.help) {
		cout << "	run - command for making alphabetical index. Possible flags: \n \
			-w for separate with words \n\
			-l for separate with letters \n\
			-q for quantity \n\
			-iset for using set \n \
			-sortseq for using sorted sequance \n \
			-fi for reading from file\n \
			-fo for reading from file\n \
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

int Output_file(Pair< ArraySequence<Pair<string, ArraySequence<int> > >, string> &a) {
	int error = 0;
	std::ofstream out(a.value); // окрываем файл для записи
	if (out.is_open())
	{
		for (int i = 0; i < a.key.GetLength(); ++i) {
			Pair<string, ArraySequence<int> > b = a.key.Get(i);
			out << "Word " << b.key << " was found in: " << b.value << "\n";
		}
	}
	else {
		error = 1;
	}
	out.close();

	return error;
}

int main() { 
	srand(time(0));
	queue<parametrs> I_files, requests;
	queue< Pair< ArraySequence<Pair<string, ArraySequence<int> > >, string> > O_files;
	std::mutex requests_mutex;
	std::mutex I_files_mutex;
	std::mutex O_files_mutex;

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

	thread Input_files([&]() {
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

	thread Output_files([&]() {
		bool quit = false;
		do {
			int file = 0;
			Pair< ArraySequence<Pair<string, ArraySequence<int> > >, string> a;
			O_files_mutex.lock();
			if (!O_files.empty()) {
				a = O_files.front();
				O_files.pop();
				file = 1;
			}
			O_files_mutex.unlock();
			if (file == 1) {
				if (a.value != "NULL") {
					int error = Output_file(a);
					if (error == 1)
						cout << "Can not open file " << a.value << endl;
				}
				else {
					quit = true;
				}
			}
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
				ArraySequence<Pair<string, ArraySequence<int> > > ans;
				update(buf, ans);
				if (buf.out_file) {
					O_files_mutex.lock();
					Pair< ArraySequence<Pair<string, ArraySequence<int> > >, string> a(ans, buf.out_file_name);
					O_files.push(a);
					O_files_mutex.unlock();
				}
			}
			quit = buf.quit;
			if (quit) {
				O_files_mutex.lock();
				ArraySequence < Pair<string, ArraySequence<int> > > arr;
				Pair< ArraySequence<Pair<string, ArraySequence<int> > >, string> a(arr, "NULL");
				O_files.push(a);
				O_files_mutex.unlock();
			}
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
				ArraySequence<Pair<string, ArraySequence<int> > > ans;
				update(buf, ans);
				if (buf.out_file) {
					O_files_mutex.lock();
					Pair< ArraySequence<Pair<string, ArraySequence<int> > >, string> a(ans, buf.out_file_name);
					O_files.push(a);
					O_files_mutex.unlock();
				}
			}
			quit = buf.quit;
			if (quit) {
				O_files_mutex.lock();
				ArraySequence < Pair<string, ArraySequence<int> > > arr;
				Pair< ArraySequence<Pair<string, ArraySequence<int> > >, string> a(arr, "NULL");
				O_files.push(a);
				O_files_mutex.unlock();
			}
	} while (!quit);
	});


	console.join();
	Input_files.join();
	Output_files.join();
	calc1.join();
	calc2.join();

	return 0;
}