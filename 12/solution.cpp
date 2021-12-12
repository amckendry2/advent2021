#include <unordered_map>
#include <string>
#include <vector>
#include <algorithm>
#include <regex>
#include <iostream>
using namespace std;

enum CaveSize { BIG, SMALL };

struct Cave {
	CaveSize size;
	vector<string> connections;
};

bool isUpper(const string& s){
	return all_of(s.begin(), s.end(), [](char c){return isupper(c);});
}

void insertCave(unordered_map<string, Cave>& caves, const string& id, const string& connection){
	auto caveIt = caves.find(id);
	if(caveIt != caves.end()){
		caveIt->second.connections.push_back(connection);
		return;
	}
	CaveSize size = isUpper(id) ? BIG : SMALL;	
	caves.insert({id, {size, {connection}}});
}

int getPaths(unordered_map<string, Cave>& caves, const string& start, vector<string> excl, bool didTwice){
	if(start == "end")
		return 1;
	if(caves[start].size == SMALL){
		if(count(excl.begin(), excl.end(), start)){
			if(didTwice || start == "start"){
				return 0;
			} else { 
				didTwice = true;
			}
		} else {
			excl.push_back(start);
		}
	}
	int paths = 0;
	for(string& conn : caves[start].connections){
		paths += getPaths(caves, conn, excl, didTwice);
	}
	return paths;
}

int main(){
	unordered_map<string, Cave> caves;
	regex caveRegex{R"(([a-zA-Z]+)-([a-zA-z]+))"};	
	string line;	
	smatch matches;
	while(getline(cin, line)){
		if(regex_search(line, matches, caveRegex)){
			insertCave(caves, matches[1], matches[2]);
			insertCave(caves, matches[2], matches[1]);
		}
	}
	cout << "Part 1: " << getPaths(caves, "start", {}, true) << endl;
	cout << "Part 2: " << getPaths(caves, "start", {}, false) << endl;
	return 0;
}
