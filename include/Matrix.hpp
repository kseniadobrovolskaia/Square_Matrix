#ifndef MATRIX_H
#define MATRIX_H


#include "Memory.hpp"


#define ACCURACY 1e-5


template<typename T> std::ostream & operator<<(std::ostream & ostr, const Matrix<T> & mt);
template<typename T> std::istream & operator>>(std::istream & istr, Matrix<T> & mt);


template<typename T>
class Matrix
{
	int n_t;
	Memory<T> matrix;
	

public:

	explicit Matrix(int n = 0): n_t(n), matrix(n){};

	Matrix(const Matrix<T> & mt): n_t(mt.n_t), matrix(mt.matrix){};
	Matrix<T> & operator=(const Matrix<T> & mt);
	Matrix(Matrix<T> && mt): n_t(mt.n_t), matrix(mt.matrix){ ~mt.matrix(); };
	Matrix<T> & operator=(Matrix<T> && mt);
	virtual ~Matrix() noexcept {};

	Memory<T>::Row operator[](int n) const { return matrix[n]; };
	Memory<T>::Row & operator[](int n) { return matrix[n]; };

	int get_n() const { return n_t;};
	T det();
	Matrix<T> & trans();
	Matrix<T> & zero();
	void swap_rows(int n, int k);
	

	Matrix<T> & operator+=(const Matrix<T> & mt);
	Matrix<T> & operator-=(const Matrix<T> & mt);
	Matrix<T> & operator*=(const Matrix<T> & mt);
	void swap(Matrix<T> & mt){ matrix.swap(mt.matrix); };
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
Matrix<T> & Matrix<T>::operator=(const Matrix<T> & mt)
{
	if (n_t != mt.n_t)
	{
		throw std::logic_error("You cannot use operator = for matrices of different sizes");
	}

	matrix = mt.matrix;

	return *this;
}


template<typename T>
Matrix<T> & Matrix<T>::operator=(Matrix<T> && mt)
{
	if (n_t != mt.n_t)
	{
		throw std::logic_error("You cannot use operator = for matrices of different sizes");
	}

	matrix = mt.matrix;
	~mt.matrix(); 

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
T Matrix<T>::det()
{
	Matrix<T> M(*this);
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

	for (int i = 0; i < n_t; i++)
	{
		std::fill(matrix[i].row, matrix[i].row + n_t, 0);
	}

	return *this;
}


template<typename T>
Matrix<T> & Matrix<T>::trans()
{
	for (int i = 0; i < n_t; i++)
	{
		for (int j = 0; j < i; j++)
		{
			std::swap(matrix[i][j], matrix[j][i]);
		}
	}

	return *this;
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
	char space;

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++) 
    	{
    		istr >> std::ws;

			istr >> mt[i][j];
			istr >> space;

			if (!std::isspace(space) || istr.fail())
		    {
		        throw std::logic_error("Invalid input");
		    }
    	}
	}

	while (space != '\n')
	{
		if (!isspace(space))
		{
			throw std::logic_error("Invalid input");
		}
		istr >> space;
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

