//Activation.h
#ifndef ACTIVATION_H
#define ACTIVATION_H

#include "Matrix.h"

/**
 * @enum ActivationType
 * @brief Indicator of activation _function.
 */
enum ActivationType
{
	Relu,
	Softmax
};

// Insert Activation class here...

/**
 *@class Activation
 */
class Activation
{
private:
	ActivationType _function;
public:

	/**
	 * Accepts activation type (Relu/Softmax) and defines this instace’s activation accordingly
	 * @param functionType
	 */
	explicit Activation(const ActivationType& functionType);

	/**
	 * @return Returns this activation’s type(Relu/Softmax)
	 */
	ActivationType getActivationType() const;

	/**
	 * Applies activation function on input. (Does not change input)
	 * @param vector
	 * @return a new vector
	 */
	Matrix operator()(const Matrix &vector) const;
};

#endif //ACTIVATION_H


