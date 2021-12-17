#include <queue>
#include <limits>
#include <vector>
#include <iostream>
#include <chrono>
typedef std::pair<int, int> fPair;
typedef std::priority_queue<fPair, std::vector<fPair>, std::greater<fPair>> fQueue;
typedef std::chrono::high_resolution_clock Clock;
typedef std::chrono::milliseconds ms;

class Terrain {
	public:
		Terrain(std::vector<int>& d, int w, int mult) : 
			data{d}, 
			width{w}, 
			fullWidth{w * mult}
		{
			fullSize = fullWidth * fullWidth;
		}	

		int getByIdx(int idx){
			int x = idx % fullWidth;
			int y = idx / fullWidth;
			int baseVal = data[(x % width) + (y % width) * width];
			int xMod = x / width;
			int yMod = y / width;
			return (((baseVal + xMod + yMod) - 1) % 9) + 1;
		}

		int getFullWidth(){return fullWidth;}
		int getFullSize(){return fullSize;}

		std::vector<int>getAdjacents(int idx){
			std::vector<int> ret; 
			if(idx % fullWidth != fullWidth - 1)
				ret.push_back(idx + 1);
			if((idx + fullWidth) < fullSize)
				ret.push_back(idx + fullWidth);
			if(idx % fullWidth != 0)
				ret.push_back(idx - 1);
			if(idx > fullWidth) 
				ret.push_back(idx - fullWidth);
			return ret;
		}
	private:
		std::vector<int> data;
		int width;
		int fullSize;
		int fullWidth;
};

int distFromEnd(int idx, int tgtIdx, int w){
	return ((tgtIdx % w) - (idx % w)) + ((tgtIdx / w) - (idx / w));
}

int getShortestPathTotal(std::vector<int>& data, int width, int mult){
	Terrain terrain {data, width, mult};
	int fullWidth = terrain.getFullWidth();
	int fullSize = terrain.getFullSize();

	int start = 0;
	int target = fullSize - 1;

	fQueue q;
	q.push({0, 0});

	std::vector<int> dist(fullSize, std::numeric_limits<int>::max()); 	
	std::vector<int> fnum(fullSize, std::numeric_limits<int>::max());
	dist[start] = 0;
	fnum[start] = distFromEnd(start, target, fullWidth);

	while(q.size() > 0){
		int idx = q.top().second;
		q.pop();
		if (idx == target){
			return dist[idx];
		}
		for(int adj : terrain.getAdjacents(idx)){
			int d = dist[idx] + terrain.getByIdx(adj);
			if(d < dist[adj]){
				dist[adj] = d;
				fnum[adj] = d + distFromEnd(adj, target, fullWidth);
				q.push({fnum[adj], adj});
			}
		}
	}
	return 0;
}

int main(){
	std::vector<int> data;
	std::string d;
	std::getline(std::cin, d);
	for(char c : d){
		data.push_back(c - 48);
	}
	int width = data.size();
	while(std::cin >> d){
		for(char c : d){
			data.push_back(c - 48);
		}
	}
	std::cout << "Part 1: " << getShortestPathTotal(data, width, 1) <<  std::endl;
	std::cout << "Part 2: " << getShortestPathTotal(data, width, 5) <<  std::endl;
	std::cout << "Bonus: " << getShortestPathTotal(data, width, 20) << std::endl;
	return 0;
}
