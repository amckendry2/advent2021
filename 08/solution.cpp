#include <vector>
#include <algorithm>
#include <string>
#include <regex>
#include <sstream>
#include <iostream>
using namespace std;

class NumDecoder{
	public:
		NumDecoder(string data){
			string code;
			stringstream ss{data};
			while(ss >> code){
				for(char c : code){
					charCounts[c]++;
					switch(code.length()){
						case 2:
						case 4:
						case 3:
						case 7:
							knownNumCount[c]++;
							break;
					}
				}
			}
			decoder[findByCount(8, 2)] = 'a';
			decoder[findByCount(6, 2)] = 'b';
			decoder[findByCount(8, 4)] = 'c';
			decoder[findByCount(7, 2)] = 'd';
			decoder[findByCount(4, 1)] = 'e';
			decoder[findByCount(9, 4)] = 'f';
			decoder[findByCount(7, 1)] = 'g';
		}
		
		int decode(string input){
			for(auto it = input.begin(); it != input.end(); it++){
				if(*it != ' ')
					*it = decoder[*it];
			}
			string final = "";
			stringstream ss{input};
			string s;
			while(ss >> s){
				sort(s.begin(), s.end());
				final += numDict[s];
			}
			return stoi(final);
		}

		static map<string, char> numDict;

	private:
		char findByCount(int c, int kc){
			for(auto it = charCounts.begin(); it != charCounts.end(); it++){
				if((*it).second == c && knownNumCount[(*it).first] == kc){
					return (*it).first;	
				}
			}
			return 'x';
		}

		map<char, int> charCounts{
			{'a', 0},
			{'b', 0},
			{'c', 0},
			{'d', 0},
			{'e', 0},
			{'f', 0},
			{'g', 0}
		};

		map<char, int> knownNumCount = charCounts;
		map<char, char> decoder{};
};

map<string, char> NumDecoder::numDict = {
	{"abcefg", '0'},
	{"cf", '1'},
	{"acdeg", '2'},
	{"acdfg", '3'},
	{"bcdf", '4'},
	{"abdfg", '5'},
	{"abdefg", '6'},
	{"acf", '7'},
	{"abcdefg", '8'},
	{"abcdfg", '9'}
};

int main(){
	vector<pair<string, string>> data;
	string line;
	smatch matches;
	regex getPair{R"(^(.*) \| (.*)$)"};
	while(getline(cin, line)){
		regex_search(line, matches, getPair);
		data.push_back(make_pair(matches[1], matches[2]));
	}
	int total = 0;
	for(auto d : data){
		NumDecoder nd{d.first};	
		total += nd.decode(d.second);
	}
	cout << total << endl;
	return 0;
}
