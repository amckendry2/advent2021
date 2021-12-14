#include <vector>
#include <string>
#include <sstream>
#include <iostream>
#include <regex>
using namespace std;

void foldPoints(vector<long long int>& dots, int foldPoint, bool horizontal, int width){
	for(size_t i = 0; i < dots.size(); i++){
		if(horizontal){
			int x = dots[i] % width;
			if(x > foldPoint){
				dots[i] -= (x - foldPoint) * 2;
			}
		} else {
			int y = dots[i] / width;
			if(y > foldPoint){
				dots[i] -= (y - foldPoint) * width * 2;
			}
		}
	}
}

void drawDots(const vector<long long int>& dots, int width, int height, int drawWidth, int drawHeight){
	for(int y = 0; y < drawHeight; y++){
		for(int x = 0; x < drawWidth; x++){
			if(find(dots.begin(), dots.end(), x + y * width) == dots.end()){
				cout << ".";
			} else { 
				cout << "#";	
			}
		}
		cout << endl;
	}
}

int main(int argc, char* argv[]){

    regex coordsRegex{R"((\d+),(\d+))"};
    regex foldRegex{R"(fold along ([x,y])=(\d+))"};
    string line;
    smatch matches;

	stringstream cinData;
	cinData << cin.rdbuf();

	int width = 0;
	int height = 0;

	while(getline(cinData, line)){
		if(regex_search(line, matches, coordsRegex)){
			int x = stoi(matches[1]);
			int y = stoi(matches[2]);
			width = x > width ? x : width;
			height = y > height ? y : height;
		}
	}
	
	int drawWidth = width;
	int	drawHeight = height;

    vector<long long int> dots; 

	cinData.clear();
	cinData.seekg(0);

	while(getline(cinData, line)){
		if(regex_search(line, matches, coordsRegex)){
			dots.push_back(stoi(matches[1]) + stoi(matches[2]) * width); 
        } else if(regex_search(line, matches, foldRegex)){
			bool horizontal = matches[1] == 'x';
			foldPoints(dots, stoi(matches[2]), horizontal, width);
			if(horizontal){
				drawWidth /= 2;
			} else { 
				drawHeight /= 2;
			}
        }
	}
	drawDots(dots, width, height, drawWidth, drawHeight);
    return 0;
}
