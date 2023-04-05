#include <cmath>
#include <string>
#include <iostream>
#include <list>
#include "magic_square.hpp"

using namespace std;

int main(int argc, char **argv) {
	unsigned int number = stoi(argv[1]);
	Square square = Square(number);

	square.solve();

	return 0;
}
