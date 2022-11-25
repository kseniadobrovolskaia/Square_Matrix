#include "Matrix.hpp"


int main()
{
	try
	{
		Matrix<double> m;

		std::cin >> m;

		std::cout<< "Determinant: " <<  m.det() <<  std::endl;

	}
	catch(std::exception & ex)
	{
		std::cout << ex.what() << std::endl;
		exit(EXIT_FAILURE);
	}

	
	return 0;
}

