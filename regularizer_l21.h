#ifndef REGULARIZER_L21
#define REGULARIZER_L21

#include<Eigen/Dense>
#include"regularizer.h"

namespace SSO
{

class Regularizer_L21: public Regularizer<Regularizer_L21>
{
public:

template<typename T>
double eval(const Eigen::MatrixBase<T>& Q)
{
//	std::cout << "Calling eval() from Regularizer_L21...\n";

	return Q.rowwise().norm().sum();
}

template<typename T>
void proxOperator(const Eigen::MatrixBase<T>& Q,
				  double reg_factor, 
                  Eigen::MatrixBase<T>& prox)
{
//	std::cout << "Calling proxOperator() from Regularizer_L21...\n";

	Eigen::ArrayXd thresholding =  
			1 - reg_factor * Q.rowwise().norm().array().inverse();

	thresholding = (thresholding < 0).select(0,thresholding);

	prox = Q.array().colwise() * thresholding; 
}

template<typename T>
double evalDuality(const Eigen::MatrixBase<T>& Q)
{
//	std::cout << "Calling evalDuality() inside Regularizer_L21...\n";

//	Eigen::MatrixXd tmp = Q.rowwise().norm();
//	return tmp.lpNorm<Eigen::Infinity>();

	//The following line is equivalent to the 2 previous ones
	return Q.rowwise().norm().template lpNorm<Eigen::Infinity>();
}

};

}

#endif
