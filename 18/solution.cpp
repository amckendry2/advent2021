#include <tuple>
#include <vector>
#include <cmath>
#include <iostream>
#include <string>
using namespace std;

struct SPair {
	
	bool isLeft;
	bool isTop;
	SPair* left;
	SPair* right;
	SPair* parent;
	bool isLit;
	int litVal;
	
	SPair(){
		isTop = true;
		isLit = false;
		isLeft = true;
	}
	SPair(SPair* p, bool isL){ //create pair
		isTop = false;
		isLeft = isL;
		isLit = false;
		parent = p;
	}
	SPair(int a, SPair* p, bool isL){ //create literal num
		isTop = false;
		isLeft = isL;
		isLit = true;
		litVal = a;
		parent = p;
	}
	void leftLit(int a){ 
		left = new SPair{a, this, true};
	}
	void leftPair(){ 
		left = new SPair{this, true};
	}
	void rightLit(int b){ 
		right = new SPair{b, this, false}; 
	}
	void rightPair(){ 
		right = new SPair{this, false};	
	}

	SPair* findParent(bool lVal, int& depth){
		SPair* ptr = this;
		while(ptr -> isLeft != lVal){
			ptr = ptr -> parent;
			depth--;
			if(ptr -> isTop){
				return nullptr;
			}
		}
		return ptr;
	}

	SPair* findChildLiteral(bool lVal, int& depth){
		SPair* ptr = this;
		while(!ptr -> isLit){
			if(lVal){
				ptr = ptr -> left;
			} else {
				ptr = ptr -> right;
			}
			depth++;
		}
		return ptr;
	}

	SPair* goRight(){
		return parent->right;
	}

	SPair* goLeft(){
		return parent->left;
	}

	void explode(){
		cout << "SPLODE" << endl;
		int depth;
		SPair* lPtr = findParent(false, depth); 
		if(lPtr != nullptr){
			lPtr = lPtr -> goLeft() -> findChildLiteral(false, depth); 
			lPtr -> litVal += left -> litVal;
		}
		
		SPair* rPtr = findParent(true, depth); 
		if(rPtr != nullptr){
			rPtr = rPtr -> goRight() -> findChildLiteral(true, depth);
			rPtr -> litVal += right -> litVal;
		}
		isLit = true;
		litVal = 0;
		delete left;
		delete right;
	}

	void split(){
		isLit = false;
		leftLit(floor(litVal / 2.0));
		rightLit(ceil(litVal / 2.0));
	}

};

SPair buildPairFromString(string data){
	bool leftMode = true;
	SPair top = SPair();
	SPair* current = &top;
	for(int i = 1; i < data.length() - 1; i++){
		if(data[i] == '['){
			if(leftMode){
				current->leftPair();
				current = current->left;
			} else {
				current->rightPair();
				current = current->right;
			}
			leftMode = true;
		}
		if(data[i] == ']'){
			current = current->parent;
		}
		if(data[i] == ','){
			leftMode = false;
		}
		if(isdigit(data[i])){
			string num {data[i]};
			while(isdigit(data[i + 1])){
				i++;
				num += data[i];
			}
			if(leftMode){
				current->leftLit(stoi(num));
			} else {
				current->rightLit(stoi(num));
			}
		}	
	}
	return top;
}

bool iterateLeftToRight(SPair*& ptr, int& depth, string& outString){
	int depthChange = 0;
	if(!ptr -> isLit){
		ptr = ptr -> findChildLiteral(true, depthChange);		
		for(int i = 0; i < depthChange; i++){
			outString += "[";
		}
		outString += to_string(ptr -> litVal);
	} else if(ptr -> isLit && ptr -> isLeft){
		ptr = ptr -> goRight();
		outString += ",";
	} else {
		outString += to_string(ptr -> litVal);
		ptr = ptr -> findParent(true, depthChange);
		for(int i = depthChange; i < 0; i++){
			outString += "]";
		}
		if(ptr == nullptr){
			return false;
		}
		ptr = ptr -> goRight();
		outString += ",";
	}

	depth += depthChange;

	return true;
}

void doExplosions(SPair& sp){
	cout << "doin explosions" << endl;
	SPair* ptr = &sp;
	int depth = 0;
	string outString;
	while(iterateLeftToRight(ptr, depth, outString)){
		if(depth > 4){
			ptr -> parent -> explode();
			ptr = &sp;
			depth = 0;
			outString = "";
			continue;	
		}
	}
	cout << "after expl: " << outString << endl;
}

void doSplits(SPair& sp){
	cout << "doin splits" << endl;
	SPair* ptr = &sp;
	int depth = 0;
	string outString;
	while(iterateLeftToRight(ptr, depth, outString)){
		if(ptr -> litVal >= 10){
			ptr -> split();
			ptr = &sp;
			depth = 0;
			outString = "";
			continue;
		}
	}
	cout << "after split: " << outString << endl;
}

string getNewString(SPair& sp){
	cout << "gettin string" << endl;
	SPair* ptr = &sp;
	int depth = 0;
	string outString;
	while(iterateLeftToRight(ptr, depth, outString));
	return outString;
}

string concatPairStrings(string a, string b){
	return "[" + a + "," + b + "]";
}

string addStrings(string a, string b){
	SPair sum = buildPairFromString(concatPairStrings(a, b));
	doExplosions(sum);
	doSplits(sum);
	doExplosions(sum);
	doSplits(sum);
	return getNewString(sum);
}

int main(){		
	vector<string> nums;
	string line;
	while(getline(cin, line)){
		nums.push_back(line);
	}
	cout << addStrings(nums[0], nums[1]) << endl;

	return 0;
}
