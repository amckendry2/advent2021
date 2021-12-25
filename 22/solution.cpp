#include <string>
#include <algorithm>
#include <vector>
#include <regex>
#include <iostream>
using namespace std;

struct Cube {
	long x0;
	long x1;
	long y0;
	long y1;
	long z0;
	long z1;
};

struct Instruction {
	Cube cube;
	bool val;
};

bool isMid(long i, long low, long high){
	return i >= low && i <= high;
}

bool isIntersecting(const Cube& a, const Cube& b){
	return !(
		a.x1 < b.x0 || a.x0 > b.x1 ||
		a.y1 < b.y0 || a.y0 > b.y1 ||
		a.z1 < b.z0 || a.z0 > b.z1
	); 
}

Cube getOverlap(const Cube& fc, const Cube& ic){
	return {
		max(fc.x0, ic.x0), min(fc.x1, ic.x1),
		max(fc.y0, ic.y0), min(fc.y1, ic.y1),
		max(fc.z0, ic.z0), min(fc.z1, ic.z1)
	};
}

vector<Cube> fragmentCube(const Cube& fc, const Cube& ic){

	if(!isIntersecting(fc, ic)){
		return {fc};
	}

	if(ic.x0 <= fc.x0 && ic.x1 >= fc.x1 && ic.y0 <= fc.y0 && ic.y1 >= fc.y1 && ic.z0 <= fc.z0 && ic.z1 >= fc.z1)
		return {};

	vector<Cube> fragments;

	long xL = fc.x0;
	long xR = fc.x1;
	long yL = fc.y0;
	long yR = fc.y1;

	bool xIntL = isMid(ic.x0, fc.x0 + 1, fc.x1);
	bool xIntR = isMid(ic.x1, fc.x0, fc.x1 - 1);
	bool yIntL = isMid(ic.y0, fc.y0 + 1, fc.y1);
	bool yIntR = isMid(ic.y1, fc.y0, fc.y1 - 1);
	bool zIntL = isMid(ic.z0, fc.z0 + 1, fc.z1);
	bool zIntR = isMid(ic.z1, fc.z0, fc.z1 - 1);

	if(xIntL){
		fragments.push_back({
			fc.x0, ic.x0 - 1,
			fc.y0, fc.y1,
			fc.z0, fc.z1
		});
		xL = ic.x0;
	}
	if(xIntR){
		fragments.push_back({
			ic.x1 + 1, fc.x1,
			fc.y0, fc.y1,
			fc.z0, fc.z1
		});
		xR = ic.x1;	
	}
	if(yIntL){
		fragments.push_back({
			xL, xR,
			fc.y0, ic.y0 - 1,
			fc.z0, fc.z1	
		});
		yL = ic.y0;
	}
	if(yIntR){
		fragments.push_back({
			xL, xR,
			ic.y1 + 1, fc.y1,
			fc.z0, fc.z1
		});
		yR = ic.y1;
	}
	if(zIntL){
		fragments.push_back({
			xL, xR,
			yL, yR,
			fc.z0, ic.z0 - 1
		});
	}
	if(zIntR){
		fragments.push_back({
			xL, xR,
			yL, yR,
			ic.z1 + 1, fc.z1
		});
	}
	return fragments;
}

long long getAreaTotal(Cube c){
	return ((c.x1 - c.x0) + 1) * ((c.y1 - c.y0) + 1) * ((c.z1 - c.z0) + 1); 
}

long long fragmentAndCount(Cube cube, vector<Cube> intersections){
	long long count = 0;
	vector<Cube> allFragments{cube};
	vector<Cube> afterIntersection;
	for(auto i : intersections){
		for(auto af : allFragments){
			vector<Cube> newFrags = fragmentCube(af, i);
			afterIntersection.insert(afterIntersection.begin(), newFrags.begin(), newFrags.end());
		}
		allFragments = move(afterIntersection);
	}
	for(auto frag : allFragments){
		count += getAreaTotal(frag);
	}
	return count;
}

int main(){
	vector<Instruction> instructions;
	string line;
	smatch matches;
	regex onOffRegex{R"(on)"};
	regex coordRegex{R"(x=([-\d]+)..([-\d]+),y=([-\d]+)..([-\d]+),z=([-\d]+)..([-\d]+))"};
	while(getline(cin, line)){
		bool val = regex_search(line, matches, onOffRegex);
		regex_search(line, matches, coordRegex);
		instructions.push_back({
			stoi(matches[1]), 
			stoi(matches[2]), 
			stoi(matches[3]), 
			stoi(matches[4]), 
			stoi(matches[5]), 
			stoi(matches[6]), 
			val
		});
	}

	long long totalCount = 0;
	vector<Cube> intersections;
	for(int i = 0; i < instructions.size(); i++){
		if(instructions[i].val == false)
			continue;
		Cube a = instructions[i].cube;
		for(int j = i + 1; j < instructions.size(); j++){
			Cube b = instructions[j].cube;
			if(isIntersecting(a, b)){
				intersections.push_back(getOverlap(a, b));
			}
		}
		totalCount += fragmentAndCount(a, intersections);
		intersections.clear();
	}
	cout << "Part 2: " << totalCount << endl;
	return 0;
}
