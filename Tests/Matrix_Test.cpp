#include "Matrix.hpp"


void print_in_file(int *answers);


int main()
{
	std::ifstream data;

	int answers[5] = {0};

	data.open("data.txt");
	
	for (int num_test = 0; num_test < 5; num_test++)
	{
		try
		{
			int n; 

			data >> n;

			Matrix<int> m(n);
			
			data >> m;

			answers[num_test] = m.det();

			std::cout << "Determinant of the " << num_test + 1 << " matrix: " << answers[num_test] << std::endl;
		}
		catch(std::exception & ex)
		{
			std::cout << ex.what() << std::endl;
			exit(EXIT_FAILURE);
		}
	}

	data.close();
	
	print_in_file(answers);

	return 0;
}


void print_in_file(int *answers)
{
	std::ofstream results;

	results.open("results.txt");

	for (int num_test = 0; num_test < 5; num_test++)
	{
		results << answers[num_test] << " ";
	}
	
	results.close();
}
