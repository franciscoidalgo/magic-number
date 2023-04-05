#ifndef SRC_MAGIC_SQUARE_HPP_
#define SRC_MAGIC_SQUARE_HPP_


#include <iostream>
#include <vector>
#include <stack>

using namespace std;

typedef unsigned int uint;

typedef struct summations {
	uint row;
	uint column;
	uint diagonal;
	uint other_diagonal;
}summations_t;

class Square {
private:
	uint **square;
	uint dimensions;
	uint range;
	uint magic_number;
	vector<uint> used_numbers;

	void initialize_square();
	bool is_used(uint number);
	bool is_valid(uint row, uint column, uint number);
	summations_t calculate_summations(uint row, uint column);
	bool validate_excess(uint row, uint column, uint number, summations_t summations);
	bool validate_magic_number(uint row, uint column, uint number, summations_t summations);

public:
	Square(uint n);
	~Square();
	uint get(uint row, uint column);
	void set(uint row, uint column, uint value);
	void print_square();
	void solve();
};

class MagicSquare {
private:
	uint n;
	vector<Square*> squares;

public:
	MagicSquare(uint n);
	void print_squares();
};


#endif /* SRC_MAGIC_SQUARE_HPP_ */
