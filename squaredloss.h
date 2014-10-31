#ifndef SQUAREDLOSS_H
#define SQUAREDLOSS_H

#include"loss.h"
#include<Eigen/Dense>
#include<iostream>

namespace SSO
{

class SquaredLoss: public Loss<SquaredLoss>
{
public:

SquaredLoss(const Eigen::MatrixXd& A_,
			const Eigen::MatrixXd& Y_,
			const Eigen::MatrixXd& S_):
			A(A_), Y(Y_), S(S_)
{

}

double evalFunction() 
{
//	std::cout << "\nCalling SquaredLoss evalFunction...\n";
	return 1.0/2.0 * ( (A*S-Y).squaredNorm() );
}

template<typename T>
void evalDerivative(Eigen::MatrixBase<T>& derivative) 
{
//	std::cout << "\nCalling SquaredLoss evalDerivative...\n";
	derivative = A.transpose()*(A*S-Y);
}

template<typename T>
void evalDerivative_for_duality(Eigen::MatrixBase<T>& derivative) 
{
//	std::cout << "Calling evalDerivative_for_duality() inside SquaredLoss.\n";
	derivative = A*S - Y;
}

template<typename T>
void evalDualityFactor(double lambda, Eigen::MatrixBase<T>& dualityFactor)
{
//	std::cout << "Calling evalDualityFactor() inside SquaredLoss...\n";

	Eigen::MatrixXd derivative_duality(Y.rows(),Y.cols());

	evalDerivative_for_duality(derivative_duality);

	dualityFactor = (1.0/lambda) * ( A.transpose()*derivative_duality );
}

void print_S() 
{
//	std::cout << "SquaredLoss print_S()...\n";
	std::cout << S << std::endl;
}


private:
const Eigen::MatrixXd& A;
const Eigen::MatrixXd& Y;
const Eigen::MatrixXd& S;

};

}

#endif
