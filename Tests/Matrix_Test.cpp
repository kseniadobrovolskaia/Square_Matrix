#include "Matrix.hpp"


void print_in_file(int *answers);


int main()
{
	std::ifstream data;

	int answers[5] = {0};

	data.open("data.txt");
	
	for (int num_test = 0; num_test < 5; num_test++)
	{
		Matrix<int> m;
		data >> m;

		answers[num_test] = m.det();

		std::cout << "Determinant of the " << num_test + 1 << " matrix: " << answers[num_test] << std::endl;
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