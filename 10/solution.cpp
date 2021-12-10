#include <string>
#include <stack>
#include <iostream>
#include <vector>
#include <map>
using namespace std;

bool isOpener(char& c){
	return c == '(' || c == '[' || c == '{' || c == '<';
}

map<char, int> part1ScoreTable {
	{')', 3},
	{']', 57},
	{'}', 1197},
	{'>', 25137}
};

map<char, int> part2ScoreTable {
	{'(', 1},
	{'[', 2},
	{'{', 3},
	{'<', 4}
};

map<char, char> pairs {
	{'(', ')'},
	{'[', ']'},
	{'{', '}'},
	{'<', '>'}
};

int main(){
	int part1Score = 0;
	vector<long long int> part2Scores;
	stack<char> pairStack;
	string line;
	while(cin >> line){
		bool corrupted = false;
		for(char c : line){
			if(isOpener(c)){
				pairStack.push(c);
			} else {
				if(pairs[pairStack.top()] == c){
					pairStack.pop();
				} else {
					part1Score += part1ScoreTable[c];
					corrupted = true;
					break;
				}
			}
		}
		if(!corrupted){
			long long int incScore = 0;
			while(!pairStack.empty()){
				incScore *= 5;
				incScore += part2ScoreTable[pairStack.top()];
				pairStack.pop();
			}
			part2Scores.push_back(incScore);
		}
		pairStack = {};
	}
	sort(part2Scores.begin(), part2Scores.end());
	cout << "part 1: " << part1Score << endl;
	cout << "part 2: " << part2Scores[part2Scores.size() / 2] << endl;
	return 0;
}
