#include <string>
#include <numeric>
#include <vector>
#include <bitset>
#include <sstream>
#include <iostream>

enum Operator { SUM, PRODUCT, MIN, MAX, LIT, GT, LT, EQ };

std::string popBits(std::stringstream& ss, int len){
	std::string s(len, '\0');
	ss.read(&s[0], s.size());
	return s;
}

unsigned long long popInt(std::stringstream& ss, int len){
	return stoull(popBits(ss, len), nullptr, 2);
}

unsigned long long readLiteral(std::stringstream& ss, int& bitsRead){
	std::string literal;
	while(popInt(ss, 1) == 1){
		literal += popBits(ss, 4);	
		bitsRead += 5;
	}
	bitsRead += 5;
	return std::stoull(literal + popBits(ss, 4), nullptr, 2);
}

unsigned long long readPacket(std::stringstream& ss, int& verTotal, int& bits){
	unsigned long long val;
	std::vector<unsigned long long> operands;
	int myBits = 6;
	int childBits = 0;
	verTotal += popInt(ss, 3); 
	Operator op = static_cast<Operator>(popInt(ss, 3)); 
	if(op == LIT){
		val = readLiteral(ss, myBits);
	} else {
		if(popInt(ss, 1)){
			int numPackets = popInt(ss, 11);
			while(numPackets-- > 0){
				operands.push_back(readPacket(ss, verTotal, childBits));
			}
			myBits += 12;
		} else {
			int packetsLen = popInt(ss, 15);
			while(childBits < packetsLen){
				operands.push_back(readPacket(ss, verTotal, childBits));
			}
			myBits += 16;
		}
	}
	if(op == SUM)
		val = std::accumulate(operands.begin(), operands.end(), (unsigned long long)0);
	if(op == PRODUCT)
		val = std::accumulate(operands.begin(), operands.end(), (unsigned long long)1, std::multiplies<unsigned long long>());
	if(op == MIN)
		val = *std::min_element(operands.begin(), operands.end());
	if(op == MAX)
		val = *std::max_element(operands.begin(), operands.end());
	if(op == GT)
		val = (unsigned long long)(operands[0] > operands[1]);
	if(op == LT)
		val = (unsigned long long)(operands[0] < operands[1]);
	if(op == EQ)
		val = (unsigned long long)(operands[0] == operands[1]);
	bits += myBits + childBits;
	return val;
}

int main(){
	std::stringstream transmission;
	std::string d;
	getline(std::cin, d);
	for(char c : d){
		int intval = (c >= 'A') ? (c - 'A' + 10) : (c - '0');
		transmission << std::bitset<4>(intval);
	}
	int verTotal = 0;
	int totalBits = 0;
	unsigned long long calcTotal = readPacket(transmission, verTotal, totalBits);
	std::cout << "Part1: " << verTotal << std::endl;
	std::cout << "Part2: " << calcTotal << std::endl;
	return 0;
}
