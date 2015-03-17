// ConsoleApplication1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <cstdio>
#include <vector>
#include <string>
#include <sstream>
#include "Matrix.h"

/**
 * Construct Matrix of given size
 */
Matrix::Matrix(int x, int y){
	d1 = x; //rows
	d2 = y; //columns
	m = std::vector<float>(d1*d2, 0);
}

Matrix::~Matrix(){
}

Matrix* Matrix::clone(){
	Matrix* ret_matrix = new Matrix(d1, d2);
	ret_matrix->m = this->m;
	return ret_matrix;
}

void Matrix::identity_fill(){
	if (this->get_numcols() != this->get_numrows()){
		return;
	}
	this->fill(0);
	for (size_t i = 0; i < m.size(); i + (size_t)d1 + 1){
		this->m[i] = 1;
	}
}

Matrix* Matrix::augment_matrix(){
	Matrix* augmented_matrix = new Matrix(d1, d2*2);
	augmented_matrix->fill(0);
	for (int i = 0; i < this->get_numrows(); i++){
		for (int j = 0; j < this->get_numcols(); j++){
			augmented_matrix->set_pos(i, j, this->get_pos(i, j));
		}
		augmented_matrix->set_pos(i, i + this->get_numrows(), 1);
		
	}

	//printf("augmented matrix is:\n%s", augmented_matrix->to_str().c_str());
	return augmented_matrix;
}

Matrix* Matrix::split_inverse(Matrix* old){
	Matrix* inverse_matrix = new Matrix(old->get_numrows(), old->get_numcols() / 2);
	unsigned numcols = old->get_numcols()/2;
	for (int i = 0; i < old->get_numrows(); i++){
		for (int j = 0; j < numcols; j++){
			inverse_matrix->set_pos(i, j, old->get_pos(i, j+numcols));
		}

	}
	delete old;
	return inverse_matrix;
}

/**
 * Fill matrix with given float version
 * @param f Value to fill
 */
void Matrix::fill(float f){
	for (unsigned i = 0; i < m.size(); i++){
		m.at(i) = f;
	}
}

/**
 * Get number of rows
 * @return unsigned int size
 */
unsigned Matrix::get_numrows() const{
	return d1;
}

/**
 * Get number of columns
 * @return unsigned int
 */
unsigned Matrix::get_numcols() const{
	return d2;
}

/**
 * Is matrix square
 * @return bool
 */
bool Matrix::is_square(){
	return d1 == d2;
}

Matrix* Matrix::transpose(){
	if (!this->is_square()){
		return NULL;
	}

	Matrix* transposed = new Matrix(this->get_numrows(), this->get_numcols());

	for (size_t i = 0; i < this->get_numcols(); i++)
	{
		for (size_t j = 0; j < this->get_numrows(); j++)
		{
			transposed->set_pos(i, j, this->get_pos(j, i));
		}
	}
	return transposed;
}

Matrix* Matrix::get_det_submatrix(unsigned index){
	Matrix* new_matrix = new Matrix(this->get_numrows() - 1, this->get_numcols() - 1);
	new_matrix->m.resize(0);
	for (size_t i = this->get_numcols(); i < this->m.size(); i++) {
		if (i % this->get_numcols() != index) {
			new_matrix->m.push_back(this->m.at(i));
		}
	}
	return new_matrix;
}

float Matrix::get_det(){
	float rval = 0;
	if (!this->is_square()){
		return NULL;
	}
	if (this->get_numcols() == 2){
		float ad = this->get_pos(0, 0) * this->get_pos(1, 1);
		float bc = this->get_pos(0, 1) * this->get_pos(1, 0);
		return ad - bc;
	} else {
		for (size_t i = 0; i < this->get_numcols(); i++) {

			Matrix* new_matrix = this->get_det_submatrix(i);
			if (i % 2 == 0){
				rval += this->get_pos(0, i) * new_matrix->get_det();
			} else {
				rval -= this->get_pos(0, i) * new_matrix->get_det();
			}
		}
	}

	return rval;
}

