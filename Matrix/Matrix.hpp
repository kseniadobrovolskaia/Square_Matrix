#ifndef MATRIX_H
#define MATRIX_H


#include <iostream>
#include <cmath>
#include <fstream>
#include <cstdlib>
#include <new>
#include <stdexcept>
#include <exception>
#include <string>
#include <algorithm>


#define ACCURACY 1e-5


template<typename T>
class Matrix;


template<typename T> std::ostream & operator<<(std::ostream & ostr, const Matrix<T> & mt);
template<typename T> std::istream & operator>>(std::istream & istr, Matrix<T> & mt);


template<typename T>
class Matrix
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

	explicit Matrix(int n = 0);
	Matrix(const Matrix<T> & mt);
	Matrix<T> & operator=(const Matrix<T> & mt);
	~Matrix();

	Row operator[](int n) const { return matrix[n]; }
	Row & operator[](int n) { return matrix[n]; }

	int get_n() const { return n_t;};
	T det() const;
	Matrix<T> & trans();
	Matrix<T> & zero();
	void swap_rows(int n, int k);
	

	Matrix<T> & operator+=(const Matrix<T> & mt);
	Matrix<T> & operator-=(const Matrix<T> & mt);
	Matrix<T> & operator*=(const Matrix<T> & mt);
	void swap(Matrix<T> & mt);
	bool operator==(const Matrix<T> & mt) const;


	template<typename U>
	Matrix<T> operator*(U elem) const;
	template<typename U>
	Matrix<T> & operator*=(U elem);
	

	friend std::ostream & operator<< <T>(std::ostream & ostr, const Matrix<T> & mt);
	friend std::istream & operator>> <T>(std::istream & istr, Matrix<T> & mt);
	
};


template<typename T>
bool is_zero(const T elem)
{
	return (elem > -ACCURACY) && (elem < ACCURACY);
}


//-----------------------------------Matrix----------------------------------------


