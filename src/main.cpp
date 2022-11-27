#include "Matrix.hpp"


int main()
{
	try
	{
		int n;

		std::cin >> n;

		if (std::cin.fail())
		{
			throw std::logic_error("Invalid input");
		}

		Matrix<double> m(n);
		
		std::cin >> m;

		std::cout << "Determinant: " << m.det() << std::endl;	

	}
	catch(std::exception & ex)
	{
		std::cout << ex.what() << std::endl;
		exit(EXIT_FAILURE);
	}
	
	return 0;
}

