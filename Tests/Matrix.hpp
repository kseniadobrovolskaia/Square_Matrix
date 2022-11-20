#ifndef MATRIX_H
#define MATRIX_H


#include <iostream>
#include <cmath>
#include <fstream>


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
		T operator[](int n) const{ return row[n];}
		T & operator[](int n) { return row[n];}
	};
	struct Row* matrix;
	

public:
	Matrix(int n = 2);
	Matrix(const Matrix<T> & mt);
	Matrix<T> & operator=(const Matrix<T> & mt);
	~Matrix();

	Row operator[](int n) const { return matrix[n];}
	Row & operator[](int n) { return matrix[n];}

	int get_n() const { return n_t;};
	T det();
	Matrix<T> & trans();
	bool is_zero(const T elem) const {return (elem > -ACCURACY) && (elem < ACCURACY);}
	void swap_rows(int n, int k, int first_col);
	
	Matrix<T> operator+(const Matrix<T> & mt) const;
	Matrix<T> & operator+=(const Matrix<T> & mt);
	Matrix<T> operator-(const Matrix<T> & mt) const;
	Matrix<T> & operator-=(const Matrix<T> & mt);
	Matrix<T> operator-() const;
	Matrix<T> operator*(const Matrix<T> & mt) const;
	Matrix<T> & operator*=(const Matrix<T> & mt);
	bool operator==(const Matrix<T> & mt);


	template<typename U>
	Matrix<T> operator*(U elem) const;
	template<typename U>
	Matrix<T> & operator*=(U elem);
	

	friend std::ostream & operator<< <T>(std::ostream & ostr, const Matrix<T> & mt);
	friend std::istream & operator>> <T>(std::istream & istr, Matrix<T> & mt);
	
};


template<typename T>
Matrix<T>::Matrix(int n): n_t(n)
{
	matrix = new struct Row[n];
	for (int i = 0; i < n; i++)
	{
		matrix[i].row = new T[n];
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
	matrix = new struct Row[n_t];

	for (int i = 0; i < n_t; i++)
	{
		matrix[i].row = new T[n_t];

		for (int j = 0; j < n_t; j++)
		{
			matrix[i].row[j] = mt.matrix[i].row[j];
		}
	}
}


template<typename T>
Matrix<T> & Matrix<T>::operator=(const Matrix<T> & mt)
{
	if (*this == mt)
	{
		return *this;
	}

	for (int i = 0; i < n_t; i++)
	{
		delete [] matrix[i].row;
	}
	delete [] matrix;

	n_t = mt.n_t;

	matrix = new struct Row[n_t];

	for (int i = 0; i < n_t; i++)
	{
		matrix[i].row = new T[n_t];

		for (int j = 0; j < n_t; j++)
		{
			matrix[i].row[j] = mt.matrix[i].row[j];
		}
	}

	return *this;
}


template<typename T>
bool Matrix<T>::operator==(const Matrix<T> & mt)
{
	if (n_t != mt.n_t)
	{
		return 0;
	}

	for (int i = 0; i < n_t; i++)
	{
		for (int j = 0; j < n_t; j++)
		{
			if (matrix[i].row[j] != mt.matrix[i].row[j])
			{
				return 0;
			}
		}
	}

	return 1;
}


template<typename T>
T Matrix<T>::det()
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
		for (int i = k + 1; i < n_t; i++)
		{
			for (int j = k + 1; j < n_t; j++)
			{
				if (Matrix<T>::is_zero(znam))
				{
					sign++;
					int n = k;

					while (Matrix<T>::is_zero(M[n][k]))
					{
						if (n-1 == n_t)
						{
							return 0;
						}
						n++;
					}
					M.swap_rows(n, k-1, 0);
					
				}
				
				if (k != 0)
				{
					znam = M[k-1][k-1];
				}

				M[i][j] = (M[i][j]*M[k][k] - M[i][k]*M[k][j]) / znam;
				
			}
		}
	}

	if (sign % 2 == 0)
	{
		return -M[n_t - 1][n_t - 1];
	}

	return M[n_t - 1][n_t - 1];
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
void Matrix<T>::swap_rows(int n, int k, int first_col)
{
	T elem;

	for (int col = first_col; col < n_t; col++)
	{
		elem = matrix[n][col];
		matrix[n][col] = matrix[k][col];
		matrix[k][col] = elem;
	}
}


