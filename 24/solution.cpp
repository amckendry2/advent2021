#include <iostream>
#include <string>
#include <deque>
#include <regex>
using namespace std;

int main(){

	bool divStep = false;
	int diff = 0;
	int modAdd = 0;
	int idx = 0;

	deque<int> highInputs(14, 9);
	deque<int> lowInputs(14, 0);
	deque<pair<int, int>> instrStack;

	string line;
	smatch matches;
	regex divRegex{R"(div z (\d+))"};
	regex diffRegex{R"(add x ([-\d]+))"};
	regex addRegex{R"(add y (\d+))"};
	regex endRegex{R"(add z y)"};
		
	while(getline(cin, line)){
		if(regex_search(line, matches, divRegex))
			divStep = matches.str(1) == "26";
		if(regex_search(line, matches, diffRegex))
			diff = stoi(matches.str(1));
		if(regex_search(line, matches, addRegex))
			modAdd = stoi(matches.str(1));
		if(regex_search(line, matches, endRegex)){
			if(divStep){
				auto p = instrStack.front();
				instrStack.pop_front();

				lowInputs[p.first] = max(1, min(9, 1 - (diff + p.second)));
				lowInputs[idx] = max(1, min(9, 1 + diff + p.second));

				highInputs[p.first] = max(1, min(9, 9 - (diff + p.second)));
				highInputs[idx] = max(1, min(9, 9 + diff + p.second));

			} else {
				instrStack.push_front({idx, modAdd});
			}
			idx++;
		}
	}
	
	cout << "Part 1: ";
	for(int h : highInputs){
		cout << h;
	}
	cout << endl;

	cout << "Part 2: ";
	for(int l : lowInputs){
		cout << l;
	}
	cout << endl;	

	return 0;
}
