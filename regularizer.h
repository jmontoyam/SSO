#ifndef REGULARIZER_H
#define REGULARIZER_H

#include<Eigen/Dense>

namespace SSO
{
template<typename Derived>
class Regularizer
{
public:

template<typename T>
double eval(const Eigen::MatrixBase<T>& Q)
{
	return static_cast<Derived*>(this)->eval(Q);
}

template<typename T>
void proxOperator(const Eigen::MatrixBase<T>& Q,
				  double reg_factor, 
                  Eigen::MatrixBase<T>& prox)
{
	static_cast<Derived*>(this)->proxOperator(Q, reg_factor, prox); 
}

template<typename T>
double evalDuality(const Eigen::MatrixBase<T>& Q)
{
	return static_cast<Derived*>(this)->evalDuality(Q);
}

};


}

#endif
