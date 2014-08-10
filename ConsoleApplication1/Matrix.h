#pragma once
#include <vector>
#include <string>
class Matrix{
	unsigned d1, d2;
	std::vector < std::vector<float>> m;
public:
	Matrix(int, int);
	void fill(float);
	unsigned get_numrows() const;
	unsigned get_numcols() const;
	float get_pos(unsigned, unsigned) const;
	void set_pos(unsigned, unsigned, float);
	/*Matrix dotProduct(const Matrix&);
	Matrix crossProduct(const Matrix&);*/
	Matrix operator+(const Matrix&);
	Matrix operator-(const Matrix&);
	Matrix operator*(const Matrix&);
	Matrix operator/(const Matrix&);
	std::string to_str();
};