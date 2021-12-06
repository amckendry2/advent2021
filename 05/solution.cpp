#include <vector>
#include <map>
#include <iostream>
#include <regex>
using namespace std;

void addPt(map<int, int>& m, int x, int y, int width){
	int idx = x + y * width;
	if(m[idx])
		m[idx]++;
	else m[idx] = 1;
}

int main(int argc, char* argv[]){
	map<int, int>ventMap;	
	string line;
	smatch matches;
	regex coords{R"(^([0-9]+),([0-9]+) -> ([0-9]+),([0-9]+)$)"};
	while(getline(cin, line)){
		if(regex_search(line, matches, coords)){
			int x1 = stoi(matches[1]);
			int y1 = stoi(matches[2]);
			int x2 = stoi(matches[3]);
			int y2 = stoi(matches[4]);
			addPt(ventMap, x1, y1, 1000);
			while(x1 != x2 || y1 != y2){
				x1 += x2 == x1 ? 0 : x2 > x1 ? 1 : -1;
				y1 += y2 == y1 ? 0 : y2 > y1 ? 1 : -1;
				addPt(ventMap, x1, y1, 1000);
			}
		}
	}
	int overlaps = 0;
	for(auto v : ventMap)
		if(v.second > 1)
			overlaps++;
	cout << overlaps << endl;
}
