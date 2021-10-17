//
// Created by Aviel Shtern on 14/06/2020.
//

#ifndef EX4_DENSE_H
#define EX4_DENSE_H

#include "Activation.h"
#include "Matrix.h"

/**
 * @class Dense
 */
class Dense
{
private:
	Matrix _weights;
	Matrix _bias;
	Activation _functionAct;
public:

	/**
	 * Inits a new layer with given parameters
	 * @param w  the weights of this layer
	 * @param bies the bias of this layer
	 * @param functionType the type of activation function
	 */
	Dense(const Matrix &w, const Matrix &bies, const ActivationType& functionType);

	/**
	 * @return Returns the weights of this layer
	 */
	const Matrix &getWeights() const;

	/**
	 * @return Returns the bias of this layer
	 */
	const Matrix &getBias() const;

	/**
	 * @return Returns the activation function of this layer
	 */
	const Activation& getActivation() const;

	/**
	 * Applies the layer on input and returns output matrix
	 * @param input
	 * @return output matrix
	 */
	Matrix operator()(const Matrix &input) const;
};


#endif //EX4_DENSE_H
