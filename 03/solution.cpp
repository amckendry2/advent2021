#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int getOnesAt(vector<int>& data, int idx, int width){
    int count = 0;
    for(auto it = data.begin(); it < data.end(); it++)
	count += (*it >> ((width - 1) - idx)) & 1;
    return count;
};

void bitFilter(vector<int>& vec, int idx, int tgt, int width){
    vec.erase(
	remove_if(
	    vec.begin(),
	    vec.end(),
	    [&tgt, &width, &idx](int v){return tgt ^ ((v >> ((width - 1) - idx)) & 1);}),
	vec.end());
};

int part2Reduce(vector<int> vec, bool inverted, int width){
    for(int i = 0; vec.size() > 1; i++){
	int lastVal = vec.back();
	double half = vec.size() / 2.0;
    	int ones = getOnesAt(vec, i, width);
	int comp = inverted ? ones > half : ones < half;
	int tgt = ones == half ? inverted ? 1 : 0 : comp;
    	bitFilter(vec, i, tgt, width);
    }
    return vec[0];
}

int main(){
   
    string d;
    cin >> d;
    int bitWidth = d.length();
    vector<int> data{stoi(d, 0, 2)};
    while(cin >> d)
	data.push_back(stoi(d, 0, 2));

    int gamma = 0;
    int epsilon = 0;
       
    for(int j = 0; j < bitWidth; j++){
	int val = 1 << ((bitWidth - 1) - j);
        if(getOnesAt(data, j, bitWidth) > data.size() / 2)
    	    gamma += val;
    	else epsilon += val;
    }
    
    cout << "part 1: " << gamma * epsilon << endl;

    int oxygen = part2Reduce(data, false, bitWidth);
    int c02 = part2Reduce(data, true, bitWidth);

    cout << "part 2: " << oxygen * c02 << endl;
}

