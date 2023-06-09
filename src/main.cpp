#include <cmath>
#include <string>
#include <iostream>
#include <list>
#include "magic_square.hpp"

using namespace std;

int main(int argc, char **argv) {
	unsigned int number = stoi(argv[1]);
	int limit = 0;
	if (argc == 3) {
		limit = stoi(argv[2]);
	}
	Square square = Square(number, limit);

	square.solve();

	return 0;
}
