#include <vector>
#include <iostream>
using namespace std;

int main(){

	string d;
	vector<int> data;
	while(getline(cin, d, ','))
		data.push_back(stoi(d));

	sort(data.begin(), data.end());
	double half = data.size() / 2;
	int sum = 0;
	for(auto it = data.begin(); it != data.end(); it++)
		if(it <= data.begin() + half - 1)
			sum += data[half - 1] - *it;
		else sum += *it - data[half];
	cout << "part 1: " << sum << endl; 

	int lowest = 0;
	for(int i = data.front(); i <= data.back(); i++){
		int sum = 0;
		for(auto it = data.begin(); it != data.end(); it++){
			int diff = abs(i - *it);
			sum += diff * (diff + 1) / 2;
		}
		lowest = lowest == 0 ? sum : sum < lowest ? sum : lowest;
	}
	cout << "part 2: " << lowest << endl;
	return 0;
}
