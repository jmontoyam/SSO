#ifndef LOSS_H
#define LOSS_H

#include<Eigen/Dense>

namespace SSO
{

template<typename Derived>
class Loss
{

public:

double evalFunction() 
{
	return static_cast<Derived*>(this)->evalFunction();
}

template<typename T>
void evalDerivative(Eigen::MatrixBase<T>& derivative) 
{
	static_cast<Derived*>(this)->evalDerivative(derivative);
}

template<typename T>
void evalDerivative_for_duality(Eigen::MatrixBase<T>& derivative) 
{
	static_cast<Derived*>(this)->evalDerivative_for_duality(derivative);
}

template<typename T>
void evalDualityFactor(double lambda, Eigen::MatrixBase<T>& dualityFactor)
{
	static_cast<Derived*>(this)->evalDualityFactor(lambda, dualityFactor);
}

};

}

#endif
