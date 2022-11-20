#pragma once

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


int read_file(int file, int elem)
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


