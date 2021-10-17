//
// Created by Aviel Shtern on 14/06/2020.
//
#include "Activation.h"
#include <cmath>

using namespace std;


Activation::Activation(const ActivationType& functionType)
{
	_function = functionType;
}


ActivationType Activation::getActivationType() const
{
	return _function;
}

Matrix Activation::operator()(const Matrix &vector) const
{
	Matrix newVec(vector);

	if (_function == Relu)
	{
		for (int i = 0; i < newVec.getRows() * newVec.getCols(); i++)
		{
			newVec[i] = newVec[i] >= 0 ? newVec[i] : 0;
		}
	}
	else if (_function == Softmax)
	{
		float sum = 0;
		for (int i = 0; i < newVec.getRows() * newVec.getCols(); i++)
		{
			float expt = exp(newVec[i]);
			sum += expt;
			newVec[i] = expt;
		}
		newVec = (1 / sum) * newVec;
	}
	return newVec;
}

