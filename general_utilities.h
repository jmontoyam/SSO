#ifndef GENERAL_UTILITIES_H
#define GENERAL_UTILITIES_H

#include<iostream>
#include<string>
#include<fstream>
#include<regex>
#include<sstream>
#include<Eigen/Dense>

//Use Qt to work with Android
#ifdef Q_OS_ANDROID
#include<QFile>
#include<QTextStream>
#include<QDebug>
#endif


namespace SSO
{
#ifndef Q_OS_ANDROID

//The following functions uses regex c++11 features, which are not
//currently support in android ndk

template<typename T>
void loadMatrixFromFile(const std::string& path_to_file, 
							  Eigen::MatrixBase<T>& M)
{

	std::ifstream fh(path_to_file);

	if( !fh.is_open() )
	{
		std::cerr << "*** ERROR LOADING MATRIX FROM FILE: " << 
                          path_to_file << "\n";
		return;
	}

	std::string line;
	
	int counter_rows = 0;
	int counter_cols = 0;

	std::sregex_token_iterator end_of_line;

	std::regex delimiter("\t");

	while( std::getline( fh, line ) )
	{
		std::sregex_token_iterator iterator( line.begin(), line.end(), 
											 delimiter, -1);
		counter_cols = 0;

		for( ; iterator!= end_of_line; iterator++ )
		{
			M( counter_rows, counter_cols ) = std::stod( *iterator );

			counter_cols++;
		}

		counter_rows++;

	}

	fh.close();
}


double loadNumberFromFile( const std::string& path_to_file )
{
	std::ifstream fh(path_to_file);

	if( !fh.is_open() )
	{
		std::cerr << "*** ERROR LOADING NUMBER FROM FILE: " <<
							path_to_file << "\n";
		return 0;
	}

	std::string line;

	std::getline( fh, line );

	double L = std::stod( line );
	
	fh.close();

	return L;
}

#else

template<typename T>
void loadMatrixFromFile(const std::string& path_to_file,
                              Eigen::MatrixBase<T>& M)
{


    QFile fh(path_to_file.c_str());

    if( !fh.open( QIODevice::ReadOnly | QIODevice::Text ) )
    {
        std::cerr << "*** ERROR LOADING MATRIX FROM FILE: " <<
                          path_to_file << "\n";
        return;
    }


    QTextStream in(&fh);

    int i=0;
    int j=0;

    while ( !in.atEnd() )
    {
        QString line = in.readLine();
        QStringList cols = line.split("\t");

        foreach (QString element, cols)
        {
            M(i,j) = element.toDouble();

            j++;

        }

        j = 0;

        i++;
    }

    fh.close();

}

double loadNumberFromFile( const std::string& path_to_file )
{
    QFile fh(path_to_file.c_str());

    if( !fh.open( QIODevice::ReadOnly | QIODevice::Text ) )
    {
        std::cerr << "*** ERROR LOADING MATRIX FROM FILE: " <<
                          path_to_file << "\n";
        return 0;
    }


    QTextStream in(&fh);

    QString mydata = in.readAll();

    double L = mydata.toDouble();

    fh.close();

    return L;

}


#endif

}

#endif
