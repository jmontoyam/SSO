#ifndef SQUAREDLOSS_MF_H
#define SQUAREDLOSS_MF_H

#include"loss.h"
#include<Eigen/Dense>
#include<iostream>

namespace SSO
{

class SquaredLoss_MF: public Loss<SquaredLoss_MF>
{
public:
SquaredLoss_MF(const Eigen::MatrixXd& A_,
			   const Eigen::MatrixXd& Y_,
			   const Eigen::MatrixXd& B_,
			   const Eigen::MatrixXd& C_):
			  A(A_), Y(Y_), B(B_), C(C_)
{
}

double evalFunction() 
{
//	std::cout << "Calling SquaredLoss_MF evalFunction...\n";
	return 1.0/2.0 * ( (A*B*C - Y).squaredNorm() ); 
}

template<typename T>
void evalDerivative(Eigen::MatrixBase<T>& derivative) 
{
	derivative = A.transpose() * (A*B*C-Y) * C.transpose();
}

template<typename T>
void evalDerivative_for_duality(Eigen::MatrixBase<T>& derivative) 
{
//	std::cout<<"Calling evalDerivative_for_duality() inside SquaredLoss_MF.\n";
	derivative = A*B*C - Y;
}

template<typename T>
void evalDualityFactor(double lambda, Eigen::MatrixBase<T>& dualityFactor)
{
//	std::cout << "Calling evalDualityFactor() inside SquaredLoss_MF...\n";

	Eigen::MatrixXd derivative_duality( Y.rows(), Y.cols() );

	evalDerivative_for_duality( derivative_duality );

	dualityFactor = 
			(1.0/lambda) * ( A.transpose()*derivative_duality*C.transpose() );
}

void print_B_C() 
{
//	std::cout << "SquaredLoss_MF print_B_C()...\n";
//	std::cout << "B:\n" << B  << std::endl << std::endl;
	std::cout << "C:\n" << C  << std::endl << std::endl;
	std::cout << "Y:\n" << Y  << std::endl << std::endl;
}

private:
const Eigen::MatrixXd& A;
const Eigen::MatrixXd& Y;
const Eigen::MatrixXd& B;
const Eigen::MatrixXd& C;

};

}

#endif
