// ConsoleApplication1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <cstdio>
#include <vector>
#include <string>
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
 * Get value at 0-indexed position TODO: Possibly change to 1-index
 * @param  row 	Row position
 * @param  col 	Column position
 * @return
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
Matrix* operator*(int lhs, const Matrix& rhs){
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
		
		returnString.append(std::to_string(m.at(i)));
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

