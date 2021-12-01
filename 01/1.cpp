#include <string>
#include <fstream>
#include <vector>
#include <iostream>
using namespace std;

void part1(ifstream& input){
    int lastVal = 0;
    int largerCount = 0;
    int val;
    while(input >> val){
	if(lastVal != 0 && val > lastVal)
	    largerCount++;
	lastVal = val;
    }
    cout << largerCount << endl;
}

void part2(ifstream& input){
    int v;
    vector<int> vals;
    while(input >> v)
	vals.push_back(v);
    int count = 0;
    for(auto it = vals.begin(); it < vals.end() - 3; it++)
	count += *(it + 3) > *it ? 1 : 0;
    cout << count << endl;
}

int main(int argc, char* argv[]){
    if(argc < 3){
        cout << "please supply args: [1/2] [input data path]" << endl;
        return 1;
    }
    ifstream input{argv[2]}; 
    if((string)argv[1] == "1")
        part1(input);
    if((string)argv[1] == "2")
        part2(input);
    return 0;
}
