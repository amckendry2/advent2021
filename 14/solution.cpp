#include <string>
#include <iostream>
#include <regex>
#include <unordered_map>
using namespace std;

void addRule(unordered_map<string, pair<string, string>>& polymerMap, string combo, string res){
	polymerMap.insert({combo, {combo[0] + res, res + combo[1]}});
}

void addCount(unordered_map<string, long long int>& countMap, string key, long long int num){
	if(countMap[key])
		countMap[key]+= num;
	else countMap[key] = num;
}

long long int mostMinusLeast(const unordered_map<string, long long int>& polymers, string firstLetter, string lastLetter){
	unordered_map<string, long long int> count;
	long long int total = 1;
	for(auto p : polymers){
		total += p.second;
		for(char c : p.first){
			string s{c};
			addCount(count, s, p.second);
		}
	}
	addCount(count, firstLetter, 1);
	addCount(count, lastLetter, 1);
	long long int highest = 0;
	long long int lowest = 0;
	for(auto c : count){
		if(highest == 0 || c.second > highest) highest = c.second;
		if(lowest == 0 || c.second < lowest) lowest = c.second;
	}
	return (highest - lowest) / 2;
}

int main(int argc, char* argv[]){
	if(argc < 2){
		cout << "missing cycles argument" << endl;
		return 0;
	}

	int cycles = stoi(argv[1]);
	unordered_map<string, long long int> polymerState;
	unordered_map<string, long long int> nextPolymerState;
	unordered_map<string, pair<string, string>> polymerMap;

	string line;
	getline(cin, line);

	string firstLetter{line.front()};
	string lastLetter{line.back()};
	for(auto it = line.begin(); it != line.end() - 1; it++){
		string combo{*it};
		combo += *(it + 1);
		addCount(polymerState, combo, 1);
	}
	
	regex ruleRegex{R"(([A-Z]{2}) -> ([A-Z]{1}))"};
	smatch matches;
	while(getline(cin, line))
		if(regex_match(line, matches, ruleRegex))
			addRule(polymerMap, matches.str(1), matches.str(2));

	int totalCycles = cycles;
	while(cycles-- > 0){
		for(auto p : polymerState){
			pair<string, string> toAdd = polymerMap[p.first];
			addCount(nextPolymerState, toAdd.first, p.second);
			addCount(nextPolymerState, toAdd.second, p.second); 
		}
		polymerState = move(nextPolymerState);
	}
	cout << mostMinusLeast(polymerState, firstLetter, lastLetter) << endl;
}
