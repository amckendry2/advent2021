#include <map>
#include <set>
#include <string>
#include <regex>
#include <vector>
#include <iostream>
using namespace std;

typedef vector<int> Vec;
typedef vector<Vec> Mat;

//MATRIX STUFF=============================================
Mat getIdentityMat(){
	return {{1, 0, 0, 0}, {0, 1, 0, 0}, {0, 0, 1, 0}, {0, 0, 0, 1}};
}

Mat getTransMat(int x, int y, int z){
	return Mat{{1, 0, 0, x}, {0, 1, 0, y}, {0, 0, 1, z}, {0, 0, 0, 1}};
}

vector<Mat> getRotMat(){
	vector<Mat> ret;
	vector<Mat> primaryRot { 
		{ { 1, 0, 0, 0}, {0, 1, 0, 0}, {0, 0, 1, 0}, {0, 0, 0, 1} },
		{ { 0, 0, 1, 0}, {0, 1, 0, 0}, {-1,0, 0, 0}, {0, 0, 0, 1} },
		{ {-1, 0, 0, 0}, {0, 1, 0, 0}, {0, 0,-1, 0}, {0, 0, 0, 1} },
		{ { 0, 0,-1, 0}, {0, 1, 0, 0}, {1, 0, 0, 0}, {0, 0, 0, 1} },
		{ { 1, 0, 0, 0}, {0, 0, 1, 0}, {0,-1, 0, 0}, {0, 0, 0, 1} },
		{ { 1, 0, 0, 0}, {0, 0,-1, 0}, {0, 1, 0, 0}, {0, 0, 0, 1} }
	};
	for(auto p : primaryRot){
		for(int i = 0; i < 4; i++){
			Vec neg = p[0];
			for(int n = 0; n < 3; n++){
				neg[n] *= -1;
			}
			p[0] = p[1];
			p[1] = neg;
			ret.push_back(p);
		}
	}
	return ret;
}

Mat operator*(const Mat& m0, const Mat& m1){
	return Mat {
		{
			m0[0][0] * m1[0][0] + m0[0][1] * m1[1][0] + m0[0][2] * m1[2][0] + m0[0][3] * m1[3][0],
			m0[0][0] * m1[0][1] + m0[0][1] * m1[1][1] + m0[0][2] * m1[2][1] + m0[0][3] * m1[3][1],
			m0[0][0] * m1[0][2] + m0[0][1] * m1[1][2] + m0[0][2] * m1[2][2] + m0[0][3] * m1[3][2],
			m0[0][0] * m1[0][3] + m0[0][1] * m1[1][3] + m0[0][2] * m1[2][3] + m0[0][3] * m1[3][3]
		},
		{
			m0[1][0] * m1[0][0] + m0[1][1] * m1[1][0] + m0[1][2] * m1[2][0] + m0[1][3] * m1[3][0],
			m0[1][0] * m1[0][1] + m0[1][1] * m1[1][1] + m0[1][2] * m1[2][1] + m0[1][3] * m1[3][1],
			m0[1][0] * m1[0][2] + m0[1][1] * m1[1][2] + m0[1][2] * m1[2][2] + m0[1][3] * m1[3][2],
			m0[1][0] * m1[0][3] + m0[1][1] * m1[1][3] + m0[1][2] * m1[2][3] + m0[1][3] * m1[3][3]
		},
		{
			m0[2][0] * m1[0][0] + m0[2][1] * m1[1][0] + m0[2][2] * m1[2][0] + m0[2][3] * m1[3][0],
			m0[2][0] * m1[0][1] + m0[2][1] * m1[1][1] + m0[2][2] * m1[2][1] + m0[2][3] * m1[3][1],
			m0[2][0] * m1[0][2] + m0[2][1] * m1[1][2] + m0[2][2] * m1[2][2] + m0[2][3] * m1[3][2],
			m0[2][0] * m1[0][3] + m0[2][1] * m1[1][3] + m0[2][2] * m1[2][3] + m0[2][3] * m1[3][3]
		},
		{
			m0[3][0] * m1[0][0] + m0[3][1] * m1[1][0] + m0[3][2] * m1[2][0] + m0[3][3] * m1[3][0],
			m0[3][0] * m1[0][1] + m0[3][1] * m1[1][1] + m0[3][2] * m1[2][1] + m0[3][3] * m1[3][1],
			m0[3][0] * m1[0][2] + m0[3][1] * m1[1][2] + m0[3][2] * m1[2][2] + m0[3][3] * m1[3][2],
			m0[3][0] * m1[0][3] + m0[3][1] * m1[1][3] + m0[3][2] * m1[2][3] + m0[3][3] * m1[3][3]
		},
	};
}

Mat getMatrixFromPts(Vec v0, Vec v1){
	return getTransMat(v0[0] - v1[0], v0[1] - v1[1], v0[2] - v1[2]);
}

Vec operator*(const Vec& vec3, const Mat& m){
	Vec ret(3);
	for(int i = 0; i < 3; i++){
		ret[i] = m[i][3];
		for(int j = 0; j < 3; j++){
			ret[i] += m[i][j]*vec3[j];
		}
	}
	return ret;
}

