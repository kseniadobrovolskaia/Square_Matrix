#include "Matrix.hpp"


void print_in_file(int *answers, int num_file);


int main()
{
	std::ifstream det_data, input_data;

	int det_answers[5] = {0}, input_answers[5] = {0};

	det_data.open("det_data.txt");
	if (!(det_data.is_open()))
  {
    std::cerr << "File \"det_data.txt\" did not open" << std::endl;
    exit(EXIT_FAILURE);
  }
	
	for (int num_test = 0; num_test < 5; num_test++)
	{
		try
		{
			int n; 
			char space;

			det_data >> std::noskipws;
			det_data >> n;
			det_data >> space;

			if (!std::isspace(space) || std::cin.fail())
			{
				throw std::logic_error("Invalid input");
			}

			Matrix<int> m(n);
			
			det_data >> m;

			det_answers[num_test] = m.det();

			std::cout << "Determinant of the " << num_test + 1 << " matrix: " << det_answers[num_test] << std::endl;
		}
		catch(std::exception & ex)
		{
			std::cout << ex.what() << std::endl;
			exit(EXIT_FAILURE);
		}
	}

	print_in_file(det_answers, 0);

	det_data.close();

	input_data.open("input_data.txt");
	if (!(input_data.is_open()))
  {
    std::cerr << "File \"input_data.txt\" did not open" << std::endl;
    exit(EXIT_FAILURE);
  }

	for (int num_test = 0; num_test < 5; num_test++)
	{
		try
		{
			int n; 
			char space;

			input_data >> std::noskipws;
			input_data >> n;
			input_data >> space;

			if (!std::isspace(space) || std::cin.fail())
			{
				throw std::logic_error("Invalid input");
			}

			Matrix<int> m(n);
			
			input_data >> m;

			input_answers[num_test] = 1;
			
		}
		catch(std::exception & ex)
		{
			input_answers[num_test] = 0;
			char elem;
			input_data >> elem;
			while (elem != '\n')
			{
				input_data >> elem;
			}
		}

		std::cout << "Correct input in " << num_test + 1 << " test: " << input_answers[num_test] << std::endl;
	}

	print_in_file(input_answers, 1);

	input_data.close();
	
	return 0;
}


void print_in_file(int *answers, int num_file)
{
	std::ofstream results;

	if (num_file == 0)
	{
		results.open("det_results.txt");

		if (!(results.is_open()))
		{
		  std::cerr << "File \"det_results.txt\" did not open" << std::endl;
		  exit(EXIT_FAILURE);
		}
	}
	else
	{
		results.open("input_results.txt");

		if (!(results.is_open()))
		{
		  std::cerr << "File \"input_results.txt\" did not open" << std::endl;
		  exit(EXIT_FAILURE);
		}

	}

	for (int num_test = 0; num_test < 5; num_test++)
	{
		results << answers[num_test] << " ";
	}
	
	results.close();
}
