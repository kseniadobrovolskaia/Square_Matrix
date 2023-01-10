#include <gtest/gtest.h>
#include <iostream>
#include <stdio.h>
#include <fstream>


enum name
{
  det_answers = 0,
  det_results = 1,
  input_answers = 2,
  input_results = 3,  
};


std::ifstream det_fans("../det_answers.txt");
std::ifstream det_fres("../det_results.txt");
std::ifstream input_fans("../input_answers.txt");
std::ifstream input_fres("../input_results.txt");
int read_file(name file, int elem);


//--------------------------Test_Matrix<int>--------------------------


TEST(Test_Matrix_int, Test1)
{
  EXPECT_EQ(read_file(det_answers, 1), read_file(det_results, 1));

}

TEST(Test_Matrix_int, Test2)
{

  EXPECT_EQ(read_file(det_answers, 2), read_file(det_results, 2));

}

TEST(Test_Matrix_int, Test3)
{

  EXPECT_EQ(read_file(det_answers, 3), read_file(det_results, 3));

}

TEST(Test_Matrix_int, Test4)
{

  EXPECT_EQ(read_file(det_answers, 4), read_file(det_results, 4));

}

TEST(Test_Matrix_int, Test5)
{

  EXPECT_EQ(read_file(det_answers, 5), read_file(det_results, 5));

}

TEST(Test_Input, Test1)
{

  EXPECT_EQ(read_file(input_answers, 1), read_file(input_results, 1));

}

TEST(Test_Input, Test2)
{

  EXPECT_EQ(read_file(input_answers, 2), read_file(input_results, 2));

}

TEST(Test_Input, Test3)
{

  EXPECT_EQ(read_file(input_answers, 3), read_file(input_results, 3));

}

TEST(Test_Input, Test4)
{

  EXPECT_EQ(read_file(input_answers, 4), read_file(input_results, 4));

}

TEST(Test_Input, Test5)
{

  EXPECT_EQ(read_file(input_answers, 5), read_file(input_results, 5));

}


int read_file(name file, int elem)
{
  static int elems[20];
  static int flag = 0;

  if (flag == 0)
  {
    if (!(det_fans.is_open()))
    {
      std::cerr << "File \"det_answers.txt\" did not open" << std::endl;
      exit(EXIT_FAILURE);
    }

    if (!(det_fres.is_open()))
    {
      std::cerr << "File \"det_results.txt\" did not open" << std::endl;
      exit(EXIT_FAILURE);
    }

    if (!(input_fans.is_open()))
    {
      std::cerr << "File \"input_answers.txt\" did not open" << std::endl;
      exit(EXIT_FAILURE);
    }

    if (!(input_fres.is_open()))
    {
      std::cerr << "File \"input_results.txt\" did not open" << std::endl;
      exit(EXIT_FAILURE);
    }

    flag++;
    for (int i = 0; i < 5; i++)
    {
      det_fans >> elems[0*5 + i];
    }
    det_fans.close();

    for (int i = 0; i < 5; i++)
    {
      det_fres >> elems[1*5 + i];
    }
    det_fres.close();

    for (int i = 0; i < 5; i++)
    {
      input_fans >> elems[2*5 + i];
    }
    input_fans.close();

    for (int i = 0; i < 5; i++)
    {
      input_fres >> elems[3*5 + i];
    }
    input_fres.close();
  }

  return elems[file*5 + elem - 1];
}