unsigned Matrix::largest_col_in_row(unsigned row){
	unsigned rval = 0;
	float max = this->get_pos(row, 0);
	for (size_t i = 1; i < this->get_numcols(); i++){
		float val2 = this->get_pos(row, i);
		if (val2 > max) {
			max = val2;
			rval = i;
		}
		
	}
	return rval;
}

void Matrix::swap_rows(unsigned row1, unsigned row2){
	printf("CHANGE PLACES: %d, %d\n", row1, row2);
	float v1;
	for (size_t i = 0; i < this->get_numcols(); i++){
		v1 = this->get_pos(row1, i);
		this->set_pos(row1, i, this->get_pos(row2, i));
		this->set_pos(row2, i, v1);
	}
}

//from_row and to_row are indices!
void Matrix::add_rows(unsigned from_row, unsigned to_row, float amount){
	for (size_t i = 0; i < this->get_numcols(); i++){
		float result = amount * this->get_pos(from_row, i);
		result += this->get_pos(to_row, i);
		//printf("result %f\n", result);
		this->set_pos(to_row, i, result);
	}
	printf("Add rows: %s", this->to_str().c_str());
}

void Matrix::reduce_row(unsigned row_index){
	float dividend = this->get_pos(row_index, row_index);
	printf("Dividend %f\n", dividend);
	for (size_t i = 0; i < this->get_numcols(); i++){
		float result = this->get_pos(row_index, i);
		result /= dividend;
		this->set_pos(row_index, i, result);
	}
	printf("Reduce: %s", this->to_str().c_str());

}

float Matrix::solve_for_zero(float x, float y){
	y *= -1;
	return y / x;
}

Matrix* Matrix::get_inverse(){
	if (!this->is_square()){
		return NULL;
	}
	if (this->get_det() == 0){
		return NULL;
	}
	Matrix* rval = this->augment_matrix();
	printf("Before: %s", rval->to_str().c_str());
	int numrows = rval->get_numrows();

	
	for (size_t i = 0; i < numrows; i++){
		//reduce row
		rval->reduce_row(i);
		for (size_t j = 0; j < numrows; j++){
			//zero out following rows
			if (i != j){
				float x = rval->get_pos(i, i);
				printf("x %f\n", x);
				float y = rval->get_pos(j, i);
				printf("y %f\n", y);
				rval->add_rows(i, (j) % numrows, Matrix::solve_for_zero(x, y));
			}
		}
	}
	return Matrix::split_inverse(rval);
}

/**
 * Get value at 0-indexed position TODO: Possibly change to 1-index
 * @param  row 	Row position
 * @param  col 	Column position
 * @return float
 */
float Matrix::get_pos(unsigned row, unsigned col) const{
	if (row >= d1 || col >= d2){
		return 0;
	}
	return m.at(row*d2+col);
}

/**
 * Set float value to given 0-indexed position
 * @param row 	Row position
 * @param col 	Column position
 * @param val 	Float value to be 
 */
void Matrix::set_pos(unsigned row, unsigned col, float val){
	if (row >= d1 || col >= d2){
		return;
	}
	m.at( (row * d2) + col) = val;
}

/**
 * Add each element of the matrix. If matrix dimensions do not match, return empty
 * matrix with equivalent size of left-hand side of operation.
 */
Matrix* Matrix::operator+(const Matrix& rhs){
	Matrix* result = new Matrix(d1,d2);
	if (d1 == rhs.d1 && d2 == rhs.d2){
		for (unsigned i = 0; i < d1; i++){
			for (unsigned j = 0; j < d2; j++){
				float resultVal = this->get_pos(i, j) + rhs.get_pos(i, j);
				result->set_pos(i, j, resultVal);
			}
		}
	}
	return result;
}

