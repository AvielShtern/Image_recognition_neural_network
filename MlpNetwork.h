//MlpNetwork.h

#ifndef MLPNETWORK_H
#define MLPNETWORK_H

#include "Matrix.h"
#include "Digit.h"
#include "Dense.h"

#define MLP_SIZE 4

const MatrixDims imgDims = {28, 28};
const MatrixDims weightsDims[] = {{128, 784},
								  {64,  128},
								  {20,  64},
								  {10,  20}};
const MatrixDims biasDims[] = {{128, 1},
							   {64,  1},
							   {20,  1},
							   {10,  1}};

/**
 * @class MlpNetwork
 */
class MlpNetwork
{
private:

	Dense _layers[MLP_SIZE];
public:

	/**
	 * Accepts 2 arrays, size 4 each. one for weights and one for biases. constructs the network
	 * @param weights
	 * @param biases
	 */
	MlpNetwork(const Matrix weights[], const Matrix biases[]);

	/**
	 * Applies the entire network on input returns digit struct
	 * @param input
	 * @return digit struct
	 */
	Digit operator()(const Matrix &input) const;

};

#endif // MLPNETWORK_H
