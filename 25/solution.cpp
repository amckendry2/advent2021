#include <string>
#include <vector>
#include <iostream>
using namespace std;

int getBelow(int idx, int width, int height){
	return idx + width < width * height ? idx + width : idx % width;
}

int getRight(int idx, int width){
	return idx % width != width - 1 ? idx + 1 : idx - (width - 1); 
}

void printBoard(const vector<char>& board, int width){
	cout << endl << "=======================" << endl;
	for(int i = 0; i < board.size(); i++){
		if(i % width == 0)
			cout << endl;
		cout << board[i];
	}
}

bool doRightMove(vector<char>& board, int width){
	vector<char> cache = board;
	bool didMove = false;
	for(int i = 0; i < board.size(); i++){
		if(board[i] == '>'){
			int next = getRight(i, width);
			if(board[next] == '.'){
				cache[i] = '.';
				cache[next] = '>';
				didMove = true;
			}
		}
	}
	board = move(cache);
	return didMove;
}

bool doDownMove(vector<char>& board, int width, int height){
	vector<char> cache = board;
	bool didMove = false;
	for(int i = 0; i < board.size(); i++){
		if(board[i] == 'v'){
			int next = getBelow(i, width, height);
			if(board[next] == '.'){
				cache[i] = '.';
				cache[next] = 'v';
				didMove = true;
			}
		}
	}
	board = move(cache);
	return didMove;
}

bool doStep(vector<char>& board, int width, int height){
	bool didMove = false;
	didMove = doRightMove(board, width) || didMove;
	didMove = doDownMove(board, width, height) || didMove;
	return didMove;
}

int main(){
	vector<char> cucumbers;
	string line;
	int width;
	getline(cin, line);
	for(char c : line){
		cucumbers.push_back(c);	
	}
	width = cucumbers.size();
	int height = 1;
	while(getline(cin, line)){
		height++;
		for(char c : line){
			cucumbers.push_back(c);
		}
	}
	int steps = 1;
	while(doStep(cucumbers, width, height))
		steps++;
	cout << "steps: " << steps << endl;

	return 0;
}
