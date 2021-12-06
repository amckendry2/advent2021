#include <vector>
#include <iostream>
using namespace std;

int main(int argc, char* argv[]){
	vector<pair<long long int,int>> fish;
	string d;
	while(getline(cin, d, ','))
		fish.push_back(make_pair(1, stoi(d)));
	for(int count = stoi(argv[1]); count > 0; count--){
		long long int born = 0;
		for(auto it = fish.begin(); it != fish.end(); it++){
			if((*it).second == 0)
				born+=(*it).first;
			(*it).second = (*it).second > 0 ? (*it).second - 1 : 6;
		}
		if(born > 0)
			fish.push_back(make_pair(born, 8));
	}
	long long int total = 0;
	for(auto f : fish){
		total += f.first;
	}
	cout << total << endl;
}
