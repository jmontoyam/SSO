#ifndef FISTA_METHOD_H
#define FISTA_METHOD_H

#include<cmath>
#include<Eigen/Dense>
#include"loss.h"
#include"regularizer.h"
#include<iostream>

namespace SSO
{

template<typename T1, typename T2, typename T3>
void fista(const Eigen::MatrixBase<T1>& Y,
			     Eigen::MatrixBase<T1>& S,
                 SSO::Loss<T2>& loss,
				 SSO::Regularizer<T3>& reg,
				 double lambda,
				 double L,
				 double error_tol,
				 int& final_iteration,
				 double& final_duality_gap_error,
				 int max_it=100,
				 int iter_duality_check=10)
{
int N = S.rows();
int T = S.cols();
int M = Y.rows();
int iteration_counter = 0;

double t_old = 1;
double t_new = 0;
double reg_factor = lambda/L;
double H = 0;
double dual_norm_eval = 0;
double g = 0;
double duality_gap_error = 0;

Eigen::MatrixXd tmp(N,T);
Eigen::MatrixXd grad_loss_function(N,T);
Eigen::MatrixXd V = S;
Eigen::MatrixXd S_old = S;
Eigen::MatrixXd derivative_duality(M,T);
Eigen::MatrixXd duality_factor;
Eigen::MatrixXd nu(M,T);

//std::cout << "Before fista loop:\n" << S.topRows(4) << "\n\n";

for(int i=1; i<=max_it; i++)
{
	iteration_counter++;

	S = V;	

	loss.evalDerivative( grad_loss_function );

	tmp = V - 1/L*grad_loss_function;

	reg.proxOperator( tmp, reg_factor, S );

 	t_new = ( 1 + std::sqrt( 1 + 4*std::pow( t_old, 2 ) ) ) / 2.0;

	V = S + ( ( t_old - 1 ) / t_new )*( S - S_old);

	//std::cout << "S at iteration " << i << ":\n" << S << std::endl << std::endl;

	/************************************************************************/
	/*Compute the duality gap*/
	/************************************************************************/


	if ((i % iter_duality_check)==0)
	{
		H = loss.evalFunction() + lambda*reg.eval(S);

		loss.evalDerivative_for_duality( derivative_duality );

		loss.evalDualityFactor( lambda, duality_factor );
	
		dual_norm_eval = reg.evalDuality( duality_factor );

        nu = fmin( 1, 1.0/dual_norm_eval )*derivative_duality;

		g = -1*( 1.0/2.0*nu.squaredNorm() + ( nu.transpose()*Y ).trace() );
	
		duality_gap_error = std::abs( H-g )/std::abs(H);  		

		if ( duality_gap_error <= error_tol )
		{
			break;
		}

	}

	/************************************************************************/
	

	t_old = t_new;
	S_old = S;

}

final_iteration = iteration_counter;
final_duality_gap_error = duality_gap_error;

//std::cout << "After fista loop:\n" << S.topRows(4) << "\n\n";

//std::cout << "final iteration: " << final_iteration << ", " <<
//			 "duality gap (relative error): " << final_duality_gap_error <<"\n";
}

}

#endif
