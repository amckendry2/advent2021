#include <string>
#include <fstream>
#include <vector>
#include <iostream>
using namespace std;

void part1(vector<int> vals){
    int lastVal = 0;
    int largerCount = 0;
    for(int val : vals){
	if(lastVal != 0 && val > lastVal)
	    largerCount++;
	lastVal = val;
    }
    cout << largerCount << endl;
}

void part2(vector<int> vals){
    int count = 0;
    for(auto it = vals.begin(); it < vals.end() - 3; it++)
	count += (int)*(it + 3) > *it;
    cout << count << endl;
}

int main(int argc, char* argv[]){
    
    if(argc < 3){
        cout << "please supply args: [1/2] [input data path]" << endl;
        return 1;
    }
    
    int v;
    vector<int> vals;
    ifstream input{argv[2]};
    while(input >> v)
	vals.push_back(v);
    
    if((string)argv[1] == "1")
        part1(vals);
    if((string)argv[1] == "2")
        part2(vals);
    return 0;
}
