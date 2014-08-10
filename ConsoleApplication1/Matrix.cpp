// ConsoleApplication1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <cstdio>
#include <vector>
#include <string>
#include "Matrix.h"



Matrix::Matrix(int x, int y){
	d1 = x; //rows
	d2 = y; //columns
	m = std::vector<float>(d1*d2, 0);
}


void Matrix::fill(float f){
	for (unsigned i = 0; i < m.size(); i++)
	{
		m.at(i) = f;
	}
}

unsigned Matrix::get_numrows() const{
	return d1;
}

unsigned Matrix::get_numcols() const{
	return d2;
}

float Matrix::get_pos(unsigned row, unsigned col) const{
	if (row >= d1 || col >= d2){
		return 0;
	}
	return m.at(row*d2+col);
}

void Matrix::set_pos(unsigned row, unsigned col, float val){
	if (row >= d1 || col >= d2){
		return;
	}
	m.at( (row * d2) + col) = val;
}

Matrix Matrix::operator+(const Matrix& other){
	Matrix result(d1,d2);
	if (d1 == other.d1 && d2 == other.d2){
		for (unsigned i = 0; i < d1; i++){
			for (unsigned j = 0; j < d2; j++){
				float resultVal = this->get_pos(i, j) + other.get_pos(i, j);
				result.set_pos(i, j, resultVal);
			}
		}
	} else {
		//Matrix result(d1,d2);
		//probably throw an exception or something
		//return NULL;
	}
	return result;
}

Matrix Matrix::operator-(const Matrix& other){
	Matrix result(d1, d2);
	if (d1 == other.d1 && d2 == other.d2){
		for (unsigned i = 0; i < d1; i++){
			for (unsigned j = 0; j < d2; j++){
				float resultVal = this->get_pos(i, j) - other.get_pos(i, j);
				result.set_pos(i, j, resultVal);
			}
		}
	} else {
		//Matrix result(d1,d2);
		//probably throw an exception or something
		//return NULL;
	}
	return result;
}

Matrix Matrix::operator*(const Matrix& other){
	Matrix result(other.get_numcols(), this->get_numrows());
	if (this->get_numcols() == other.get_numrows()){
		float resultValue = 0;
		unsigned m1Rows = this->get_numrows();
		unsigned m2Cols = other.get_numcols();
		unsigned matched = this->get_numcols();
		float finalVal = 0;
		float tmpVal = 0;
		for (unsigned i = 0; i < m1Rows; i++){
			for (unsigned j = 0; j < m2Cols; j++){
				for (unsigned k = 0; k < matched; k++){
					float tmp1 = this->get_pos(i, k);
					float tmp2 = other.get_pos(k, j);
					tmpVal = tmp1 * tmp2;
					printf("(%d, %d) * (%d, %d)\n", i, k, k, j);
					finalVal += tmpVal;
				}
				result.set_pos(i, j, finalVal);
				finalVal = 0;
			}
		}
	} else {
		printf("Bad matchup");
	}

	return result;
}

std::string Matrix::to_str() {
	std::string returnString = "";
	returnString.append("\n");
	for (unsigned i = 0; i < m.size(); i++){
		if (i % d2 == 0){
			if (i == 0){
				returnString.append("/");
			} else if (i/d2 == d1 - 1) {
				returnString.append("\\");
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
				returnString.append("/");
			} else if (i == (d2 - 1)){
				returnString.append("\\");
			} else {
				returnString.append("|");
			}
			returnString.append("\n");
		}

	}
	returnString.append("\n");
	return returnString;
}

