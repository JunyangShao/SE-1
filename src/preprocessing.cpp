//
// Creaed by jxq96 on 2019/3/10.
//
#include <iostream>
#include <vector>
#include <map>
#include <stdio.h>
#include <string>
#include <fstream>
#define SOURCE_PATH "./test.txt"
using namespace std;
map<char, vector<string>*> worldmap;
int preprocess() {
	ifstream ifs(SOURCE_PATH);
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
			if (worldmap.count(c) == 0) {
				auto worldlist = new vector<string>;
				worldlist->push_back(temp);
				worldmap.insert(pair<char, vector<string>*>(c, worldlist));
			}
			else {
				worldmap[c]->push_back(temp);
			}
		}
		temp = ""; //clear temp
	}
	if (temp != "") {
		c = temp.at(0);
		if (worldmap.count(c) == 0) {
			auto worldlist = new vector<string>;
			worldlist->push_back(temp);
			worldmap.insert(pair<char, vector<string>*>(c, worldlist));
		}
		else {
			worldmap[c]->push_back(temp);
		}
	}
	return 0;
}
int main() {
	preprocess();
	for (auto it = worldmap.begin(); it != worldmap.end(); it++) {
		cout << "======" << it->first << "======" << endl;
		for (auto iter : *it->second)
		{
			cout << iter << endl;
		}
	
	}

	for (auto it = worldmap.begin(); it != worldmap.end(); it++) {
		delete it->second;
	}
	getchar();
}
