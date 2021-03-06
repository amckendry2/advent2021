#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <cmath>
using namespace std;

int main(int argc, char* argv[]){
	if(argc < 1)
		return 1;
	int cardWidth = stoi(argv[1]);
	int numPicks = 0;

	vector<int> data;

	string line;
	getline(cin, line);
	stringstream ls{line};
	string d;
	while(getline(ls, d, ','))
		data.push_back(stoi(d));
	numPicks = data.size();

	while(cin >> d)
		data.push_back(stoi(d));

	auto callNum = [](vector<int>:: iterator& it, int num, int size){
		for(int i = 0; i < size; i++){
			if(*(it + i) == num)
				*(it + i) = -1;
		}
	};

	auto processSet = [](vector<int>::iterator& it, int& subTotal, int spacing, int width, bool addVals){
		bool win = true;
		int sum = 0;
		for(int i = 0; i < width; i++){
			int val = *(it + i * spacing);
			if(val != -1){
				if(addVals)
					subTotal += val; 
				win = false;
			}
		}	
		return win;
	};

	vector<int> winnerList;
	int finalTotal = 0;

	int cardArea = pow(cardWidth, 2);	

	for(auto pickIt = data.begin(); pickIt < data.begin() + numPicks; pickIt++){
		
		auto cardIt = data.begin() + numPicks;

		while(find(winnerList.begin(), winnerList.end(), cardIt - data.begin()) != winnerList.end())
			cardIt += cardArea;

		if(cardIt == data.end()){
			cout << finalTotal << endl;
			return 0;
		}

		for(; cardIt < data.end(); cardIt += cardArea){
			
			if(find(winnerList.begin(), winnerList.end(), cardIt - data.begin()) != winnerList.end())
				continue;

			callNum(cardIt, *pickIt, cardArea);

			int cardTotal = 0;
			bool cardWon = false;

			for(int i = 0; i < 5; i++){
				auto rowStart = cardIt + i * cardWidth;
				auto colStart = cardIt + i;
				cardWon = processSet(rowStart, cardTotal, 1, cardWidth, true) || cardWon; //check rows for wins and add vals
				cardWon = processSet(colStart, cardTotal, cardWidth, cardWidth, false) || cardWon; //check cols for wins and don't add vals
			}

			if(cardWon){
				finalTotal = cardTotal * (*pickIt);
				winnerList.push_back(cardIt - data.begin());
			}
		}
	}
	return 0;
}
