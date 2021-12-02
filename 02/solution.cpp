#include <fstream>
#include <map>
#include <complex>
#include <iostream>
#include <iterator>
using namespace std;

typedef istream_iterator<string> iter;
typedef complex<int> comp;

map<string,comp> dirs {
    {"forward", {1,  0} },
    {"up",      {0, -1} },
    {"down",    {0,  1} }
};

int main(){   
    comp pos1 {0, 0};
    comp pos2 {0, 0};
    int aim = 0;
    ifstream input {"input"};
    for(iter it = iter(input); it != iter(); it++){
        comp d = dirs[*it];
	int a = stoi(*++it);
	pos1 += d * a;
	pos2 += comp{ 1, (aim += d.imag() * a)} * a * d.real();
    }
    cout << pos1.real() * pos1.imag() << endl;
    cout << pos2.real() * pos2.imag() << endl;
}
