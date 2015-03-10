#pragma once
#include <vector>
#include <string>
class Matrix{
public:
	Matrix(int, int);
	~Matrix();
	void fill(float);
	unsigned get_numrows() const;
	unsigned get_numcols() const;
	unsigned size() const;
	Matrix* getMatrixVector();
	float get_pos(unsigned, unsigned) const;
	void set_pos(unsigned, unsigned, float);
	bool is_square();
	Matrix* operator+(const Matrix&);
	Matrix* operator-(const Matrix&);
	Matrix* operator*(const Matrix&);
	Matrix* operator/(const Matrix&);
	Matrix* operator*(float);
	Matrix* operator*(int);
	std::string to_str();
private:
	unsigned d1, d2;
	std::vector <float> m;
};