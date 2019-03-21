//
// Creaed by jxq96 on 2019/3/10.
//
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
vector<vector<string>> mostWords(map<char, vector<pair<string, bool>>>*);
void search(map<char, vector<pair<string, bool>>>*words,char start,int index);
vector<vector<string>> mostLetters(map<char, vector<pair<string, bool>>>* words);
vector<vector<string>> fixed_num(map<char, vector<pair<string, bool>>>* words, int n);
vector<vector<string>> fixed_head_tail(map<char, vector<pair<string, bool>>>* words, char head, char tail);
map<char, vector<pair<string, bool>>>* preprocess(string filename);
int letter_count(vector<string> wolrdlist);
void reset(map<char, vector<pair<string, bool>>>*);
int main(int argc, char* argv[]) {
	// < -- parser command arguments -- >
	const char* optstring = "wch:t:n:";
	bool choice = true; // most word or most character, true:word,false:character
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
				choice = true;
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
				choice = false;
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
	//auto words = preprocess(inputFileName);
	map<char,vector<pair<string,bool>>>* words = new map<char,vector<pair<string,bool>>>;
	(*words)['a'].push_back(make_pair("algebra",false));
	(*words)['a'].push_back(make_pair("apple",false));
	(*words)['z'].push_back(make_pair("zoo",false));
	(*words)['e'].push_back(make_pair("elephant",false));
	(*words)['u'].push_back(make_pair("under",false));
	(*words)['f'].push_back(make_pair("fox",false));
	(*words)['d'].push_back(make_pair("dog",false));
	(*words)['m'].push_back(make_pair("moon",false));
	(*words)['l'].push_back(make_pair("leaf",false));
	(*words)['t'].push_back(make_pair("trick",false));
	(*words)['h'].push_back(make_pair("hello",false));
	(*words)['n'].push_back(make_pair("neer",false));
	(*words)['s'].push_back(make_pair("softw",false));
	(*words)['w'].push_back(make_pair("world",false));
	//vector<vector<string>> result;
	mostWords2(words);
	for (auto &worldlist:*result) {
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

vector<vector<string>> fixed_num(map<char, vector<pair<string, bool>>>* words,int n) {
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
					if (tmpres.size()==n) {
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

vector<vector<string>> fixed_head_tail(map<char, vector<pair<string, bool>>>* words, char head,char tail) {
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
	for (auto word :wolrdlist) {
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

void  mostWords2(map<char, vector<pair<string, bool>>>*words){
	char c = 'a';
	for(;c<='z';c++){
		if(words->count(c)) {
			tmpresult->push_back((*words)[c][0].first);
			(*words)[c][0].second = true;
			used[c-GAP] ++ ;
			search(words,c,0);
			tmpresult->pop_back();
			(*words)[c][0].second = false;
			used[c-GAP] -- ;
		}
	}
}

void search(map<char, vector<pair<string, bool>>>*words,char start,int index){

	char next = (*words)[start][index].first.at((*words)[start][index].first.size()-1);
	if(!words->count(next) || used[next-GAP] == (*words)[next].size()){
		if(result->empty()){
			result->push_back(*tmpresult);
		}
		else{
			if((*result)[0].size() < tmpresult->size()){
				result->clear();
				result->push_back(*tmpresult);
			}
			else if((*result)[0].size() == tmpresult->size()){
				result->push_back(*tmpresult);
			}
		}
		return;
	}
	else{
		for(int i = 0;i<(*words)[next].size();i++){
			if(!(*words)[next][i].second){
				tmpresult->push_back((*words)[next][i].first);
				(*words)[next][i].second = true;
				used[next-GAP]++;
				search(words,(*words)[next][i].first.at(0),i);
				tmpresult->pop_back();
				(*words)[next][i].second = false;
				used[next-GAP] -- ;
			}
			else{
				continue;
			}
		}
	}
}