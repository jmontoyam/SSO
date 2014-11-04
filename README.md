<h3>Structured Sparse Optimization Library: solving nonsmooth convex optimization problems on Mobile devices and Laptop/Desktop machines</h3>


Structured Sparse Optimization (<b>SSO</b>) Library is a C++ template library for solving composite
optimization problems, whose objective function can be splitted into a 
sum of a smooth and a nonsmooth function (both convex). In order to solve such problems,
it uses the Fast Iterative Shrinkage-Thresholding Algorithm (FISTA). It is based on Eigen, 
a C++ template library for linear algebra (http://eigen.tuxfamily.org), and therefore, 
it inherits all its "goodies" such as explicit vectorization
for SSE 2/3/4, ARM NEON and AltiVec instruction sets. It can be used
on mobile devices, as well as on laptop and desktop machines. It is a multiplatform library:
it can be used on Android, Linux, Mac and Windows OS (currently tested on Android and Ubuntu).
The current implementation can solve nonsmooth convex optimization problems involving standard
regularizers such as Lasso, Group Lasso and the matrix factorization approach proposed in
the paper "A regularized matrix factorization approach to induce structured sparse-low-rank solutions in the EEG inverse problem"
(http://asp.eurasipjournals.com/content/2014/1/97). 
SSO library is highly configurable by the user, it can be easily extended to incorporate new regularizers
and new cost functions. Its implementation is based heavily on template metaprogramming and static polymorphism. 

The library contains the following example files and projects 
(Qt projects (http://qt-project.org/) to be run on Android and Laptop/Desktop machines):

- Simulation_Compute_Only_B.cpp (Console app)
- Simulation_Compute_Only_C.cpp (Console app)
- Android_Compute_Only_B (Qt based GUI app for Android and Laptop/Desktop machines)	
- Android_Compute_Only_C (Qt based GUI app for Android and Laptop/Desktop machines)	

You can compile the console app as follows:

g++ -I/path/to/eigen/ Simulation_Compute_Only_B.cpp -DNDEBUG -O2 -std=c++11 -o Simulation_Compute_Only_B

g++ -I/path/to/eigen/ Simulation_Compute_Only_C.cpp -DNDEBUG -O2 -std=c++11 -o Simulation_Compute_Only_C

To compile the Qt based GUI app for Android and Laptop/Desktop machines, please proceed as follows:

1) Dowload and install Qt (http://qt-project.org/).

2) Configure Qt for Android (http://qt-project.org/doc/qt-5/androidgs.html)

3) Run Qt, and then select: File->Open File or Project and select the project file inside the Android_Compute_Only_B folder 
(Android_Compute_Only_B.pro). 

4) In the Configure Project window that appears after executing step 3), select both options "Android for armeabi-v7a" and "Desktop Qt 5.3.x GCC 64 bits", and then click the button "Configure Project".

5) After executing step 4), the "Android_Compute_Only_B" must be opened. Now, look at the bottom of the left margin, there you will find a PC icon with the word debug below it, click on this icon, and select Desktop Qt 5.3.x GCC 64 bits -> Release. Then, compile and run the app (ctrl+r).

6) If you want to run the "Android_Compute_Only_B" app on your smartphone/tablet device, connect the device to the your PC and then repeat step 5),
but this time select Android for armeabi-v7a -> Release.

7) Repeat the same process to compile and run Android_Compute_Only_C.

That's it!, enjoy the library!, all the comments and suggestions are truly welcome! :-).

This library has been jointly used with the smarthphonebrainscanner2 project (https://github.com/SmartphoneBrainScanner/smartphonebrainscanner2-core/wiki) to solve,
using structured sparsity optimization algorithms, the EEG inverse problem on mobile devices 
(currently tested on the Nexus7 and the Galaxy Note I). The summarized process is as follows: 

- Capture EEG data from the Emotiv neuroheadset (http://emotiv.com/). 

- Solve (online and as fast as possible) the nonsmooth convex optimization problem related with the EEG inverse problem (for instance, using the matrix factorization approach mentioned above).

- Finally, show, using a 3D brain model, the solution of the former problem: the active brain cortex areas whose activity have produced the recorded data.

In the following we can see some pictures of this process in action:

![alt tag](https://raw.github.com/jmontoyam/SSO/master/img/galaxy_note_online_matrix_factorization.jpg) 
![alt tag](https://raw.github.com/jmontoyam/SSO/master/img/nexus7_online_matrix_factorization.jpg) 
![alt tag](https://raw.github.com/jmontoyam/SSO/master/img/multiplatform_online_matrix_factorization.jpg) 
