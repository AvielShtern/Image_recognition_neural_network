//
// Created by Aviel Shtern on 14/06/2020.
//

#include "Dense.h"


Dense::Dense(const Matrix &w, const Matrix &bies, const ActivationType& functionType) : _weights
(w), _bias
(bies), _functionAct(functionType) {}


const Matrix &Dense::getWeights() const
{
	return _weights;
}

const Matrix &Dense::getBias() const
{
	return _bias;
}

const Activation& Dense::getActivation() const
{
	return _functionAct;
}


Matrix Dense::operator()(const Matrix &input) const
{
	Matrix output;
	output = _functionAct((_weights * input) + _bias);
	return output;
}





