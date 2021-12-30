#include <iostream>
#include <queue>
#include <vector>
#include <map>
#include <unordered_map>
#include <string>
using namespace std;

typedef pair<int, string> fPair;
typedef priority_queue<fPair, vector<fPair>, greater<fPair>> fQueue;

enum Location{HALL, AROOM, BROOM, CROOM, DROOM}; 

struct MoveData {
	string state;
	int cost;
};

struct Room {
	Location loc;
	int col;
	int low;
	int high;
};

struct Piece {
	int cost;
	Location dest;
};

static vector<Room> rooms {
	{HALL, -1, 0, 10},
	{AROOM, 2, 11, 14},
	{BROOM, 4, 15, 18},
	{CROOM, 6, 19, 22},
	{DROOM, 8, 23, 26}
};

static map<char, Piece> pieces {
	{'A', {1, AROOM}},
	{'B', {10, BROOM}},
	{'C', {100, CROOM}},
	{'D', {1000, DROOM}}
};

static string WINSTRING = "...........AAAABBBBCCCCDDDD";

Room getRoom(int idx){
	for(auto r : rooms)
		if(idx >= r.low && idx <= r.high)
			return r; 
	return rooms[0];
}

Room getRoom(Location l){
	for(auto r : rooms){
		if(r.loc == l)
			return r;
	}
	return rooms[0];
}

bool pathClear(int a, int b, string& state){
	int inc = ((b - a) > 0) - ((b - a) < 0);
	while(a != b){
		a += inc;
		if(state[a] != '.'){
			return false;
		}
	}
	return true;
}

int getDist(int a, int b){
	int total = 0;
	int colA = a;
	int colB = b;
	Room roomA = getRoom(a);
	Room roomB = getRoom(b);
	if(roomA.loc == roomB.loc)
		return abs(a - b);
	if(roomA.loc != HALL){
		total += a - roomA.low + 1; 	
		colA = roomA.col;
	}	
	if(roomB.loc != HALL){
		total += b - roomB.low + 1;
		colB = roomB.col;
	}
	return total + abs(colA - colB);
}

vector<MoveData> getMoves(int idx, string& state){
	vector<MoveData> moveData;
	vector<int> moves;
	char type = state[idx];	
	if(type == '.')
		return {};
	int it = idx;
	Room room = getRoom(idx);
	Room dest = getRoom(pieces[type].dest);
	//check if entrance is clear
	if(room.loc != HALL){
		while(--it >= room.low){
			if(state[it] != '.'){
				return {};
			}
		}
	}
	//check if already at destination
	if(room.loc == dest.loc){		
		it = idx;
		while(state[it] == type){
			if(it == room.high)
				return {};				
			it++;
		}
	}
	//get hall moves
	int col = room.col == -1 ? idx : room.col;
	if(room.loc != HALL){
		for(int tgt : {0, 1, 3, 5, 7, 9, 10}){
			if(pathClear(col, tgt, state)){
				moves.push_back(tgt);
			}
		}
	}
	//get room moves
	bool roomReady = true;
	int destIdx = 0;
	for(int i = dest.low; i <= dest.high; i++){
		if(!(state[i] == type || state[i] == '.')){
			roomReady = false;
			break;	
		}
		if(state[i] == '.')
			destIdx = i;
	}
	if(roomReady && pathClear(col, dest.col, state)){
		moves.push_back(destIdx);				
	}

	//get costs & new states	
	for(int m : moves){
		int cost = pieces[type].cost * getDist(idx, m);
		string newState = state;
		newState[m] = state[idx];
		newState[idx] = '.';
		moveData.push_back({newState, cost});
	}
	return moveData;
}

vector<MoveData> getAllMoves(string& state){
	vector<MoveData> allMoves;
	for(int i = 0; i < state.size(); i++){
		vector<MoveData> newMoves = getMoves(i, state);
		allMoves.insert(allMoves.end(), newMoves.begin(), newMoves.end());
	}
	return allMoves;
}

int getStateRating(string& state){
	int total = 0;
	for(int i = 0; i < state.size(); i++){ char type = state[i];
		if(type == '.')
			continue;
		int dist = getDist(i, getRoom(pieces[type].dest).high);
		total += pieces[type].cost * dist;
	}
	return total - 6666;
}

int getBestSolution(string& initState){
	fQueue q;
	unordered_map<string, int> cost;
	unordered_map<string, int> fnum;
	q.push({0, initState});
	cost[initState] = 0;
	fnum[initState] = getStateRating(initState);
	while(q.size() > 0){
		string currentState = q.top().second;
		q.pop();
		if(currentState == WINSTRING){
			return cost[currentState];	
		}
		vector<MoveData> adjStates = getAllMoves(currentState);
		for(auto adj: adjStates){
			int newCost = cost[currentState] + adj.cost;
			if(!cost.count(adj.state) || newCost < cost[adj.state]){
				cost[adj.state] = newCost;
				int newFnum = newCost + getStateRating(adj.state);
				fnum[adj.state] = newFnum;
				q.push({newFnum, adj.state});
			}
		}
	}
	return 0;
}

int main(){
	string initState = "...........DDDBACBCCBABDACA";
	cout << "Part 2: " << getBestSolution(initState) << endl;
	return 0;
}
