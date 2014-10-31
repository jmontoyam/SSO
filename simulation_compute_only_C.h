#ifndef SIMULATION_COMPUTE_ONLY_C_H
#define SIMULATION_COMPUTE_ONLY_C_H

#include<string>
#include<Eigen/Dense>
#include"fista_method.h"
#include"general_utilities.h"
#include"squaredloss_mf.h"
#include"regularizer_l21.h"
#include<iostream>
#include<chrono>

void simulation_compute_only_C( int N, int K, int T,
                                const std::string& path_to_data,
								double& mean_elapsed_time,
								double&  std_elapsed_time)
{
	int num_simulations = 10;
	Eigen::VectorXd vector_elapsed_times( num_simulations );

	Eigen::MatrixXd A(14,N);
	Eigen::MatrixXd Y(14,T);

	Eigen::MatrixXd I = Eigen::MatrixXd::Identity(K,K);
	Eigen::MatrixXd D(K,K);
	Eigen::MatrixXd E(K,T);

	std::string path_to_A   = path_to_data + "/" + "A.txt";
	std::string path_to_Y   = path_to_data + "/" + "Y.txt";
	std::string path_to_L_a = path_to_data + "/" + "L_a.txt"; 

	SSO::loadMatrixFromFile( path_to_A, A );
	SSO::loadMatrixFromFile( path_to_Y, Y );
	
	double L_a = SSO::loadNumberFromFile( path_to_L_a );		

	Eigen::JacobiSVD<Eigen::MatrixXd> svd_Y( Y, Eigen::ComputeThinV);

	Eigen::MatrixXd V = svd_Y.matrixV();

	Eigen::MatrixXd C = V.leftCols(K).transpose();

	Eigen::MatrixXd B = Eigen::MatrixXd::Zero(N,K);

	SSO::SquaredLoss_MF squaredloss_mf( A, Y, B, C );
	SSO::Regularizer_L21 reg_l21;

	double L = L_a * ( C*C.transpose() ).norm();

	Eigen::MatrixXd tmp = ( A.transpose() * Y * C.transpose() );
	double lambda_max = reg_l21.evalDuality( tmp );
	double lambda = lambda_max * 0.2;

	double error_tol_fista = 1e-1;
	int final_iteration_fista = 0;
	double final_duality_gap_error = 0;
	int max_it_fista = 500;
	
	double elapsed_time = 0;

	SSO::fista(Y, B, squaredloss_mf, reg_l21, lambda, L, error_tol_fista,
			   final_iteration_fista, final_duality_gap_error,
			   max_it_fista);	


	for(int i=0; i<num_simulations; i++)
	{
		auto t_ini = std::chrono::steady_clock::now();

		D = B.transpose()*A.transpose()*A*B + I;
	
		E = B.transpose()*A.transpose()*Y;
	
		C = D.ldlt().solve(E);
		
		auto t_end = std::chrono::steady_clock::now();

		elapsed_time =
     	std::chrono::duration_cast<std::chrono::microseconds>(t_end-t_ini).count();

		vector_elapsed_times(i) = elapsed_time;
	}

	mean_elapsed_time = vector_elapsed_times.mean();

	std_elapsed_time = std::sqrt( (1.0/(num_simulations-1) ) *
     ((vector_elapsed_times.array() - mean_elapsed_time).pow(2).sum()));

	std::cout << "C:\n" << C << std::endl;


}



#endif
