#include <map>
#include <string>
#include <regex>
#include <iostream>

int getXAt(int v, int t){
	if(t > abs(v)) t = abs(v);
	return t * 0.5 * (2 * v + 1 - t);  
}

int main(){
	std::regex coordsRegex{R"(([-\d]+)..([-\d]+), y=([-\d]+)..([-\d]+))"};	
	std::string line;
	std::smatch matches;
	getline(std::cin, line);
	std::regex_search(line, matches, coordsRegex);
	int x0 = std::stoi(matches[1]);
	int x1 = std::stoi(matches[2]);
	int y0 = std::stoi(matches[3]);
	int y1 = std::stoi(matches[4]);
	
	int yFar = std::abs(y0) > std::abs(y1) ? std::abs(y0) : std::abs(y1);
	int maxTime = (yFar) * 2;
	int minXVel = 1;
	while(getXAt(minXVel, maxTime) < x0){
		minXVel++;	
	}
	int count = 0;

	for(int xVel = minXVel; xVel <= x1; xVel++){
		for(int yVel = -yFar; yVel <= yFar; yVel++){
			int x = 0;
			int y = 0;
			for(int t = 1; t <= maxTime; t++){
				x += std::max(xVel - (t - 1), 0);
				y += yVel - (t - 1);
				if(x >= x0 && x <= x1 && y >= y0 && y <= y1){
					count++;	
					break;
				} 
			}
		}
	}
	std::cout << "Part 2: " << count << std::endl;
	return 0;
}
