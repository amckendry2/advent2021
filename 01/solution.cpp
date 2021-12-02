#include <string>
#include <fstream>
#include <vector>
#include <iostream>
using namespace std;

int part1(vector<int>& vals){
    int count = 0;
    for(auto it = vals.begin(); it < vals.end(); it++)
	count += (int)*(it + 1) > *it;
    return count;
}

int part2(vector<int>& vals){
    int count = 0;
    for(auto it = vals.begin(); it < vals.end() - 3; it++)
	count += (int)*(it + 3) > *it;
    return count;
}

int main(int argc, char* argv[]){    
    int v;
    vector<int> vals;
    ifstream input{"input"};
    while(input >> v)
	vals.push_back(v);
    cout << part1(vals) << endl;
    cout << part2(vals) << endl;
    return 0;
}
