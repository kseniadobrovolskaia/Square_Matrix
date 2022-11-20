#include "Matrix.hpp"


int main()
{
	
	Matrix<int> m;

	std::cin >> m;

	std::cout<< "Determinant: " <<  m.det() << std::endl;
	
	return 0;
}

