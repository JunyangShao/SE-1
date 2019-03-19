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
map<char, vector<pair<string, bool>>*> worldmap;
int world_count;
int preprocess() {
	world_count = 0;
	ifstream ifs(SOURCE_PATH);
	if (ifs) {
		cout << "open file success" << endl;
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
			if (worldmap.count(c) == 0) {
				auto worldlist = new vector<pair<string, bool>>;
				pair<string, bool> world(temp, false);
				worldlist->push_back(world);
				worldmap.insert(pair<char, vector<pair<string, bool>>*>(c, worldlist));
				world_count++;
			}
			else {
				pair<string, bool> world(temp, false);
				worldmap[c]->push_back(world);
				world_count++;
			}
		}
		temp = ""; //clear temp
	}
	if (temp != "") {
		c = temp.at(0);
		if (worldmap.count(c) == 0) {
			auto worldlist = new vector<pair<string, bool>>;
			pair<string, bool> world(temp, false);
			worldlist->push_back(world);
			worldmap.insert(pair<char, vector<pair<string, bool>>*>(c, worldlist));
			world_count++;
		}
		else {
			pair<string, bool> world(temp, false);
			worldmap[c]->push_back(world);
		}
	}
	return 0;
}


int main() {
	preprocess();
	/*
	for (auto it = worldmap.begin(); it != worldmap.end(); it++) {
		cout << "======" << it->first << "======" << endl;
		for (auto iter : *it->second)
		{
			cout << iter.first << endl;
		}
	
	}
	*/
	//cout << world_count << endl;
	for (auto it = worldmap.begin(); it != worldmap.end(); it++) {
		delete it->second;
	}
	getchar();
}
