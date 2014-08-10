#pragma once
class CoordinateMatrix :
	public Matrix
{
public:
	CoordinateMatrix() : Matrix(1, 3){}
	virtual ~CoordinateMatrix();
};

