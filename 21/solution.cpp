#include <string>
#include <cmath>
#include <regex>
#include <iostream>
using namespace std;

struct State {
	int p1s;
	int p2s;
	int p1pos;
	int p2pos;
	unsigned long long universes;
};

int moveSpaces(int startSpace, int numSpaces){
	return ((startSpace + numSpaces) - 1) % 10 + 1;
}

State makeNewState(State state, int roll, bool p1){
	switch(roll){
		case 3:
		case 9:
			state.universes *= 1;
			break;
		case 4:
		case 8:
			state.universes *= 3;
			break;
		case 5:
		case 7:
			state.universes *= 6;
			break;
		case 6:
			state.universes *= 7;
			break;
	}
	if(p1){
		state.p1pos = moveSpaces(state.p1pos, roll);
		state.p1s += state.p1pos;
	} else {
		state.p2pos = moveSpaces(state.p2pos, roll);
		state.p2s += state.p2pos;
	}
	return state;
}

int main(){
	//exctracting data from cin
	int player1Pos;
	int player2Pos; 

	regex startPosRegex{R"(: ([\d]+))"};
	smatch matches;
	string line;
	getline(cin, line);
	regex_search(line, matches, startPosRegex);
	player1Pos = stoi(matches[1]);
	getline(cin, line);
	regex_search(line, matches, startPosRegex);
	player2Pos = stoi(matches[1]);
	//==========================

	vector<State> states;
	int player1Score = 0;
	int player2Score = 0;

	states.push_back({0, 0, player1Pos, player2Pos, 1});
	unsigned long long p1Won = 0;
	unsigned long long p2Won = 0;
	while(states.size() > 0){
		for(int p1Turn : {1, 0}){
			vector<State> newStates;
			for(auto s : states){
				for(int roll = 3; roll <= 9; roll++){
					State newState = makeNewState(s, roll, p1Turn);
					if(p1Turn && newState.p1s >= 21){
						p1Won += newState.universes;
					} else if(!p1Turn && newState.p2s >= 21){
						p2Won += newState.universes;
					} else {
						newStates.push_back(newState);
					}
				}
			}
			states = move(newStates);
		}
	}

	cout << "Part 2: " << max({p1Won, p2Won}) << endl;
		
	return 0;
}
