#include <iostream>
// unistd.h and getopt.h for parser command line parameters
#include <unistd.h>
#include <getopt.h>
#include <string>
#include <string.h>
#include <vector>
#include <map>
#include <fstream>
#define GAP 'a'
extern "C" { FILE __iob_func[3] = { *stdin,*stdout,*stderr }; }
using std::string;
using std::cout;
using std::endl;
using std::vector;
using std::map;
using std::pair;
using std::make_pair;
int word_count;
vector<vector<string>>* result = new vector<vector<string>>();
vector<string>* tmpresult = new vector<string>();
int used[26];
void mostWords2(map<char, vector<pair<string, bool>>>*words);
void mostLetters2(map<char, vector<pair<string, bool>>>*words);
void fixed_num2(map<char, vector<pair<string, bool>>>*words,int n);
void fixed_head2(map<char, vector<pair<string, bool>>>*words, char head);
void fixed_tail2(map<char, vector<pair<string, bool>>>*words, char tail);
void binary_w_x(map<char, vector<pair<string, bool>>>*words, char type, char head_tail, int n);
void binary_c_x(map<char, vector<pair<string, bool>>>*words, char type, char head_tail, int n);
void binary_n_x(map<char, vector<pair<string, bool>>>*words, char type, char head_tail, int n);
void binary_t_h(map<char, vector<pair<string, bool>>>*words, char head, char tail);
void triple_w_x1_x2(map<char, vector<pair<string, bool>>>*words, char type1, char type2, char head, char tail, int n);
void triple_c_x1_x2(map<char, vector<pair<string, bool>>>*words, char type1, char type2, char head, char tail, int n);
void triple_h_t_n(map<char, vector<pair<string, bool>>>*words, char head, char tail, int n);
void quadruple_c_h_t_n(map<char, vector<pair<string, bool>>>*words, char head, char tail, int n);
void quadruple_w_h_t_n(map<char, vector<pair<string, bool>>>*words, char head, char tail, int n);
vector<vector<string>> mostWords(map<char, vector<pair<string, bool>>>*);
void search_w(map<char, vector<pair<string, bool>>>*words, char start, int index);
void search_c(map<char, vector<pair<string, bool>>>*words, char start, int index);
void search_n(map<char, vector<pair<string, bool>>>*words, char start, int index,int n);
void search_h(map<char, vector<pair<string, bool>>>*words, char start, int index);
void search_t(map<char, vector<pair<string, bool>>>*words, char start, int index,char tail);
vector<vector<string>> mostLetters(map<char, vector<pair<string, bool>>>* words);
vector<vector<string>> fixed_num(map<char, vector<pair<string, bool>>>* words, int n);
vector<vector<string>> fixed_head_tail(map<char, vector<pair<string, bool>>>* words, char head, char tail);
map<char, vector<pair<string, bool>>>* preprocess(string filename);
int letter_count(vector<string> wolrdlist);
void reset(map<char, vector<pair<string, bool>>>*);
int main(int argc, char* argv[]) {
	// < -- parser command arguments -- >
	const char* optstring = "wch:t:n:";
	bool choice_w = false; 
	bool choice_c = false;
	bool head = false;
	bool tail = false;
	bool fixedlength = false;
	bool conflictflag = false; // is -c and -w both used in the parameter
	// if constraint head character or tail character
	char headChar, tailChar;
	string inputFileName;
	int c;
	opterr = 0;
	int length; // the length of the word chain assigned
	while ((c = getopt(argc, argv, optstring)) != -1) {
		switch (c) {
		case 'w': {
			if (conflictflag) {
				cout << "ERROR:You can't choose both most words and most character both" << endl;
				exit(0);
			}
			else {
				choice_w= true;
				conflictflag = true;
				break;
			}
		}
		case 'c': {
			if (conflictflag) {
				cout << "ERROR:You can't choose both most words and most characters both" << endl;
				exit(0);
			}
			else {
				choice_c = true;
				//inputFileName = optarg;
				conflictflag = true;
				break;
			}
		}
		case 'h': {
			if (strlen(optarg) > 1 || opterr) {
				cout << "ERROR:You can only assign one character as head character" << endl;
				exit(0);
			}
			else {
				head = true;
				headChar = optarg[0];
				break;
			}
		}
		case 't': {
			if (strlen(optarg) > 1 || opterr) {
				cout << "ERROR:You can only assign one character as tail character" << endl;
				exit(0);
			}
			else {
				tail = true;
				tailChar = optarg[0];
				break;
			}
		}
		case 'n': {
			if (opterr) {
				cout << "ERROR:You must assign a number of the -n parameter,line -n number";
				exit(0);
			}
			else {
				length = atoi(optarg);
				fixedlength = true;
				break;
			}
		}
		default:
			cout << "ERROR:unrecognized parameter!" << endl;
			break;
		}
	}
	if (!conflictflag) {
		cout << "ERROR:You must have -w or -c parameter" << endl;
		exit(0);
	}
	if (argc == optind) {
		cout << "ERROR:You must have a file to input" << endl;
		exit(0);
	}
	else {
		inputFileName = argv[argc - 1];
	}
	// < -- parser command line arguments finished -- >
	auto words = preprocess(inputFileName);
	//map<char,vector<pair<string,bool>>>* words = new map<char,vector<pair<string,bool>>>;
	//(*words)['a'].push_back(make_pair("algebra",false));
	//(*words)['a'].push_back(make_pair("apple",false));
	//(*words)['z'].push_back(make_pair("zoo",false));
	//(*words)['e'].push_back(make_pair("elephant",false));
	//(*words)['u'].push_back(make_pair("under",false));
	//(*words)['f'].push_back(make_pair("fox",false));
	//(*words)['d'].push_back(make_pair("dog",false));
	//(*words)['m'].push_back(make_pair("moon",false));
	//(*words)['l'].push_back(make_pair("leaf",false));
	//(*words)['t'].push_back(make_pair("trick",false));
	//(*words)['h'].push_back(make_pair("hello",false));
	//(*words)['n'].push_back(make_pair("neer",false));
	//(*words)['s'].push_back(make_pair("softw",false));
	//(*words)['w'].push_back(make_pair("world",false));
	//vector<vector<string>> result;
	if (choice_w&&!choice_c&&!head&&!tail&&!fixedlength) {
		//£¨1£¬0£¬0£¬0£¬0£©
		mostWords2(words);
	}
	else if (!choice_w && choice_c && !head && !tail && !fixedlength) {
		//£¨0£¬1£¬0£¬0£¬0£©
		mostLetters2(words);
	}
	else if (!choice_w && !choice_c && head && !tail && !fixedlength) {
		//£¨0£¬0£¬1£¬0£¬0£©
		fixed_head2(words,headChar);
	}
	else if (!choice_w && !choice_c && !head && tail && !fixedlength) {
		//£¨0£¬0£¬0£¬1£¬0£©
		fixed_tail2(words,tailChar);
	}
	else if (!choice_w && !choice_c && !head && !tail && fixedlength) {
		//£¨0£¬0£¬0£¬0£¬1£©
		fixed_num2(words,length);
	}
	else if (choice_w && !choice_c && head && !tail && !fixedlength) {
		//£¨1£¬0£¬1£¬0£¬0£©
		binary_w_x(words,'h',headChar,0);
	}
	else if (choice_w && !choice_c && !head && tail && !fixedlength) {
		//£¨1£¬0£¬0£¬1£¬0£©
		binary_w_x(words, 't', tailChar, 0);
	}
	else if (choice_w && !choice_c && !head && !tail && fixedlength) {
		//£¨1£¬0£¬0£¬0£¬1£©
		binary_w_x(words, 'n', 'a', length);
	}
	else if (!choice_w && choice_c && head && !tail && !fixedlength) {
		//£¨0£¬1£¬1£¬0£¬0£©
		binary_c_x(words, 'h', headChar, 0);
	}
	else if (!choice_w && choice_c && !head && tail && !fixedlength) {
		//£¨0£¬1£¬0£¬1£¬0£©
		binary_c_x(words, 't', tailChar, 0);
	}
	else if (!choice_w && choice_c && !head && !tail && fixedlength) {
		//£¨0£¬1£¬0£¬0£¬1£©
		binary_c_x(words, 'n', 'a', length);
	}
	else if (!choice_w && !choice_c && head && tail && !fixedlength) {
		//£¨0£¬0£¬1£¬1£¬0£©
		binary_t_h(words, headChar, tailChar);
	}
	else if (!choice_w && !choice_c && head && !tail && fixedlength) {
		//£¨0£¬0£¬1£¬0£¬1£©
		binary_n_x(words, 'h', headChar, length);
	}
	else if (!choice_w && !choice_c && !head && tail && fixedlength) {
		//£¨0£¬0£¬0£¬1£¬1£©
		binary_n_x(words, 't', tailChar, length);
	}
	else if (choice_w && !choice_c && head && tail && !fixedlength) {
		//£¨1£¬0£¬1£¬1£¬0£©
		triple_w_x1_x2(words, 't', 'h', headChar, tailChar, 0);
	}
	else if (choice_w && !choice_c && head && !tail && fixedlength) {
		//£¨1£¬0£¬1£¬0£¬1£©
		triple_w_x1_x2(words, 'h', 'n', headChar, 'a', length);
	}
	else if (choice_w && !choice_c && !head && tail && fixedlength) {
		//£¨1£¬0£¬0£¬1£¬0£©
		triple_w_x1_x2(words, 't', 'n', 'a', headChar, length);
	}
	else if (!choice_w && choice_c && head && tail && !fixedlength) {
		//£¨0£¬1£¬1£¬1£¬0£©
		triple_c_x1_x2(words, 't', 'h', headChar, tailChar, 0);
	}
	else if (!choice_w && choice_c && head && !tail && fixedlength) {
		//£¨0£¬1£¬1£¬0£¬1£©
		triple_c_x1_x2(words, 'h', 'n', headChar, 'a', length);
	}
	else if (!choice_w && choice_c && !head && tail && fixedlength) {
		//£¨0£¬1£¬0£¬1£¬1£©
		triple_c_x1_x2(words, 't', 'n', 'a', headChar, length);
	}
	else if (!choice_w && !choice_c && head && tail && fixedlength) {
		//£¨0£¬0£¬1£¬1£¬1£©
		triple_h_t_n(words, headChar, tailChar, length);
	}
	else if (choice_w && !choice_c && head && tail && fixedlength) {
		//£¨1£¬0£¬1£¬1£¬1£©
		quadruple_w_h_t_n(words, headChar, tailChar, length);
	}
	else if (!choice_w && choice_c && head && tail && fixedlength) {
		//£¨0£¬1£¬1£¬1£¬1£©
		quadruple_c_h_t_n(words, headChar, tailChar, length);
	}
	else {
		cout << "ERROR:invaild choices" << endl;
		exit(0);
	}
	//triple_c_x1_x2(words,'t','h','p','m',0);
	for (auto &worldlist : *result) {
		for (auto& i : worldlist) {
			cout << i << endl;
		}
		cout << endl;
	}
	getchar();
}
vector<vector<string>> mostWords(map<char, vector<pair<string, bool>>>* words) {
	vector<string> tmpres = vector<string>();
	vector<string> res = vector<string>();
	char c = 'a';
	for (; c <= 'z'; c++) {
		if (words->count(c)) {
			//tmpres.clear();
			for (int i = 0; i < (*words)[c].size(); i++) {
				string start = (*words)[c][i].first;
				(*words)[c][0].second = true;
				tmpres.push_back(start);
				char next = start.at(start.size() - 1);
				while (words->count(next)) {
					int k = 0;
					char old_next;
					for (; k < (*words)[next].size(); k++) {
						if (!(*words)[next][k].second) {
							tmpres.push_back((*words)[next][k].first);
							(*words)[next][k].second = true;
							old_next = next;
							next = (*words)[next][k].first.at((*words)[next][k].first.size() - 1);
							break;
						}
						else {
							continue;
						}
					}
					if (k == (*words)[old_next].size()) {
						break;
					}
				}
				if (tmpres.size() > res.size()) {
					res = tmpres;
					tmpres.clear();
					reset(words);
				}
				else {
					tmpres.clear();
					reset(words);
					continue;
				}


			}
		}
	}
	vector<vector<string>> result = vector<vector<string>>();
	result.push_back(res);
	return result;
}
vector<vector<string>> mostLetters(map<char, vector<pair<string, bool>>>* words) {
	vector<string> tmpres = vector<string>();
	vector<string> res = vector<string>();
	char c = 'a';
	int res_letters = 0;
	int tmpres_letters = 0;
	for (; c <= 'z'; c++) {
		if (words->count(c)) {
			//tmpres.clear();
			for (int i = 0; i < (*words)[c].size(); i++) {
				string start = (*words)[c][i].first;
				(*words)[c][0].second = true;
				tmpres.push_back(start);
				char next = start.at(start.size() - 1);
				while (words->count(next)) {
					int k = 0;
					char old_next;
					for (int k = 0; k < (*words)[next].size(); k++) {
						if (!(*words)[next][k].second) {
							tmpres.push_back((*words)[next][k].first);
							(*words)[next][k].second = true;
							old_next = next;
							next = (*words)[next][k].first.at((*words)[next][k].first.size() - 1);
							break;
						}
						else {
							continue;
						}
					}
					if (k == (*words)[old_next].size()) {
						break;
					}
				}
				res_letters = letter_count(res);
				tmpres_letters = letter_count(tmpres);
				if (tmpres_letters > res_letters) {
					res = tmpres;
					tmpres.clear();
					reset(words);
				}
				else {
					tmpres.clear();
					reset(words);
					continue;
				}


			}
		}
	}
	vector<vector<string>> result = vector<vector<string>>();
	result.push_back(res);
	return result;
}
vector<vector<string>> fixed_num(map<char, vector<pair<string, bool>>>* words, int n) {
	vector<string> tmpres = vector<string>();
	vector<vector<string>> res = vector<vector<string>>();
	char c = 'a';
	for (; c <= 'z'; c++) {
		if (words->count(c)) {
			//tmpres.clear();
			for (int i = 0; i < (*words)[c].size(); i++) {
				string start = (*words)[c][i].first;
				(*words)[c][0].second = true;
				tmpres.push_back(start);
				char next = start.at(start.size() - 1);
				while (words->count(next)) {
					int k = 0;
					char old_next;
					for (; k < (*words)[next].size(); k++) {
						if (!(*words)[next][k].second) {
							tmpres.push_back((*words)[next][k].first);
							(*words)[next][k].second = true;
							old_next = next;
							next = (*words)[next][k].first.at((*words)[next][k].first.size() - 1);
							break;
						}
						else {
							continue;
						}
					}
					if (tmpres.size() == n) {
						res.push_back(tmpres);
						tmpres.clear();
						reset(words);
						break;
					}
					if (k == (*words)[old_next].size()) {
						break;
					}
				}
				tmpres.clear();
				reset(words);
				continue;
			}
		}
	}
	return res;
}
vector<vector<string>> fixed_head_tail(map<char, vector<pair<string, bool>>>* words, char head, char tail) {
	vector<string> tmpres = vector<string>();
	vector<vector<string>> res = vector<vector<string>>();
	char c = head;
	if (c == ' ') {
		c = 'a';
		for (; c <= 'z'; c++) {
			if (words->count(c)) {
				//tmpres.clear();
				for (int i = 0; i < (*words)[c].size(); i++) {
					string start = (*words)[c][i].first;
					(*words)[c][0].second = true;
					tmpres.push_back(start);
					if (tmpres.size() > 0) {
						if (tail == ' ') {
							res.push_back(tmpres);
						}
						else if (tmpres.back().at(tmpres.back().size() - 1) == tail) {
							res.push_back(tmpres);
						}
					}
					char next = start.at(start.size() - 1);
					while (words->count(next)) {
						int k = 0;
						char old_next;
						for (; k < (*words)[next].size(); k++) {
							if (!(*words)[next][k].second) {
								tmpres.push_back((*words)[next][k].first);
								if (tmpres.size() > 0) {
									if (tail == ' ') {
										res.push_back(tmpres);
									}
									else if (tmpres.back().at(tmpres.back().size() - 1) == tail) {
										res.push_back(tmpres);
									}
								}
								(*words)[next][k].second = true;
								old_next = next;
								next = (*words)[next][k].first.at((*words)[next][k].first.size() - 1);
								break;
							}
							else {
								continue;
							}
						}
						if (k == (*words)[old_next].size()) {
							break;
						}
					}
					tmpres.clear();
					reset(words);
					continue;
				}
			}
		}
	}
	else if (words->count(c)) {
		//tmpres.clear();
		for (int i = 0; i < (*words)[c].size(); i++) {
			string start = (*words)[c][i].first;
			(*words)[c][0].second = true;
			tmpres.push_back(start);
			if (tmpres.size() > 0) {
				if (tail == ' ') {
					res.push_back(tmpres);
				}
				else if (tmpres.back().at(tmpres.back().size() - 1) == tail) {
					res.push_back(tmpres);
				}
			}
			char next = start.at(start.size() - 1);
			while (words->count(next)) {
				int k = 0;
				char old_next;
				for (int k = 0; k < (*words)[next].size(); k++) {
					if (!(*words)[next][k].second) {
						tmpres.push_back((*words)[next][k].first);
						if (tmpres.size() > 0) {
							if (tail == ' ') {
								res.push_back(tmpres);
							}
							else if (tmpres.back().at(tmpres.back().size() - 1) == tail) {
								res.push_back(tmpres);
							}
						}
						(*words)[next][k].second = true;
						old_next = next;
						next = (*words)[next][k].first.at((*words)[next][k].first.size() - 1);
						break;
					}
					else {
						continue;
					}
					if (k == (*words)[old_next].size()) {
						break;
					}
				}
			}
			tmpres.clear();
			reset(words);
			continue;
		}
	}
	return res;
}
int letter_count(vector<string> wolrdlist) {
	int res = 0;
	for (auto word : wolrdlist) {
		res += word.length();
	}
	return res;
}
void reset(map<char, vector<pair<string, bool>>>* wordmap) {
	for (auto it = wordmap->begin(); it != wordmap->end(); it++) {
		for (auto& iter : it->second) {
			iter.second = false;
		}
	}
}
map<char, vector<pair<string, bool>>>* preprocess(string filename) {
	auto worldmap = new map<char, vector<pair<string, bool>>>;
	word_count = 0;
	std::ifstream ifs(filename);
	if (ifs) {
		//cout << "open file success" << endl;
	}
	else {
		cout << "EORROR:open file failed" << endl;
		exit(0);
	}
	char c;
	string temp = "";
	while (ifs.get(c))
	{
		if (c >= 'a'&&c <= 'z') {
			temp += c;
			continue;
		}
		if (c >= 'A'&&c <= 'Z') {
			c = c - 'A' + 'a';
			temp += c;
			continue;
		}
		if (temp != "") {
			c = temp.at(0);
			if (worldmap->count(c) == 0) {
				auto worldlist = new vector<pair<string, bool>>;
				pair<string, bool> world(temp, false);
				worldlist->push_back(world);
				worldmap->insert(pair<char, vector<pair<string, bool>>>(c, *worldlist));
				word_count++;
			}
			else {
				pair<string, bool> world(temp, false);
				(*worldmap)[c].push_back(world);
				word_count++;
			}
		}
		temp = ""; //clear temp
	}
	if (temp != "") {
		c = temp.at(0);
		if (worldmap->count(c) == 0) {
			auto worldlist = new vector<pair<string, bool>>;
			pair<string, bool> world(temp, false);
			worldlist->push_back(world);
			worldmap->insert(pair<char, vector<pair<string, bool>>>(c, *worldlist));
			word_count++;
		}
		else {
			pair<string, bool> world(temp, false);
			(*worldmap)[c].push_back(world);
		}
	}
	return worldmap;
}
void  mostWords2(map<char, vector<pair<string, bool>>>*words) {
	char c = 'a';
	for (; c <= 'z'; c++) {
		if (words->count(c)) {
			for (int i = 0; i < (*words)[c].size(); i++) {
				tmpresult->push_back((*words)[c][i].first);
				(*words)[c][i].second = true;
				used[c - GAP] ++;
				search_w(words, c, i);
				tmpresult->pop_back();
				(*words)[c][i].second = false;
				used[c - GAP] --;
			}
		}
	}
}
void search_w(map<char, vector<pair<string, bool>>>*words, char start, int index) {

	char next = (*words)[start][index].first.at((*words)[start][index].first.size() - 1);
	if (!words->count(next) || used[next - GAP] == (*words)[next].size()) {
		if (result->empty()) {
			result->push_back(*tmpresult);
		}
		else {
			if ((*result)[0].size() < tmpresult->size()) {
				result->clear();
				result->push_back(*tmpresult);
			}
			else if ((*result)[0].size() == tmpresult->size()) {
				result->push_back(*tmpresult);
			}
		}
		return;
	}
	else {
		for (int i = 0; i < (*words)[next].size(); i++) {
			if (!(*words)[next][i].second) {
				tmpresult->push_back((*words)[next][i].first);
				(*words)[next][i].second = true;
				used[next - GAP]++;
				search_w(words, (*words)[next][i].first.at(0), i);
				tmpresult->pop_back();
				(*words)[next][i].second = false;
				used[next - GAP] --;
			}
			else {
				continue;
			}
		}
	}
}
void  mostLetters2(map<char, vector<pair<string, bool>>>*words) {
	char c = 'a';
	for (; c <= 'z'; c++) {
		if (words->count(c)) {
			for (int i = 0; i < (*words)[c].size(); i++) {
				tmpresult->push_back((*words)[c][i].first);
				(*words)[c][i].second = true;
				used[c - GAP] ++;
				search_c(words, c, i);
				tmpresult->pop_back();
				(*words)[c][i].second = false;
				used[c - GAP] --;
			}
		}
	}
}
void search_c(map<char, vector<pair<string, bool>>>*words, char start, int index) {

	char next = (*words)[start][index].first.at((*words)[start][index].first.size() - 1);
	if (!words->count(next) || used[next - GAP] == (*words)[next].size()) {
		if (result->empty()) {
			result->push_back(*tmpresult);
		}
		else {
			int tmp_count = letter_count(*tmpresult);
			int res_count = letter_count((*result)[0]);
			if (res_count < tmp_count) {
				result->clear();
				result->push_back(*tmpresult);
			}
			else if (res_count == tmp_count) {
				result->push_back(*tmpresult);
			}
		}
		return;
	}
	else {
		for (int i = 0; i < (*words)[next].size(); i++) {
			if (!(*words)[next][i].second) {
				tmpresult->push_back((*words)[next][i].first);
				(*words)[next][i].second = true;
				used[next - GAP]++;
				search_c(words, (*words)[next][i].first.at(0), i);
				tmpresult->pop_back();
				(*words)[next][i].second = false;
				used[next - GAP] --;
			}
			else {
				continue;
			}
		}
	}
}
void  fixed_num2(map<char, vector<pair<string, bool>>>*words,int n) {
	char c = 'a';
	if (n <= 0) {
		cout << "ERROR:n shoud be a number >0" << endl;
		exit(0);
	}
	for (; c <= 'z'; c++) {
		if (words->count(c)) {
			for (int i = 0; i < (*words)[c].size(); i++) {
				tmpresult->push_back((*words)[c][i].first);
				(*words)[c][i].second = true;
				used[c - GAP] ++;
				search_n(words, c, i, n - 1);
				tmpresult->pop_back();
				(*words)[c][i].second = false;
				used[c - GAP] --;
			}
		}
	}
}
void search_n(map<char, vector<pair<string, bool>>>*words, char start, int index,int n) {

	char next = (*words)[start][index].first.at((*words)[start][index].first.size() - 1);
	if (!words->count(next) || used[next - GAP] == (*words)[next].size()||n==0) {
		if (n == 0) {
			result->push_back(*tmpresult);
		}
		return;
	}
	else {
		for (int i = 0; i < (*words)[next].size(); i++) {
			if (!(*words)[next][i].second) {
				tmpresult->push_back((*words)[next][i].first);
				(*words)[next][i].second = true;
				used[next - GAP]++;
				search_n(words, (*words)[next][i].first.at(0), i ,n-1);
				tmpresult->pop_back();
				(*words)[next][i].second = false;
				used[next - GAP] --;
			}
			else {
				continue;
			}
		}
	}
}
void  fixed_head2(map<char, vector<pair<string, bool>>>*words, char head) {
	if (head < 'a'||head > 'z') {
		cout << "ERROR:input head is not a letter" << endl;
		exit(0);
	}
	if (words->count(head)) {
		for (int i = 0; i < (*words)[head].size(); i++) {
			tmpresult->push_back((*words)[head][i].first);
			result->push_back(*tmpresult);
			(*words)[head][i].second = true;
			used[head - GAP] ++;
			search_h(words, head, i);
			tmpresult->pop_back();
			(*words)[head][i].second = false;
			used[head - GAP] --;
		}
	}
}
void search_h(map<char, vector<pair<string, bool>>>*words, char start, int index) {

	char next = (*words)[start][index].first.at((*words)[start][index].first.size() - 1);
	if (!words->count(next) || used[next - GAP] == (*words)[next].size()) {
		return;
	}
	else {
		for (int i = 0; i < (*words)[next].size(); i++) {
			if (!(*words)[next][i].second) {
				tmpresult->push_back((*words)[next][i].first);
				result->push_back(*tmpresult);
				(*words)[next][i].second = true;
				used[next - GAP]++;
				search_h(words, (*words)[next][i].first.at(0), i);
				tmpresult->pop_back();
				(*words)[next][i].second = false;
				used[next - GAP] --;
			}
			else {
				continue;
			}
		}
	}
}
void  fixed_tail2(map<char, vector<pair<string, bool>>>*words, char tail) {
	if (tail < 'a' || tail > 'z') {
		cout << "ERROR:input tail is not a letter" << endl;
		exit(0);
	}
	char c = 'a';
	for (; c <= 'z'; c++) {
		if (words->count(c)) {
			for (int i = 0; i < (*words)[c].size(); i++) {
				tmpresult->push_back((*words)[c][i].first);
				if (tmpresult->back().at(tmpresult->back().size() - 1) == tail) {
					result->push_back(*tmpresult);
				}
				(*words)[c][i].second = true;
				used[c - GAP] ++;
				search_t(words, c, i, tail);
				tmpresult->pop_back();
				(*words)[c][i].second = false;
				used[c - GAP] --;
			}
		}
	}
}
void search_t(map<char, vector<pair<string, bool>>>*words, char start, int index,char tail) {

	char next = (*words)[start][index].first.at((*words)[start][index].first.size() - 1);
	if (!words->count(next) || used[next - GAP] == (*words)[next].size()) {
		return;
	}
	else {
		for (int i = 0; i < (*words)[next].size(); i++) {
			if (!(*words)[next][i].second) {
				tmpresult->push_back((*words)[next][i].first);
				if (tmpresult->back().at(tmpresult->back().size() - 1) == tail) {
					result->push_back(*tmpresult);
				}
				(*words)[next][i].second = true;
				used[next - GAP]++;
				search_t(words, (*words)[next][i].first.at(0), i, tail);
				tmpresult->pop_back();
				(*words)[next][i].second = false;
				used[next - GAP] --;
			}
			else {
				continue;
			}
		}
	}
}
void binary_w_x(map<char, vector<pair<string, bool>>>*words, char type, char head_tail, int n) {
	vector<vector<string>>* tmpres = new vector<vector<string>>();
	if (type == 't') {
		fixed_tail2(words, head_tail);
	}
	else if (type == 'h') {
		fixed_head2(words, head_tail);
	}
	else if (type == 'n') {
		fixed_num2(words, n);
	}
	else {
		cout << "EORROR:invaild combination of choices" << endl;
		exit(0);

	}
	if (result->size() == 0) {
		return;
	}
	tmpres->push_back((*result)[0]);
	for (auto &worldlist : *result) {
		if (worldlist.size() > (*tmpres)[0].size()) {
			tmpres->clear();
			tmpres->push_back(worldlist);
		}
		else if ((*tmpres)[0].size() == worldlist.size()&&worldlist!=(*result)[0]) {
			tmpres->push_back(worldlist);
		}
	}
	(*result) = (*tmpres);
}
void binary_c_x(map<char, vector<pair<string, bool>>>*words, char type, char head_tail, int n) {
	vector<vector<string>>* tmpres = new vector<vector<string>>();
	if (type == 't') {
		fixed_tail2(words, head_tail);
	}
	else if (type == 'h') {
		fixed_head2(words, head_tail);
	}
	else if (type == 'n') {
		fixed_num2(words, n);
	}
	else {
		cout << "EORROR:invaild combination of choices" << endl	;
		exit(0);

	}
	if (result->size() == 0) {
		return;
	}
	tmpres->push_back((*result)[0]);
	for (auto &worldlist : *result) {
		int worldlist_count = letter_count(worldlist);
		int tmpres_count = letter_count((*tmpres)[0]);
		if (worldlist_count > tmpres_count) {
			tmpres->clear();
			tmpres->push_back(worldlist);
		}
		else if (worldlist_count == tmpres_count && worldlist != (*result)[0]) {
			tmpres->push_back(worldlist);
		}
	}
	(*result) = (*tmpres);
}
void binary_n_x(map<char, vector<pair<string, bool>>>*words, char type, char head_tail, int n) {
	vector<vector<string>>* tmpres = new vector<vector<string>>();
	if (type == 't') {
		fixed_tail2(words, head_tail);
	}
	else if (type == 'h') {
		fixed_head2(words, head_tail);
	}
	else {
		cout << "EORROR:invaild combination of choices" << endl;
		exit(0);

	}
	if (result->size() == 0) {
		return;
	}
	for (auto &worldlist : *result) {
		if (worldlist.size() == n) {
			tmpres->push_back(worldlist);
		}
	}
	(*result) = (*tmpres);
}
void binary_t_h(map<char, vector<pair<string, bool>>>*words, char head, char tail) {
	vector<vector<string>>* tmpres = new vector<vector<string>>();
	fixed_head2(words, head);
	if (result->size() == 0) {
		return;
	}
	for (auto &worldlist : *result) {
		if (worldlist.back().at(worldlist.back().size() - 1) == tail) {
			tmpres->push_back(worldlist);
		}
	}
	(*result) = (*tmpres);
}
void triple_w_x1_x2(map<char, vector<pair<string, bool>>>*words, char type1, char type2, char head, char tail, int n) {
	vector<vector<string>>* tmpres = new vector<vector<string>>();
	if ((type1 == 't'&& type2 == 'h')|| (type1 == 'h'&& type2 == 't')) {
		binary_t_h(words, head, tail);
	}
	else if ((type1 == 't'&& type2 == 'n') || (type1 == 'n'&& type2 == 't')) {
		binary_n_x(words, 't', tail, n);
	}
	else if ((type1 == 'h'&& type2 == 'n') || (type1 == 'n'&& type2 == 'h')) {
		binary_n_x(words, 'h', head, n);
	}
	else {
		cout << "EORROR:invaild combination of choices" << endl;
		exit(0);

	}
	if (result->size() == 0) {
		return;
	}
	tmpres->push_back((*result)[0]);
	for (auto &worldlist : *result) {
		if (worldlist.size() > (*tmpres)[0].size()) {
			tmpres->clear();
			tmpres->push_back(worldlist);
		}
		else if ((*tmpres)[0].size() == worldlist.size() && worldlist != (*result)[0]) {
			tmpres->push_back(worldlist);
		}
	}
	(*result) = (*tmpres);
}
void triple_c_x1_x2(map<char, vector<pair<string, bool>>>*words, char type1, char type2, char head, char tail, int n) {
	vector<vector<string>>* tmpres = new vector<vector<string>>();
	if ((type1 == 't'&& type2 == 'h') || (type1 == 'h'&& type2 == 't')) {
		binary_t_h(words, head, tail);
	}
	else if ((type1 == 't'&& type2 == 'n') || (type1 == 'n'&& type2 == 't')) {
		binary_n_x(words, 't', tail, n);
	}
	else if ((type1 == 'h'&& type2 == 'n') || (type1 == 'n'&& type2 == 'h')) {
		binary_n_x(words, 'h', head, n);
	}
	else {
		cout << "EORROR:invaild combination of choices" << endl;
		exit(0);

	}
	if (result->size() == 0) {
		return;
	}
	tmpres->push_back((*result)[0]);
	for (auto &worldlist : *result) {
		int worldlist_count = letter_count(worldlist);
		int tmpres_count = letter_count((*tmpres)[0]);
		if (worldlist_count > tmpres_count) {
			tmpres->clear();
			tmpres->push_back(worldlist);
		}
		else if (worldlist_count == tmpres_count && worldlist != (*result)[0]) {
			tmpres->push_back(worldlist);
		}
	}
	(*result) = (*tmpres);
}
void triple_h_t_n(map<char, vector<pair<string, bool>>>*words, char head, char tail, int n) {
	vector<vector<string>>* tmpres = new vector<vector<string>>();
	binary_t_h(words,head,tail);
	if (result->size() == 0) {
		return;
	}
	for (auto &worldlist : *result) {
		if (worldlist.size() == n) {
			tmpres->push_back(worldlist);
		}
	}
	(*result) = (*tmpres);
}
void quadruple_c_h_t_n(map<char, vector<pair<string, bool>>>*words, char head, char tail, int n) {
	vector<vector<string>>* tmpres = new vector<vector<string>>();
	triple_h_t_n(words, head, tail, n);
	if (result->size() == 0) {
		return;
	}
	tmpres->push_back((*result)[0]);
	for (auto &worldlist : *result) {
		int worldlist_count = letter_count(worldlist);
		int tmpres_count = letter_count((*tmpres)[0]);
		if (worldlist_count > tmpres_count) {
			tmpres->clear();
			tmpres->push_back(worldlist);
		}
		else if (worldlist_count == tmpres_count && worldlist != (*result)[0]) {
			tmpres->push_back(worldlist);
		}
	}
	(*result) = (*tmpres);

}
void quadruple_w_h_t_n(map<char, vector<pair<string, bool>>>*words, char head, char tail, int n) {
	vector<vector<string>>* tmpres = new vector<vector<string>>();
	triple_h_t_n(words, head, tail, n);
	if (result->size() == 0) {
		return;
	}
	tmpres->push_back((*result)[0]);
	for (auto &worldlist : *result) {
		if (worldlist.size() > (*tmpres)[0].size()) {
			tmpres->clear();
			tmpres->push_back(worldlist);
		}
		else if ((*tmpres)[0].size() == worldlist.size() && worldlist != (*result)[0]) {
			tmpres->push_back(worldlist);
		}
	}
	(*result) = (*tmpres);

}