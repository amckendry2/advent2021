#include <fstream>
#include <vector>
#include <iostream>

using namespace std;

int main(){
    ifstream input{"input"};
    int count1 = 0;
    int count2 = 0;
    int v;
    vector<int> vals;
    while(input >> v)
	vals.push_back(v);
    for(auto it = vals.begin(); it < vals.end(); it++){
	count1 += (int)*(it + 1) > *it;
	if(it < vals.end() - 3)
	    count2 += (int)*(it + 3) > *it;
    }
    cout << count1 << endl;
    cout << count2 << endl;
    return 0;
}
