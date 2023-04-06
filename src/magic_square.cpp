#include "magic_square.hpp"
#include <iomanip>

//Square
Square::Square(uint n) {
	this->dimensions = n;
	this->range = n * n;
	this->magic_number = n * (n * n + 1) / 2;
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
	for (auto it = begin(this->used_numbers); it != end(this->used_numbers);
			++it) {
		if (*it == number) {
			return true;
		}
	}
	return false;
}

summations_t Square::calculate_summations(uint row, uint column) {
	summations_t summation = { 0, 0, 0, 0 };
	for (uint i = 0; i < dimensions; i++) {
		for (uint j = 0; j < dimensions; j++) {
			uint current_number = square[i][j];
			if (current_number == 0) {
				return summation;
			}
			if (i == row) {
				summation.row += current_number;
			}
			if (j == column) {
				summation.column += current_number;
			}
			if (i == j) {
				summation.diagonal += current_number;
			}
			if ((j + 1) == (this->dimensions - i)) {
				summation.other_diagonal += current_number;
			}
		}
	}
	return summation;
}

bool Square::validate_excess(uint row, uint column, uint number,
		summations_t summations) {
	if ((summations.row + number) > magic_number) {
		return false;
	}
	if ((summations.column + number) > magic_number) {
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

bool Square::validate_magic_number(uint row, uint column, uint number,
		summations_t summations) {
	if ((row + 1) == dimensions
			&& (summations.column + number) != magic_number) {
		return false;
	}
	if ((column + 1) == dimensions
			&& (summations.row + number) != magic_number) {
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

	summations_t summations = this->calculate_summations(row, column);

	if (!this->validate_magic_number(row, column, number, summations)) {
		return false;
	}

	if (!this->validate_excess(row, column, number, summations)) {
		return false;
	}

	return true;
}

void Square::solve() {
	for (uint i = 0; i < this->dimensions; i++) {
		for (uint j = 0; j < this->dimensions; j++) {
			if (this->square[i][j] == 0) {
				for (uint n = 1; n <= this->range; n++) {
					if (this->is_valid(i, j, n)) {
						this->square[i][j] = n;
						this->used_numbers.push_back(n);
						this->solve();
						this->square[i][j] = 0;
						this->used_numbers.pop_back();
					}
				}
				return;
			}
		}
	}
	this->print_square();
	cout << "Show next? y/n" << endl;
	char next;
	cin >> next;
	if (next != 'y') {
		return;
	}
	cout << endl;
}

// MagicSquare

MagicSquare::MagicSquare(uint n) {
	this->n = n;
	this->squares = vector<Square*>();
}

void MagicSquare::print_squares() {
	// vector<Square>::iterator it;
	for (auto it = begin(this->squares); it != end(this->squares); ++it) {
		(*it)->print_square();
	}
}