//----------------------------------Operators---------------------------


template<typename T>
Matrix<T> Matrix<T>::operator+(const Matrix<T> & mt) const
{
	Matrix<T> result(n_t);

	if (n_t != mt.get_n())
	{
		std::cout << "Incorrect size for operator +" << std::endl;
		return result;
	}

	for (int i = 0; i < n_t; i++)
	{
		for (int j = 0; j < n_t; j++) 
    	{
        	result[i][j] = matrix[i][j] + mt[i][j];
    	}
	}

	return result;
}


template<typename T>
Matrix<T> & Matrix<T>::operator+=(const Matrix<T> & mt)
{

	if (n_t != mt.get_n())
	{
		std::cout << "Incorrect size for operator +=" << std::endl;
		return *this;
	}

	for (int i = 0; i < n_t; i++)
	{
		for (int j = 0; j < n_t; j++) 
    	{
        	matrix[i][j] += mt[i][j];
    	}
	}

	return *this;
}


template<typename T>
Matrix<T> Matrix<T>::operator-(const Matrix<T> & mt) const
{
	Matrix<T> result(n_t);

	if (n_t != mt.get_n())
	{
		std::cout << "Incorrect size for operator -" << std::endl;
		return result;
	}

	for (int i = 0; i < n_t; i++)
	{
		for (int j = 0; j < n_t; j++) 
    	{
        	result[i][j] = matrix[i][j] - mt[i][j];
    	}
	}

	return result;
}


template<typename T>
Matrix<T> & Matrix<T>::operator-=(const Matrix<T> & mt)
{

	if (n_t != mt.get_n())
	{
		std::cout << "Incorrect size for operator -=" << std::endl;
		return *this;
	}

	for (int i = 0; i < n_t; i++)
	{
		for (int j = 0; j < n_t; j++) 
    	{
        	matrix[i][j] -= mt[i][j];
    	}
	}

	return *this;
}


template<typename T>
Matrix<T> Matrix<T>::operator-() const
{
	Matrix<T> result(n_t);

	for (int i = 0; i < n_t; i++)
	{
		for (int j = 0; j < n_t; j++) 
    	{
        	result[i][j] = -matrix[i][j];
    	}
	}

	return result;
}


template<typename T>
Matrix<T> Matrix<T>::operator*(const Matrix<T> & mt) const
{
	Matrix<T> result(n_t);

	if (n_t != mt.get_n())
	{
		std::cout << "Incorrect size for operator *" << std::endl;
		return result;
	}

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

	return result;
}


template<typename T>
Matrix<T> & Matrix<T>::operator*=(const Matrix<T> & mt)
{
	*this = Matrix<T>(n_t);

	if (n_t != mt.get_n())
	{
		std::cout << "Incorrect size for operator *=" << std::endl;
		return *this;
	}

	for (int i = 0; i < n_t; i++)
	{
		for (int j = 0; j < n_t; j++) 
    	{
    		for (int k = 0; k < n_t; k++)
    		{
    			(*this)[i][j] += ((*this)[i][k] * mt[k][j]);
    		}
    	}
	}

	return *this;
}


//-----------------------------Template methods----------------------

template<typename T>
	template<typename U>
	Matrix<T> Matrix<T>::operator*(U elem) const
	{
		Matrix<T> result(n_t);

		for (int i = 0; i < n_t; i++)
		{
			for (int j = 0; j < n_t; j++) 
	    	{
	        	result[i][j] = matrix[i][j] * elem;
	    	}
		}

		return result;
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


//--------------------------------Friends-------------------------------



template<typename T>
std::istream & operator>>(std::istream & istr, Matrix<T> & mt)
{
	int n;
	istr >> n;

	if (n < 0)
	{
		std::cout << "Wrong matrix size" << std::endl;
		mt = Matrix<T>(0);
		return istr;
	}

	mt = Matrix<T>(n);

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
	int n = mt.n_t;

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

template<typename T, typename U>
Matrix<T> operator*(U elem, const Matrix<T> & mt)
{
	Matrix<T> result(mt);
	result *= elem;

	return result;
}


template<typename T, typename U>
Matrix<T> & operator*=(U elem, const Matrix<T> & mt)
{
	return mt *= elem;
}


#endif


