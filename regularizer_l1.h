#ifndef REGULARIZER_L1_H
#define REGULARIZER_L1_H

#include<Eigen/Dense>
#include"regularizer.h"
#include<iostream>

namespace SSO
{
class Regularizer_L1: public Regularizer<Regularizer_L1>
{
public:

template<typename T>
double eval(const Eigen::MatrixBase<T>& Q)
{
//	std::cout << "Calling eval() from Regularizer_L1...\n";

	return Q.array().abs().sum();
}

template<typename T>
void proxOperator(const Eigen::MatrixBase<T>& Q,
                  double reg_factor, 
                  Eigen::MatrixBase<T>& prox)
{
//	std::cout << "Calling proxOperator() from Regularizer_L1...\n";

	Eigen::ArrayXXd thresholding = 
			1 - reg_factor * Q.array().abs().inverse(); 
	
	thresholding = (thresholding<0).select(0,thresholding);

	prox = Q.array()*thresholding;
}

template<typename T>
double evalDuality(const Eigen::MatrixBase<T>& Q)
{
//	std::cout << "Calling evalDuality() from Regularizer_L1...\n";
	return Q.template lpNorm<Eigen::Infinity>();
}


};

}

#endif
