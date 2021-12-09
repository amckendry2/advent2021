#include <vector>
#include <string>
#include <unordered_set>
#include <iostream>
#include <numeric>
#include <chrono>
using namespace std;
typedef chrono::high_resolution_clock Time;
typedef chrono::milliseconds ms;

//reading input data into vector
vector<int> readData(int& width){
	string line;
	vector<int> data;
	getline(cin, line);
		for(char c : line)
			data.push_back((int)c - 48);
	width = data.size();
	while(getline(cin, line))
		for(char c : line)
			data.push_back((int)c - 48);	
	return data;
}
//==============================

bool isLowPoint(vector<int>& data, int idx, int width){
	int val = data[idx];
	bool left = idx % width == 0 || val < data[idx - 1];
	bool right = idx % width == width - 1 || val < data[idx + 1];
	bool below = idx + width > data.size() || val < data[idx + width];
	bool above = idx - width < 0 || val < data[idx - width];
	return left && right && above && below;						
}

int getBasin(vector<int>& terrain, unordered_set<int>& excl, int idx, int width){
	excl.insert(idx);
	if(terrain[idx] == 9)
		return 0;
	int area = 1;
	if(idx % width != 0 && !excl.contains(idx - 1))
		area += getBasin(terrain, excl, idx - 1, width);
	if(idx % width != width - 1 && !excl.contains(idx + 1))
		area += getBasin(terrain, excl, idx + 1, width);
	if(idx - width > 0 && !excl.contains(idx - width))
		area += getBasin(terrain, excl, idx - width, width);
	if(idx + width < terrain.size() && !excl.contains(idx + width))
		area += getBasin(terrain, excl, idx + width, width);
	return area;
}	

int main(){
	int width;
	vector<int> terrain = readData(width);
	unordered_set<int> excl;
	vector<int> basins;
	for(int i = 0; i < terrain.size(); i++){
		if(terrain[i] != 9 && !excl.contains(i) && isLowPoint(terrain, i, width)){
			basins.push_back(getBasin(terrain, excl, i, width));
		}
	}
	sort(basins.begin(), basins.end());
	cout << accumulate(basins.end() - 3, basins.end(), 1, multiplies<int>()) << endl;	
	return 0;
}
