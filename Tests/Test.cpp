#include <gtest/gtest.h>
#include <iostream>
#include <stdio.h>
#include <fstream>


enum name
{
  answers,
  results,  
};


std::ifstream fans("../answers.txt");
std::ifstream fres("../results.txt");
int read_file(name file, int elem);


//--------------------------Test_Matrix<int>--------------------------


TEST(Test_Matrix_int, Test1)
{
  EXPECT_EQ(read_file(answers, 1), read_file(results, 1));

}

TEST(Test_Matrix_int, Test2)
{

  EXPECT_EQ(read_file(answers, 2), read_file(results, 2));

}

TEST(Test_Matrix_int, Test3)
{

  EXPECT_EQ(read_file(answers, 3), read_file(results, 3));

}

TEST(Test_Matrix_int, Test4)
{

  EXPECT_EQ(read_file(answers, 4), read_file(results, 4));

}

TEST(Test_Matrix_int, Test5)
{

  EXPECT_EQ(read_file(answers, 5), read_file(results, 5));

}


int read_file(name file, int elem)
{
  static int elems[10];
  static int flag = 0;

  if (flag == 0)
  {
    flag++;
    for (int i = 0; i < 5; i++)
    {
      fans >> elems[0*5 + i];
    }
    fans.close();

    for (int i = 0; i < 5; i++)
    {
      fres >> elems[1*5 + i];
    }
    fres.close();
  }

  return elems[file*5 + elem - 1];
}