template<typename T>
Matrix<T>::Matrix(int n): n_t(n)
{
	if (n < 0)
	{
		throw std::logic_error("Wrong matrix size");
	}

	int use_mem = 0;
	
	try
	{
		matrix = new struct Row[n];

		for (int i = 0; i < n; i++)
		{
			matrix[i].row = new T[n];
			use_mem++;
		}
	}
	catch(...)
	{
		for (int i = 0; i < use_mem; i++)
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
Matrix<T>::~Matrix()
{
	for (int i = 0; i < n_t; i++)
	{
		delete [] matrix[i].row;
	}
	delete [] matrix;

}


template<typename T>
Matrix<T>::Matrix(const Matrix<T> & mt)
{	
	n_t = mt.n_t;
	int use_mem = 0;

	Matrix<T> m_tmp(n_t);

	try
	{
		for (int i = 0; i < n_t; i++)
		{
			std::copy( mt.matrix[i].row,  mt.matrix[i].row + n_t, m_tmp.matrix[i].row);
		}

		matrix = new struct Row[n_t];

		for (int i = 0; i < n_t; i++)
		{
			matrix[i].row = new T[n_t];
			use_mem++;
		}
	}
	catch(...)
	{
		for (int i = 0; i < use_mem; i++)
		{
			delete [] matrix[i].row;
		}

		if (use_mem > 0)
		{
			delete [] matrix;
		}

		throw;
	}

	for (int i = 0; i < n_t; i++)
	{
		std::copy(m_tmp.matrix[i].row, m_tmp.matrix[i].row + n_t, matrix[i].row);
	}
}


template<typename T>
Matrix<T> & Matrix<T>::operator=(const Matrix<T> & mt)
{
	if (n_t != mt.n_t)
	{
		throw std::logic_error("You cannot use operator = for matrices of different sizes");
	}

	Matrix<T> m_tmp(mt);

	swap(m_tmp);

	return *this;
}


template<typename T>
bool Matrix<T>::operator==(const Matrix<T> & mt) const
{
	if (n_t != mt.n_t)
	{
		throw std::logic_error("Сomparison of matrices of different sizes is undefined");
	}
 	
	for (int i = 0; i < n_t; i++)
	{
		if (!std::equal(matrix[i].row, matrix[i].row + n_t, mt.matrix[i].row, mt.matrix[i].row + n_t))
        {
            return 0;
        }
	}

	return 1;
}


template<typename T>
void Matrix<T>::swap(Matrix<T> & mt)
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


template<typename T>
T Matrix<T>::det() const
{
	Matrix<T> M = *this;
	int sign = 1;
	T znam = 1;

	if (n_t == 0)
	{
		return -1;
	}

	for (int k = 0; k < n_t - 1; k++)
	{
		if (k != 0)
		{
			znam = M[k-1][k-1];
		}

		if (is_zero(M[k][k]))
		{
			sign = -sign;
			int n = k;

			while (is_zero(M[n][k]))
			{
				n++;
				if (n == n_t)
				{
					return 0;
				}
			}
			M.swap_rows(n, k);
					
		}

		for (int i = k + 1; i < n_t; i++)
		{
			for (int j = k + 1; j < n_t; j++)
			{
				M[i][j] = (M[i][j]*M[k][k] - M[i][k]*M[k][j]) / znam;
				
			}
		}
	}

	return M[n_t - 1][n_t - 1] * sign;
}


template<typename T>
Matrix<T> & Matrix<T>::zero()
{
	T zero[n_t] = {0};

	for (int i = 0; i < n_t; i++)
	{
		std::copy(zero, zero + n_t, matrix[i].row);
	}

	return *this;
}


template<typename T>
Matrix<T> & Matrix<T>::trans()
{
	Matrix<T> result(n_t);

	for (int i = 0; i < n_t; i++)
	{
		for (int j = 0; j < n_t; j++)
		{
			result[j][i] = (*this)[i][j];
		}
	}

	return *this = result;
}


template<typename T>
void Matrix<T>::swap_rows(int n, int k)
{
	std::swap(matrix[n].row, matrix[k].row);
}


//---------------------------Operators in the class----------------------------------

template<typename T>
Matrix<T> & Matrix<T>::operator+=(const Matrix<T> & mt)
{
	if (n_t != mt.n_t)
	{
		throw std::logic_error("Incorrect size for operator +=");
	}

	Matrix<T> m_tmp((*this));

	for (int i = 0; i < n_t; i++)
	{
		for (int j = 0; j < n_t; j++) 
    	{
        	m_tmp[i][j] += mt[i][j];
    	}
	}

	return *this = m_tmp;
}


template<typename T>
Matrix<T> & Matrix<T>::operator-=(const Matrix<T> & mt)
{
	if (n_t != mt.n_t)
	{
		throw std::logic_error("Incorrect size for operator -=");
	}

	return *this += (-mt);
}


template<typename T>
Matrix<T> & Matrix<T>::operator*=(const Matrix<T> & mt)
{
	if (n_t != mt.get_n())
	{
		throw std::logic_error("Incorrect size for operator *=");
	}

	Matrix<T> result(n_t);

	result.zero();

	for (int i = 0; i < n_t; i++)
	{
		for (int j = 0; j < n_t; j++) 
    	{
    		for (int k = 0; k < n_t; k++)
    		{
    			result[i][j] += ((*this)[i][k] * mt[k][j]);
    		}
    	}
	}

	return *this = result;
}


//-----------------------------Template methods----------------------------------

template<typename T>
	template<typename U>
	Matrix<T> Matrix<T>::operator*(U elem) const
	{
		Matrix<T> result((*this));

		return result *= elem;
	}



template<typename T>
	template<typename U>
	Matrix<T> & Matrix<T>::operator*=(U elem)
	{
		for (int i = 0; i < n_t; i++)
		{
			for (int j = 0; j < n_t; j++) 
	    	{
	        	matrix[i][j] *= elem;
	    	}
		}

		return *this;
	}



//---------------------------Operators outside the class---------------------------


template<typename T, typename U>
Matrix<T> operator*(U elem, const Matrix<T> & mt)
{
	Matrix<T> result(mt);

	return result *= elem;
}


template<typename T>
Matrix<T> operator+(const Matrix<T> & left, const Matrix<T> & right)
{
	if (left.get_n() != right.get_n())
	{
		throw std::logic_error("Incorrect size for operator +");
	}

	Matrix<T> result(left);

	result += right;

	return result;
}


template<typename T>
Matrix<T> operator-(const Matrix<T> & left, const Matrix<T> & right)
{
	if (left.get_n() != right.get_n())
	{
		throw std::logic_error("Incorrect size for operator -");
	}

	return left + (-right);
}


template<typename T>
Matrix<T> operator-(const Matrix<T> & mt)
{
	int n = mt.get_n();

	Matrix<T> result(mt);

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++) 
    	{
        	result[i][j] = -result[i][j];
    	}
	}

	return result;
}


template<typename T>
Matrix<T> operator*(const Matrix<T> & left, const Matrix<T> & right)
{
	if (left.get_n() != right.get_n())
	{
		throw std::logic_error("Incorrect size for operator *");
	}

	Matrix<T> result(left);

	return result *= right;
}


//--------------------------------Friends-------------------------------



template<typename T>
std::istream & operator>>(std::istream & istr, Matrix<T> & mt)
{
	int n = mt.n_t;

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++) 
    	{
        	istr >> mt[i][j];
    	}
	}

	return istr;
}


template<typename T>
std::ostream & operator<<(std::ostream & ostr, const Matrix<T> & mt)
{
	int n = mt.get_n();

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
        {
            ostr << mt[i][j] << " ";
        }

        ostr << std::endl;
	}

	return ostr;      
}


//---------------------------------------------------------------------


#endif

