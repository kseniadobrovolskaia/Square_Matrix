#include "Test.hpp"




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

