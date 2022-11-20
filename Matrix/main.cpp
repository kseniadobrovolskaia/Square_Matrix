#include "Matrix.hpp"


int main()
{
	
	Matrix<double> m;

	std::cin >> m;

	std::cout<< "Determinant: " <<  m.det() <<  std::endl;
	
	return 0;
}

