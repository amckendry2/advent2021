#include <vector>
#include <cmath>
#include <iostream>
#include <string>
using namespace std;

struct SDigit {
	int val;
	int depth;
};

typedef vector<SDigit> SNum;

SNum buildNumFromString(string data){
	SNum ret;
	int depth = 0;
	for(int i = 0; i < data.length(); i++){
		if(data[i] == '['){
			depth++;
			ret.push_back({-1, depth});
		}
		if(data[i] == ']'){
			ret.push_back({-1, depth});
			depth--;
		}
		if(isdigit(data[i])){
			string num {data[i]};
			while(isdigit(data[i + 1])){
				i++;
			num += data[i];
			}
			ret.push_back({stoi(num), depth});
		}	
	}
	return ret;
}

void explodeAt(SNum& sn, int idx){
	auto it = sn.begin() + idx;
	auto start = it;
	auto end = it + 4;
	int depth = start -> depth;
	while(it-- != sn.begin()){
		if(it -> val != -1){
			it -> val += (start + 1) -> val;
			break;
		}
	}
	it = end - 1;
	while(it++ != sn.end()){
		if(it -> val != -1){
			it -> val += (start + 2) -> val;
			break;
		}
	}
	sn.insert(sn.erase(start, end),{0, depth - 1});
}

void splitAt(SNum& sn, int idx){
	int depth = sn[idx].depth;
	int lNum = floor(sn[idx].val / 2.0);
	int rNum = ceil(sn[idx].val / 2.0);
	sn.insert(sn.erase(sn.begin() + idx), 
			{{-1, depth + 1},
			{lNum, depth + 1},
			{rNum, depth + 1},
			{-1, depth + 1}});
}

int recursiveMagnitude(SNum& sn, int& idx){
	int leftVal = 0;
	int rightVal = 0;
	if(sn[++idx].val != -1){
		leftVal = sn[idx].val;
	} else {
		leftVal = recursiveMagnitude(sn, idx);
	}
	if(sn[++idx].val != -1){
		rightVal = sn[idx].val;
	} else { 
		rightVal = recursiveMagnitude(sn, idx);
	}
	idx++;
	return 3 * leftVal + 2 * rightVal;
}

int getMagnitude(SNum& sn){
	int idx = 0;
	return recursiveMagnitude(sn, idx);
}

bool reduceNum(SNum& sn){
	for(int i = 0; i < sn.size(); i++){
		if(sn[i].depth > 4){
			explodeAt(sn, i);
			return true;
		}
	}
	for(int j = 0; j < sn.size(); j++){
		if(sn[j].val >= 10){
			splitAt(sn, j);
			return true;
		}
	}
	return false;
}


SNum addSNums(SNum a, SNum b){
	SNum ret{{-1, 1}};
	for(auto sd : a){
		sd.depth++;
		ret.push_back(sd);
	}
	for(auto sd : b){
		sd.depth++;
		ret.push_back(sd);
	}
	ret.push_back({-1, 1});
	while(reduceNum(ret));
	return ret;
}


int main(){		
	vector<SNum> nums;
	string line;
	while(getline(cin, line)){
		nums.push_back(buildNumFromString(line));
	}
	SNum sum {nums[0]};
	for(int i = 1; i < nums.size(); i++){
		sum = addSNums(sum, nums[i]);	
	}
	cout << "Part 1: " << getMagnitude(sum) << endl;

	int largestSum = 0;
	for(int i = 0; i < nums.size(); i++){
		for(int j = 0; j < nums.size(); j++){
			if(i != j){
				SNum sum = addSNums(nums[i], nums[j]);
				int mag = getMagnitude(sum);
				if(mag > largestSum){
					largestSum = mag;
				}
			}
		}
	}
	cout << "Part 2: " << largestSum << endl;
	return 0;
}
