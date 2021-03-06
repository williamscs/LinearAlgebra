#pragma once
#include <vector>
#include <string>
class Matrix{
public:
	Matrix(int, int);
	~Matrix();
	Matrix* clone();
	void identity_fill();
	Matrix* augment_matrix();
	static Matrix* split_inverse(Matrix*);
	void fill(float);
	unsigned get_numrows() const;
	unsigned get_numcols() const;
	unsigned size() const;
	Matrix* getMatrixVector();
	float get_pos(unsigned, unsigned) const;
	void set_pos(unsigned, unsigned, float);
	bool is_square();
	Matrix* transpose();
	Matrix* get_det_submatrix(unsigned);
	float get_det();
	unsigned largest_col_in_row(unsigned);
	void Matrix::swap_rows(unsigned, unsigned);
	void Matrix::add_rows(unsigned, unsigned, float);
	void Matrix::reduce_row(unsigned);
	static float Matrix::solve_for_zero(float, float);
	Matrix* Matrix::get_inverse();
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

Matrix* operator*(float, const Matrix&);