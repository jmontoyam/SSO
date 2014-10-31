#include"simulation_compute_only_C.h"
#include<string>
#include<iostream>

using std::cout;
using std::endl;

int main( int argc, char* argv[] )
{
	int K = 4;
	int T = 4;

	int N = 1028;
   
	double mean_elapsed_time = 0;
	double  std_elapsed_time = 0;

	std::string path_to_data = 
     std::string("./Measuring_Time/Simulation_Compute_Only_B/Varying_K") +
	 std::string("/N") + std::to_string(N) +
     std::string("/K") +
     std::to_string(K) + "/Data";	


	simulation_compute_only_C( N, K, T, path_to_data, 
							   mean_elapsed_time, std_elapsed_time);

	cout << "\nmean elapsed time: " << mean_elapsed_time <<" us\n" << endl;

	return 0;
}