/**
 * Subtract each element of the matrix. If matrix dimensions do not match, return empty
 * matrix with equivalent size of left-hand side of operation.
 */
Matrix* Matrix::operator-(const Matrix& rhs){
	Matrix* result = new Matrix(d1, d2);
	if (d1 == rhs.d1 && d2 == rhs.d2){
		for (unsigned i = 0; i < d1; i++){
			for (unsigned j = 0; j < d2; j++){
				float resultVal = this->get_pos(i, j) - rhs.get_pos(i, j);
				result->set_pos(i, j, resultVal);
			}
		}
	}
	return result;
}

/**
 * Multiply two matrices. If matrix dimensions do not match, return empty
 * matrix with equivalent size of right-hand side's columns and the left-hand
 * side's rows.
 */
Matrix* Matrix::operator*(const Matrix& rhs){
	Matrix* result = new Matrix(rhs.get_numcols(), this->get_numrows());
	if (this->get_numcols() == rhs.get_numrows()){
		float resultValue = 0;
		unsigned m1Rows = this->get_numrows();
		unsigned m2Cols = rhs.get_numcols();
		unsigned matched = this->get_numcols();
		float finalVal = 0;
		float tmpVal = 0;
		for (unsigned i = 0; i < m1Rows; i++){
			for (unsigned j = 0; j < m2Cols; j++){
				for (unsigned k = 0; k < matched; k++){
					float tmp1 = this->get_pos(i, k);
					float tmp2 = rhs.get_pos(k, j);
					tmpVal = tmp1 * tmp2;
					printf("(%d, %d) * (%d, %d)\n", i, k, k, j);
					finalVal += tmpVal;
				}
				result->set_pos(i, j, finalVal);
				finalVal = 0;
			}
		}
	} else {
		printf("Bad matchup");
	}

	return result;
}

/**
*	Scalar multiplication of a matrix
*/
Matrix* operator*(float lhs, const Matrix& rhs){
	unsigned rows = rhs.get_numrows(), columns = rhs.get_numcols();
	Matrix* result = new Matrix(rows, columns);
	for (unsigned i = 0; i < rows; i++){
		for (unsigned j = 0; j < columns; j++){
			float resultVal = rhs.get_pos(i, j) * lhs;
			result->set_pos(i, j, resultVal);
		}
	}
	return result;

}

/**
 *	Scalar multiplication of a matrix
 */
Matrix* Matrix::operator*(float lhs){
	unsigned rows = this->get_numrows(), columns = this->get_numcols();
	Matrix* result = new Matrix(rows, columns);
	for (unsigned i = 0; i < rows; i++){
		for (unsigned j = 0; j < columns; j++){
			float resultVal = this->get_pos(i, j) * lhs;
			result->set_pos(i, j, resultVal);
		}
	}
	return result;

}
double round(double d)
{
	return floor(d + 0.5);
}
/**
 * Debug friendly version of the current matrix.
 * @return std::string String containing a physically correct version of the matrix
 */
std::string Matrix::to_str() {
	std::string returnString = "";
	returnString.append("\n");
	for (unsigned i = 0; i < m.size(); i++){
		if (i % d2 == 0){
			if (i == 0){
				returnString.append("/");	//Beginning of top row
			} else if (i/d2 == d1 - 1) {
				returnString.append("\\");	//Beginning of bottom row
			} else{
				returnString.append("|");
			}
		}
		std::stringstream ss;
		ss << m.at(i);
		std::string s(ss.str());
		returnString.append(s);
		if ((i % d2) != (d2 - 1)){
			returnString.append(", ");
		}
		else {
			if (i == m.size() - 1) {
				returnString.append("/");  	//Last element
			} else if (i == (d2 - 1)){
				returnString.append("\\");	//End of first row
			} else {
				returnString.append("|");
			}
			returnString.append("\n");
		}

	}
	returnString.append("\n");
	return returnString;
}

