#include "magic_square.hpp"
#include <iomanip>

// summations_t
summations_t new_summations(uint dimensions) {
	summations_t new_summations;
	new_summations.column = new uint[dimensions];
	new_summations.row = new uint[dimensions];
	for (uint i = 0; i < dimensions; i++) {
		new_summations.column[i] = 0;
		new_summations.row[i] = 0;
	}
	new_summations.diagonal = 0;
	new_summations.other_diagonal = 0;
	return new_summations;
}

// update operations
void update_plus(uint *summation, uint number) {
	*summation += number;
}

void update_minus(uint *summation, uint number) {
	*summation -= number;
}

// Square
Square::Square(uint n, int limit) {
	this->limit = limit;
	this->count = 0;
	this->dimensions = n;
	this->range = n * n;
	this->magic_number = n * (n * n + 1) / 2;
	this->summations = new_summations(n);
	this->used_numbers = new bool[n * n];
	this->initialize_used_numbers();
	this->square = new uint*[n];
	for (uint i = 0; i < n; i++) {
		(this->square)[i] = new uint[n];
	}
	this->initialize_square();
}

Square::~Square() {
	for (uint i = 0; i < this->dimensions; i++) {
		delete[] (this->square)[i];
	}
	delete[] this->square;
	delete[] this->used_numbers;
}

void Square::initialize_used_numbers() {
	for (uint i = 0; i < this->dimensions; i++) {
		this->used_numbers[i] = false;
	}
}

void Square::initialize_square() {
	for (uint i = 0; i < this->dimensions; i++) {
		for (uint j = 0; j < this->dimensions; j++) {
			this->square[i][j] = 0;
		}
	}
}

uint Square::get(uint row, uint column) {
	return this->square[row][column];
}

void Square::set(uint row, uint column, uint value) {
	this->square[row][column] = value;
}

void Square::print_square() {
	for (uint i = 0; i < this->dimensions; i++) {
		for (uint j = 0; j < this->dimensions; j++) {
			cout << setw(4) << this->square[i][j];
		}
		cout << endl;
	}
	cout << endl;
}

bool Square::is_used(uint number) {
	return used_numbers[number];
}

void Square::update_summations(uint row, uint column, uint current_number,
		update_operation update) {
	update(&(summations.row[row]), current_number);
	update(&(summations.column[column]), current_number);
	if (row == column) {
		update(&(summations.diagonal), current_number);
	}
	if ((column + 1) == (this->dimensions - row)) {
		update(&(summations.other_diagonal), current_number);
	}
}

bool Square::validate_excess(uint row, uint column, uint number) {
	if ((summations.row[row] + number) > magic_number) {
		return false;
	}
	if ((summations.column[column] + number) > magic_number) {
		return false;
	}
	if (row == column && (summations.diagonal + number) > magic_number) {
		return false;
	}
	if (column + 1 == row - dimensions
			&& (summations.other_diagonal + number) > magic_number) {
		return false;
	}
	return true;
}

bool Square::validate_magic_number(uint row, uint column, uint number) {
	if ((row + 1) == dimensions
			&& (summations.column[column] + number) != magic_number) {
		return false;
	}
	if ((column + 1) == dimensions
			&& (summations.row[row] + number) != magic_number) {
		return false;
	}
	if ((row + 1) == dimensions && (column + 1) == dimensions
			&& (summations.diagonal + number) != magic_number) {
		return false;
	}
	if ((row + 1) == dimensions && column == 0
			&& (summations.other_diagonal + number) != magic_number) {
		return false;
	}
	return true;
}

bool Square::is_valid(uint row, uint column, uint number) {
	if (this->is_used(number)) {
		return false;
	}

	if (!this->validate_magic_number(row, column, number)) {
		return false;
	}

	if (!this->validate_excess(row, column, number)) {
		return false;
	}

	update_summations(row, column, number, &update_plus);
	return true;
}


void Square::solve() {
	for (uint i = 0; i < this->dimensions; i++) {
		for (uint j = 0; j < this->dimensions; j++) {
			if (this->square[i][j] == 0) {
				for (uint n = 1; n <= this->range; n++) {
					if (this->is_valid(i, j, n)) {
						this->square[i][j] = n;
						this->used_numbers[n] = true;
						this->solve();
						this->square[i][j] = 0;
						this->used_numbers[n] = false;
						this->update_summations(i, j, n, &update_minus);
					}
				}
				return;
			}
		}
	}
	this->print_square();
	count++;
	if (limit == count) {
		exit(0);
	}
	//cout << "Show next? y/n" << endl;
	//char next;
	//cin >> next;
	//if (next != 'y') {
	//	exit(0);
	//}
	//cout << endl;
}
