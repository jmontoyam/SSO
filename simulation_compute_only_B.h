#ifndef SIMULATION_COMPUTE_ONLY_B_H
#define SIMULATION_COMPUTE_ONLY_B_H

#include<string>
#include<Eigen/Dense>
#include"fista_method.h"
#include"general_utilities.h"
#include"squaredloss_mf.h"
#include"regularizer_l21.h"
#include<iostream>
#include<chrono>

#ifdef Q_OS_ANDROID
#include<QFile>
#include<QTextStream>
#endif

using std::cout;
using std::endl;

void simulation_compute_only_B( int N, int K, int T,
                                const std::string& path_to_data,
								double& mean_elapsed_time,
                                double&  std_elapsed_time,
                                const std::string& path_results)
{
	int num_simulations = 10;
	Eigen::VectorXd vector_elapsed_times( num_simulations );

	Eigen::MatrixXd A(14,N);
	Eigen::MatrixXd Y(14,T);

	std::string path_to_A   = path_to_data + "/" + "A.txt";
	std::string path_to_Y   = path_to_data + "/" + "Y.txt";
	std::string path_to_L_a = path_to_data + "/" + "L_a.txt"; 
	std::string path_to_C   = path_to_data + "/" + "trueC.txt";
	
	SSO::loadMatrixFromFile( path_to_A, A );
	SSO::loadMatrixFromFile( path_to_Y, Y );
	
	double L_a = SSO::loadNumberFromFile( path_to_L_a );		

	Eigen::JacobiSVD<Eigen::MatrixXd> svd_Y( Y, Eigen::ComputeThinV);

	Eigen::MatrixXd V = svd_Y.matrixV();

	Eigen::MatrixXd B = Eigen::MatrixXd::Zero(N,K);
 
	Eigen::MatrixXd C = V.leftCols(K).transpose();

    SSO::Regularizer_L21 reg_l21;

	double L = L_a * ( C*C.transpose() ).norm();

	Eigen::MatrixXd tmp = ( A.transpose() * Y * C.transpose() );
	double lambda_max = reg_l21.evalDuality( tmp );
	double lambda = lambda_max * 0.5;

	double error_tol_fista = 1e-1;
	int final_iteration_fista = 0;
	double final_duality_gap_error = 0;
	int max_it_fista = 500;
	
	double elapsed_time = 0;

	for(int i=0; i<num_simulations; i++)
	{
		B = Eigen::MatrixXd::Zero(N,K);

		SSO::SquaredLoss_MF squaredloss_mf( A, Y, B, C );

		auto t_ini = std::chrono::steady_clock::now();

		SSO::fista(Y, B, squaredloss_mf, reg_l21, lambda, L, error_tol_fista,
			   final_iteration_fista, final_duality_gap_error,
			   max_it_fista);	

		auto t_end = std::chrono::steady_clock::now();

		elapsed_time =
     	std::chrono::duration_cast<std::chrono::microseconds>(t_end-t_ini).count();

		vector_elapsed_times(i) = elapsed_time;

		cout << "Lambda: " << lambda << ", final iteration: " <<
		 final_iteration_fista << ", duality gap (relative error): " <<
		 final_duality_gap_error << endl;

	}

	mean_elapsed_time = vector_elapsed_times.mean();

	std_elapsed_time = std::sqrt( (1.0/(num_simulations-1) ) *
     ((vector_elapsed_times.array() - mean_elapsed_time).pow(2).sum()));


	cout << "\nB:\n" << B << "\n\n";
	cout << "\nC:\n" << C << "\n\n";

	cout << "Lambda max: " << lambda_max << endl;
    cout << "Lambda: " << lambda << endl;
    cout << "L: " << L << endl;
	cout << "L_a: " << L_a << endl;

	cout << "\nY:\n" << Y << endl;
    cout << "\n Mean elapsed time (us): " << mean_elapsed_time << "\n"<< endl;
	cout << "\nFinished." << endl;

#ifdef Q_OS_ANDROID
QFile fh(path_results.c_str());

if( !fh.open( QIODevice::WriteOnly | QIODevice::Text ) )
{
    std::cerr << "*** ERROR LOADING MATRIX FROM FILE: " <<
                      path_results << "\n";
    return;
}


QTextStream out(&fh);
out<<"mean: " << mean_elapsed_time;
out<<"\nstd: " << std_elapsed_time<<"\n";
out.flush();
fh.close();
#endif

}



#endif
