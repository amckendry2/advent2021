#include <numeric>
#include <vector>
#include <string>
#include <iostream>
using namespace std;

//gets adjacent indexes, restricted by grid borders
vector<int> getAdjacents(int idx, int w, int sz){
	vector<int> ret; 
	for(auto x : {idx - 1, idx, idx + 1})
		if(x >= 0 && x / w == idx / w)
			for(auto i : {x - w, x, x + w})
				if(i >= 0 && i < sz && i != idx)
					ret.push_back(i);
	return ret;
}

//execute flash
void flash(vector<int>& data, int idx, int origin, int width, int& flashes){
	flashes++;
	data[idx] = 0;
	for(int a : getAdjacents(idx, width, data.size())){
		//don't add to previously flashed spaces
		if((a > origin || data[a] != 0))
			data[a]++;
		//flash recursively at lower indexes
		if(a < origin && data[a] > 9)
			flash(data, a, origin, width, flashes);
	}
}

int main(){

	//extract data from input
	vector<int> data;
	int width;
	string line;
	char d;

	getline(cin, line);
	for(char c : line)
		data.push_back((int)c - 48);
		
	width = data.size();

	while(cin >> d)
		data.push_back((int)d - 48);
	
	//execute cycles until all octopuses (octopi?) flash at once
	int flashes = 0;
	int cycle = 0;	
	int flashesAfter100 = 0;
	
	while(accumulate(data.begin(), data.end(), 0) != 0){

		cycle++;
		
		for(size_t i = 0; i < data.size(); i++){
			data[i]++;
			if(data[i] > 9)
				flash(data, i, i, width, flashes);
		}

		if(cycle == 100)
			flashesAfter100 = flashes;
	}

	cout << "part 1: " << flashesAfter100 << endl;
	cout << "part 2: " << cycle << endl;
	return 0;
}
