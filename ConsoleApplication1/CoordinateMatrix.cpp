#include "stdafx.h"
#include "Matrix.h"
#include "CoordinateMatrix.h"

CoordinateMatrix::~CoordinateMatrix(){
}

/**
 * Returns scalar product of two coordinate vectors.
 *   NOTE: Assumes single row.
 * @param  rhs	Matrix of equivalent dimensions to 'this'.
 * @return
 */	
float CoordinateMatrix::dotProduct(const CoordinateMatrix& rhs){
	float retVal = 0;
	for (unsigned i = 0; i < this->get_numcols(); i++){
		retVal += this->get_pos(0, i) * rhs.get_pos(0, i);
	}
	return retVal;
}

/**
 * Returns (pseudo)vector perpendicular to the provided matrices.
 *  Assumes coordinate matrix in three dimensional space.
 * @param  rhs	Right-hand side of cross product
 * @return 			vector perpendicular to the provided matrices
 */
CoordinateMatrix* CoordinateMatrix::crossProduct(const CoordinateMatrix& rhs){
	CoordinateMatrix* retValue = new CoordinateMatrix();
	unsigned size = this->get_numcols();
	float add = 0, subtract = 0;
	for (unsigned i = 0; i < size; i++){
		unsigned pos1 = (i + 1) % size;
		unsigned pos2 = (i + 2) % size;
		add = this->get_pos(0, pos1) * rhs.get_pos(0, pos2);
		subtract = this->get_pos(0, pos2) * rhs.get_pos(0,pos1);
		retValue->set_pos(0, i, add - subtract);
	}

	return retValue;
}

int _tmain(int argc, _TCHAR* argv[]){
	Matrix* m1 = new Matrix(4, 4);
	m1->set_pos(0, 0, 2);
	m1->set_pos(0, 1, -1);
	m1->set_pos(0, 2, 3);
	m1->set_pos(0, 3, 4);
	m1->set_pos(1, 0, -1);
	m1->set_pos(1, 1, 2);
	m1->set_pos(1, 2, -1);
	m1->set_pos(1, 3, 7);
	m1->set_pos(2, 0, 9);
	m1->set_pos(2, 1, -1);
	m1->set_pos(2, 2, 2);
	m1->set_pos(2, 3, -5);
	m1->set_pos(3, 0, -4);
	m1->set_pos(3, 1, -1);
	m1->set_pos(3, 2, 2);
	m1->set_pos(3, 3, -9);
	Matrix* m2 = m1->get_inverse();

	//printf(m1->is_square() ? "is square\n": "not square\n");
	//printf("determinant: %f\n", m1->get_det());
	printf(m2->to_str().c_str());
	getchar();
	
	//Matrix* m1 = new Matrix(1, 3);
	//m1->fill(5);
	//Matrix* m2 = new Matrix(1, 3);
	//m2->fill(2);
	//Matrix* m3 = *m1 + *m2;
	//printf(m3->to_str().c_str());
	//m3 = *m1 - *m2;
	//printf(m3->to_str().c_str());
	//int f = 2;
	//m3 = f * *m1;
	//printf(m3->to_str().c_str());

	//delete m1;
	//delete m2;

	//Matrix m4(2, 5);
	//m4.set_pos(0, 0, 1);
	//m4.set_pos(0, 1, 2);
	//m4.set_pos(0, 2, 3);
	//m4.set_pos(0, 3, 4);
	//m4.set_pos(0, 4, 5);
	//m4.set_pos(1, 0, 5);
	//m4.set_pos(1, 1, 6);
	//m4.set_pos(1, 2, 7);
	//m4.set_pos(1, 3, 8);
	//m4.set_pos(1, 4, 9);
	//Matrix m5(5, 2);
	//m5.set_pos(0, 0, 1);
	//m5.set_pos(0, 1, 2);
	//m5.set_pos(1, 0, 2);
	//m5.set_pos(1, 1, 3);
	//m5.set_pos(2, 0, 3);
	//m5.set_pos(2, 1, 4);
	//m5.set_pos(3, 0, 4);
	//m5.set_pos(3, 1, 5);
	//m5.set_pos(4, 0, 5);
	//m5.set_pos(4, 1, 6);

	//printf(m4.to_str().c_str());
	//printf(m5.to_str().c_str());
	//m3 = m4 * m5;
	//printf((m3->to_str()).c_str());
	//delete m3;

	//CoordinateMatrix* coord_matrix = new CoordinateMatrix();
	//coord_matrix->fill(2);
	//printf(coord_matrix->to_str().c_str());

	//CoordinateMatrix* coord_matrix2 = new CoordinateMatrix();
	//coord_matrix2->fill(5);
	//printf((coord_matrix2->to_str()).c_str());

	//coord_matrix->set_pos(0, 0, 1);
	//coord_matrix->set_pos(0, 1, 2);
	//coord_matrix->set_pos(0, 2, 3);
	//coord_matrix2->set_pos(0, 0, 4);
	//coord_matrix2->set_pos(0, 1, 5);
	//coord_matrix2->set_pos(0, 2, 6);
	//printf("%f\n", coord_matrix->dotProduct(*coord_matrix2));
	//CoordinateMatrix* result;
	//result = coord_matrix->crossProduct(*coord_matrix2);
	//printf((result->to_str()).c_str());
	//delete coord_matrix;
	//delete coord_matrix2;
	//delete result;

	return 0;
}
