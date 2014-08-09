// ConsoleApplication1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <cstdio>
#include <vector>
#include <string>

class Matrix{
	int d1, d2;
	std::vector < std::vector<float>> m;
public:
	Matrix(int, int);
	void fill(float);
	int get_numrows() const;
	int get_numcols() const;
	float get_pos(int, int) const;
	void set_pos(int, int, float);
	/*Matrix dotProduct(const Matrix&);
	Matrix crossProduct(const Matrix&);*/
	Matrix operator+(const Matrix&);
	Matrix operator-(const Matrix&);
	Matrix operator*(const Matrix&);
	Matrix operator/(const Matrix&);
	std::string to_str();
};

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
		//printf(std::to_string(f).c_str());
		m.at(i) = col;
	}
}

int Matrix::get_numrows() const{
	return d1;
}

int Matrix::get_numcols() const{
	return d2;
}

float Matrix::get_pos(int row, int col) const{
	if (row >= d1 || col >= d2){
		return 0;
	}
	std::vector<float> column = m.at(row);
	return column.at(col);
}

void Matrix::set_pos(int row, int col, float val){
	if (row >= d1 || col >= d2){
		return;
	}
	std::vector<float> column = m.at(row);
	column.at(col) = val;
	m.at(row) = column;
}

//Matrix Matrix::dotProduct(const Matrix& other){
//	//if (d1 == other.d2)
//	Matrix result(d1, d2);
//	if (this->get_numcols() == other.get_numrows()){
//		printf("WE CAN DO THIS!");
//	}
//	return result;
//}
//
//Matrix Matrix::crossProduct(const Matrix& other){
//
//	Matrix result(d1, d2);
//	return result;
//}

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
	Matrix result(other.get_numcols(), this->get_numrows);
	if (this->get_numcols() == other.get_numrows()){
		for (unsigned i = 0; i < this->get_numcols(); i++){
			for (unsigned i = 0; i < other.get_numrows(); i++){

			}
		}
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
	float f = 0;
	return 0;
}

