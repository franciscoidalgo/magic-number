#ifndef SRC_MAGIC_SQUARE_HPP_
#define SRC_MAGIC_SQUARE_HPP_

#include <iostream>
#include <vector>
#include <stack>

using namespace std;

typedef unsigned int uint;

typedef struct summations {
	uint *row;
	uint *column;
	uint diagonal;
	uint other_diagonal;
} summations_t;

summations_t new_summations();

typedef void (*update_operation)(uint*, uint);

class Square {
private:
	uint **square;
	uint dimensions;
	uint range;
	uint magic_number;
	bool *used_numbers;
	summations_t summations;
	int limit;
	int count;

	void initialize_square();
	void initialize_used_numbers();
	bool is_used(uint number);
	bool is_valid(uint row, uint column, uint number);
	bool validate_excess(uint row, uint column, uint number);
	bool validate_magic_number(uint row, uint column, uint number);
	void update_summations(uint row, uint column, uint number,
			update_operation operation);

public:
	Square(uint n, int limit);
	~Square();
	uint get(uint row, uint column);
	void set(uint row, uint column, uint value);
	void print_square();
	void solve();
};

#endif /* SRC_MAGIC_SQUARE_HPP_ */
