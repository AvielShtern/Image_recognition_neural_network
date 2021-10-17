//
// Created by Aviel Shtern on 14/06/2020.
//

#include "MlpNetwork.h"

#define FOR_FIRST_DENSE 0
#define FOR_SECOND_DENSE 1
#define FOR_THIRD_DENSE 2
#define FOR_FOUR_DENSE 3


MlpNetwork::MlpNetwork(const Matrix *weights, const Matrix *biases) : _layers
{
	Dense(weights[FOR_FIRST_DENSE], biases[FOR_FIRST_DENSE], Relu),
	Dense(weights[FOR_SECOND_DENSE], biases[FOR_SECOND_DENSE], Relu),
	Dense(weights[FOR_THIRD_DENSE], biases[FOR_THIRD_DENSE], Relu),
	Dense(weights[FOR_FOUR_DENSE], biases[FOR_FOUR_DENSE], Softmax)
}
{}


Digit MlpNetwork::operator()(const Matrix &input) const
{

	Matrix tmp;
	tmp = input;

	for (const auto &currDense : _layers)
	{
		tmp = currDense(tmp);
	}
	int idx = 0;
	float max = 0;
	for (int i = 0; i < tmp.getRows(); i++)
	{
		if (tmp[i] > max)
		{
			idx = i;
			max = tmp[i];
		}
	}
	return Digit{(unsigned int) idx, max};
}

