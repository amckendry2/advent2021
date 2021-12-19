#include <map>
#include <vector>
#include <iostream>
using namespace std;

typedef vector<double> Vec;
typedef vector<Vec> Mat;

Vec operator*(const Mat& m, const Vec& v){
	int mSz = m.size();
	int vSz = v.size();
	Vec ret(mSz);
	for(int i = 0; i < mSz; i++){
		ret[i] = 0.0;
		for(int j = 0; j < vSz; j++){
			ret[i] += m[i][j]*v[j];
		}
	}
	return ret;
}

int main(){
	Mat m {
		{1, 0, 0, 0}, {0, 1, 0, 0}, {0, 0, 1, 0}, {0, 0, 0, 1}
		{1, 0, 0, 0}, {0, 1, 0, 0}, {0, 0, 1, 0}, {0, 0, 0, 1}
		{1, 0, 0, 0}, {0, 1, 0, 0}, {0, 0, 1, 0}, {0, 0, 0, 1}
		{1, 0, 0, 0}, {0, 1, 0, 0}, {0, 0, 1, 0}, {0, 0, 0, 1}
		{1, 0, 0, 0}, {0, 1, 0, 0}, {0, 0, 1, 0}, {0, 0, 0, 1}
		{1, 0, 0, 0}, {0, 1, 0, 0}, {0, 0, 1, 0}, {0, 0, 0, 1}
		{1, 0, 0, 0}, {0, 1, 0, 0}, {0, 0, 1, 0}, {0, 0, 0, 1}
		{1, 0, 0, 0}, {0, 1, 0, 0}, {0, 0, 1, 0}, {0, 0, 0, 1}
		{1, 0, 0, 0}, {0, 1, 0, 0}, {0, 0, 1, 0}, {0, 0, 0, 1}
		{1, 0, 0, 0}, {0, 1, 0, 0}, {0, 0, 1, 0}, {0, 0, 0, 1}
		{1, 0, 0, 0}, {0, 1, 0, 0}, {0, 0, 1, 0}, {0, 0, 0, 1}
	};
	Vec v {10, 20, 30};
	v = m * v;	
	for(auto d : v) cout << d << " ";
	cout << endl;
	return 0;
}

