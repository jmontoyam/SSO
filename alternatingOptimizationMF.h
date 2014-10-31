#ifndef ALTERNATINGOPTIMIZATIONMF_H
#define ALTERNATINGOPTIMIZATIONMF_H

#include<cmath>
#include<Eigen/Dense>
#include"regularizer.h"
#include"loss.h"
#include"fista_method.h"

namespace SSO
{
template<typename T1, typename T2, typename T3>
void alternatingOptimizationMF(const Eigen::MatrixBase<T1>& A,
							   const Eigen::MatrixBase<T1>& Y,
							         Eigen::MatrixBase<T1>& B,
									 Eigen::MatrixBase<T1>& C,
									 Eigen::MatrixBase<T1>& S,
									 SSO::Loss<T2>& loss,
									 SSO::Regularizer<T3>& reg,
									 double percentage_lambda,
									 double L_A,
									 double error_tol_mf,
									 double error_tol_fista,
									 int& final_iteration,
									 double& final_relative_error,
									 double& final_lambda,
									 int max_it_mf = 100,
									 int max_it_fista = 100,
									 int iter_duality_check=10)
{
int N = B.rows();
int K = B.cols();
int T = C.cols();

Eigen::MatrixXd I = Eigen::MatrixXd::Identity(K,K);
Eigen::MatrixXd S_old = Eigen::MatrixXd::Zero(N,T);
Eigen::MatrixXd D(K,K);
Eigen::MatrixXd E(K,T);
Eigen::MatrixXd tmp(N,K);
 
const double EPSILON = 1e-10;
double L = 0;
double relative_error = 0;
int iteration_counter = 0;
int final_iteration_fista = 0;
double final_duality_gap_error = 0;

double lambda_max = 0;
double lambda = 0;

for(int i=1; i<=max_it_mf; i++)
{
	iteration_counter++;
	
	/*************************************************************************/
	/*Fix C, estimate B*/
	/*************************************************************************/

	/*** Update lambda_max and lambda as a function of C ***/
	tmp = A.transpose()*Y*C.transpose();

	lambda_max = reg.evalDuality( tmp );

	lambda = lambda_max * percentage_lambda;
	/*******************************************************/

	L = L_A * (C*C.transpose()).norm();

	SSO::fista(Y, B, loss, reg, lambda, L, error_tol_fista,
			   final_iteration_fista, final_duality_gap_error,
			   max_it_fista, iter_duality_check);

	/*************************************************************************/
	/*Fix B, estimate C*/
	/*************************************************************************/
	D = B.transpose()*A.transpose()*A*B + I;
	
	E = B.transpose()*A.transpose()*Y;
	
	C = D.ldlt().solve(E);

	/*************************************************************************/
	/*Check stopping criteria*/
	/*************************************************************************/
	S.noalias() = B*C;
	
	relative_error = (S-S_old).norm() / std::fmax(EPSILON, S.norm());

	if ( (relative_error <= error_tol_mf)||( S.norm()==0 ) )
	{
		break;
	}
	/*************************************************************************/

	S_old = S;
	
}

final_iteration = iteration_counter;
final_relative_error = relative_error;
final_lambda = lambda;

}


}

#endif