vector<Vec> transformScanner(vector<Vec> scanner, const Mat& m){
	vector<Vec> ret;
	for(auto v : scanner){
		ret.push_back(v * m);
	}
	return ret;
}
//===============================================================

int compareBeaconsXOnly(vector<Vec> s0, vector<Vec> s1, int xOff){
	int counter = 0;
	int s0Sz = s0.size();
	int s1Sz = s1.size(); 
	for(int i = 0; i < s1Sz; i++){
		for(int j = 0; j < s0Sz; j++){
			if(s0[j][0] == s1[i][0] + xOff){
				counter++;
			}
			if(j - counter > s0Sz - 12)
				continue;
		}
		if(i - counter > s1Sz - 12)
			return 0;
	}
	return counter;
}

int compareBeaconsFull(vector<Vec> s0, vector<Vec> s1){
	int counter = 0;
	int s0Sz = s0.size();
	int s1Sz = s1.size(); 
	for(int i = 0; i < s1Sz; i++){
		for(int j = 0; j < s0Sz; j++){
			if(s0[j] == s1[i]){
				counter++;
			}
			if(j - counter > s0Sz - 12)
				continue;
		}
		if(i - counter > s1Sz - 12)
			return 0;
	}
	return counter;
}


bool checkForOverlap(const vector<Vec>& s0, const vector<Vec>& s1, const vector<Mat>& rotMatrices, Mat& finalMat){
	for(auto rMat : rotMatrices){
		vector<Vec> rs1 = transformScanner(s1, rMat);
		int s0Sz = s0.size();
		int rs1Sz = rs1.size();
		for(int i = 0; i < s0Sz - 11; i++){
			for(int j = 0; j < rs1Sz - 11; j++){
				Vec v0 = s0[i]; 
				Vec v1 = rs1[j];
				int xOff = v0[0] - v1[0];
				if(compareBeaconsXOnly(s0, rs1, xOff) < 12){
					continue;
				}
				Mat tMat = getMatrixFromPts(v0, v1);
				Mat trMat = tMat * rMat;				
				vector<Vec> trs1 = transformScanner(s1, trMat);
				if(compareBeaconsFull(s0, trs1) >= 12){
					finalMat = trMat;
					return true;
				}
			}
		}
	}
	return false;
}

struct CheckedChart {
	map<int, vector<int>> chart;
	void add(int a, int b){
		if(chart.contains(a))
			chart[a].push_back(b);
		else chart.insert({a, vector<int>{b}});
	}
	bool done(int a, int b){
		return chart.contains(a) && count(chart[a].begin(), chart[a].end(), b);
	}
};

int getManhattanDist(Mat& a, Mat& b){
	return abs(a[0][3] - b[0][3]) + abs(a[1][3] - b[1][3]) + abs(a[2][3] - b[2][3]);
}

int main(){

	//get data from cin===========================
	vector<vector<Vec>> scanners;
	string line;
	smatch matches;
	regex emptyRegex{R"(^$)"};
	regex coordRegex{R"(([-\d]+),([-\d]+),([-\d]+))"};
	vector<Vec> s;
	while(getline(cin, line)){
		if(regex_search(line, matches, emptyRegex)){
			scanners.push_back(s);
			s.clear();
		}
		if(regex_search(line, matches, coordRegex)){
			s.push_back({stoi(matches[1]), stoi(matches[2]), stoi(matches[3])});
		}
	}
	scanners.push_back(s);
	//=============================================

	vector<Mat> rotMatrices = getRotMat();
	vector<Vec> globalScannerData = scanners.front();
	vector<int> rotated {0};
	CheckedChart cc;
	map<int, Mat> rotatedMatrices{{0, getIdentityMat()}};
	int checking = 0;
	while(rotated.size() < scanners.size()){

		int source = rotated[checking];
		
		for(int tgt = 0; tgt < scanners.size(); tgt++){

			if(count(rotated.begin(), rotated.end(), tgt) || cc.done(source, tgt)){
				continue;
			}

			cc.add(source, tgt);	

			Mat trMatRef;
			if(checkForOverlap(scanners[source], scanners[tgt], rotMatrices, trMatRef)){
				rotated.insert(rotated.begin() + checking + 1, tgt);
				Mat finalMatrix = rotatedMatrices[source] * trMatRef; 
				rotatedMatrices.insert({tgt, finalMatrix});
				for(auto d : transformScanner(scanners[tgt], finalMatrix)){
					globalScannerData.push_back(d);
				}
				break;
			}
		}
		checking = (checking + 1) % rotated.size(); 
	}

	set<Vec> globalSet{globalScannerData.begin(), globalScannerData.end()};
	
	int highestDistance = 0;
	for(int i = 0; i < rotatedMatrices.size(); i++){
		for(int j = i; j < rotatedMatrices.size(); j++){
			int md = getManhattanDist(rotatedMatrices[i], rotatedMatrices[j]);
			if(md > highestDistance){
				highestDistance = md;
			}
		}
	}
	cout << "Part 1: " << globalSet.size() << endl;
	cout << "Part 2: " << highestDistance << endl;
	return 0;
}

