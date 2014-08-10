// ConsoleApplication1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <cstdio>
#include <vector>
#include <string>
#include "Matrix.h"



Matrix::Matrix(int x, int y){
	d1 = x;
	d2 = y;
	m = std::vector<std::vector<float>>(d1, std::vector<float>(d2, 0));
	//std::vector<std::vector<float>> m(d1, std::vector<float>(d2, 0));
}


void Matrix::fill(float f){
	for (unsigned i = 0; i < m.size(); i++)
	{
		std::vector<float> col = m.at(i);
		for (unsigned j = 0; j < col.size(); j++){
			col.at(j) = f;
		}
		m.at(i) = col;
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
	std::vector<float> column = m.at(row);
	return column.at(col);
}

void Matrix::set_pos(unsigned row, unsigned col, float val){
	if (row >= d1 || col >= d2){
		return;
	}
	std::vector<float> column = m.at(row);
	column.at(col) = val;
	m.at(row) = column;
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
	for (unsigned i = 0; i < d1; i++){
		if (i == 0){
			returnString.append("/");
		}
		else if (i == d1-1) {
			returnString.append("\\");
		}
		else{
			returnString.append("|");
		}
		for (unsigned j = 0; j < d2; j++){
			std::vector<float> col = m.at(i);
			returnString.append(std::to_string(col.at(j)));
			if (j != d2 - 1){
				returnString.append(", ");
			}
		}
		if (i == 0){
			returnString.append("\\");
		} else if (i == d1 - 1) {
			returnString.append("/");
		} else {
			returnString.append("|");
		}

		returnString.append("\n");
	}
	return returnString;
}

int _tmain(int argc, _TCHAR* argv[])
{
	Matrix m1(1, 3);
	m1.fill(5);
	Matrix m2(1, 3);
	m2.fill(2);
	Matrix m3 = m1 + m2;
	printf(m3.to_str().c_str());
	m3 = m1 - m2;
	printf(m3.to_str().c_str());

	Matrix m4(2, 5);
	m4.set_pos(0, 0, 1);
	m4.set_pos(0, 1, 2);
	m4.set_pos(0, 2, 3);
	m4.set_pos(0, 3, 4);
	m4.set_pos(0, 4, 5);
	m4.set_pos(1, 0, 5);
	m4.set_pos(1, 1, 6);
	m4.set_pos(1, 2, 7);
	m4.set_pos(1, 3, 8);
	m4.set_pos(1, 4, 9);
	Matrix m5(5, 2);
	m5.set_pos(0, 0, 1);
	m5.set_pos(0, 1, 2);
	m5.set_pos(1, 0, 2);
	m5.set_pos(1, 1, 3);
	m5.set_pos(2, 0, 3);
	m5.set_pos(2, 1, 4);
	m5.set_pos(3, 0, 4);
	m5.set_pos(3, 1, 5);
	m5.set_pos(4, 0, 5);
	m5.set_pos(4, 1, 6);

	printf(m4.to_str().c_str());
	printf(m5.to_str().c_str());
	m3 = m4 * m5;
	printf(m3.to_str().c_str());
	float f = 0;
	return 0;
}

