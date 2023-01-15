#ifndef MEMORY_H
#define MEMORY_H


#include <iostream>
#include <cmath>
#include <fstream>
#include <cstdlib>
#include <new>
#include <stdexcept>
#include <exception>
#include <string>
#include <algorithm>
#include <typeinfo>
#include <cstring>


template<typename T>
class Matrix;


template<typename T>
class Memory
{
	int n_t;
	struct Row
	{
		T *row;
		T operator[](int n) const { return row[n]; }
		T & operator[](int n) { return row[n]; }
	};
	struct Row* matrix;
	
public:

	friend class Matrix<T>;

	explicit Memory(int n = 0);

	Memory(const Memory<T> & mt);
	Memory<T> & operator=(const Memory<T> & mt);
	Memory(Memory<T> && mt): n_t(mt.n_t), matrix(mt.matrix) { mt.matrix = nullptr; mt.n_t = 0; };
	Memory<T> & operator=(Memory<T> && mt);
	virtual ~Memory() noexcept;

	Row operator[](int n) const { return matrix[n]; }
	Row & operator[](int n) { return matrix[n]; }
	void swap(Memory<T> & mt);
	
};


//---------------------------------------------------------------------
template<typename T>
Memory<T>::Memory(int n): n_t(n)
{
	if (n < 0)
	{
		throw std::logic_error("Wrong matrix size");
	}

	int use_mem = 0;
	
	try
	{
		matrix = new struct Row[n];
		use_mem++;

		for (int i = 0; i < n; i++)
		{
			matrix[i].row = new T[n];
			use_mem++;
		}
	}
	catch(...)
	{
		for (int i = 0; i < use_mem - 1; i++)
		{
			delete [] matrix[i].row;
		}

		if (use_mem > 0)
		{
			delete [] matrix;
		}

		throw;
	}
}


template<typename T>
Memory<T>::~Memory() noexcept
{
	for (int i = 0; i < n_t; i++)
	{
		delete [] matrix[i].row;
	}
	delete [] matrix;

}


template<typename T>
Memory<T>::Memory(const Memory<T> & mt)
{	
	n_t = mt.n_t;
	int use_mem = 0;

	Memory<T> m_tmp(n_t);

	try
	{
		for (int i = 0; i < n_t; i++)
		{
			std::copy( mt.matrix[i].row,  mt.matrix[i].row + n_t, m_tmp.matrix[i].row);
		}

		matrix = new struct Row[n_t];
		use_mem++;

		for (int i = 0; i < n_t; i++)
		{
			matrix[i].row = new T[n_t];
			use_mem++;
		}

		for (int i = 0; i < n_t; i++)
		{
			std::copy(m_tmp.matrix[i].row, m_tmp.matrix[i].row + n_t, matrix[i].row);
		}
	}
	catch(...)
	{
		for (int i = 0; i < use_mem - 1; i++)
		{
			delete [] matrix[i].row;
		}

		if (use_mem > 0)
		{
			delete [] matrix;
		}

		throw;
	}

}


template<typename T>
Memory<T> & Memory<T>::operator=(const Memory<T> & mt)
{

	Memory<T> m_tmp(mt);

	swap(m_tmp);

	return *this;
}


template<typename T>
Memory<T> & Memory<T>::operator=(Memory<T> && mt)
{

	Memory<T> m_tmp(mt);

	swap(m_tmp);
	mt.matrix = nullptr;
	mt.n_t = 0;

	return *this;
}


template<typename T>
void Memory<T>::swap(Memory<T> & mt)
{
	if (n_t != mt.n_t)
	{
		throw std::logic_error("You cannot swap matrices of different sizes");
	}

	for (int i = 0; i < n_t; i++)
	{
		std::swap(matrix[i].row, mt.matrix[i].row);
	}
}


#endif

