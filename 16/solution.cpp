#include <string>
#include <bitset>
#include <sstream>
#include <iostream>

std::string popBits(std::stringstream& ss, int len){
	std::string s(len, '\0');
	ss.read(&s[0], s.size());
	return s;
}

int popInt(std::stringstream& ss, int len){
	return stoi(popBits(ss, len), nullptr, 2);
}

long readLiteral(std::stringstream& ss, int& bitsRead){
	std::string literal;
	while(popInt(ss, 1) == 1){
		literal += popBits(ss, 4);	
		bitsRead += 5;
	}
	bitsRead += 5;
	return std::stol(literal + popBits(ss, 4), nullptr, 2);
}

int readPacket(std::stringstream& ss, int& verTotal){
	verTotal += popInt(ss, 3); 
	int type = popInt(ss, 3); 
	int bitsRead = 6;
	if(type == 4){
		readLiteral(ss, bitsRead);
	} else {
		if(popInt(ss, 1)){
			int numPackets = popInt(ss, 11);
			bitsRead += 12;
			while(numPackets-- > 0){
				bitsRead += readPacket(ss, verTotal);
			}
		} else {
			int packetsLen = popInt(ss, 15);
			bitsRead += 16 + packetsLen;
			while(packetsLen > 0){
				packetsLen -= readPacket(ss, verTotal);
			}
		}
	}
	return bitsRead;
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
	readPacket(transmission, verTotal);
	std::cout << "Part1: " << verTotal << std::endl;
	return 0;
}
