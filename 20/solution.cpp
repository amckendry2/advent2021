#include <vector>
#include <string>
#include <iostream>
using namespace std;

int getAdjacentVals(const vector<int>& vec, int idx, int width){
	if(idx % width == 0 || 
	   idx % width == width - 1 || 
	   idx < width || 
	   idx + width >= vec.size())
	{
		return vec[idx] == 1 ? 512 : 0;
	}
	string sum;
	vector<int> adjacents = {
		{idx - width - 1},{idx - width},{idx - width + 1},
		{idx - 1},{idx},{idx + 1},
		{idx + width - 1},{idx + width},{idx + width + 1}
	};
	for(auto adj : adjacents){
		sum += to_string(vec[adj]);
	}
	return stoi(sum, nullptr, 2);
}

void stringToPixels(vector<int>& vec, string& s, int dataWidth, int padding, int line){
	int fullWidth = dataWidth + padding * 2;
	int startIdx = fullWidth * (padding + line) + padding;	
	for(int i = 0; i < s.size(); i++){
		int vecIdx = i + startIdx;
		if(s[i] == '#')
			vec[vecIdx] = 1;
		else vec[vecIdx] = 0;
	}
}

void enhance(vector<int>& imgData, string enhancement, int width){
	vector<int> dataCache = imgData;
	for(int i = 0; i < imgData.size(); i++){
		int adjVal = getAdjacentVals(dataCache, i, width);
		imgData[i] = enhancement[adjVal] == '#' ? 1 : 0;
	}
}

int main(){
	//getting data from input file========================
	int padding = 60;
	string enhancement;
	int inputWidth;
	string line;
	int lineNum = 0;
	getline(cin, enhancement);
	getline(cin, line);
	getline(cin, line);
	inputWidth = line.length();
	int fullWidth = inputWidth + padding * 2;
	vector<int> imageData(fullWidth * fullWidth, 0);
	stringToPixels(imageData, line, inputWidth, padding, lineNum);
	while(getline(cin, line)){
		lineNum++;
		stringToPixels(imageData, line, inputWidth, padding, lineNum);
	}
	//=====================================================

	int enhanceNum = 50;
	while(enhanceNum-- > 0){
		enhance(imageData, enhancement, fullWidth);	
	}
	cout << count(imageData.begin(), imageData.end(), 1) << endl;
	return 0;
}
