#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <vector>

namespace std
{
	template<typename T>
	class matrix_t
	{
		private:
			std::vector<std::vector<T>> matrix;
			size_t nrows;
			size_t ncols;
		public:
			matrix_t();
			matrix_t(size_t _nrows, size_t _ncols);
			~matrix_t();
			vector<T>& operator[](size_t row);
			matrix_t operator*(matrix_t matrix1) const;
			inline size_t get_nrows() const {return nrows;}
			inline size_t get_ncols() const {return ncols;}
			void traverse(void (*)(size_t, size_t, T&));
			template<typename PARAM_T>void traverse(void (*fun)(size_t, size_t, T&, PARAM_T), PARAM_T param)
			{
				for(size_t i = 0; i < nrows; i++)
				{
					for(size_t j = 0; j < ncols; j++)
					{
						fun(i,j,(*this)[i][j],param);
					}
				}
			}
			//T& operator[][](T,T);
	};

	template<typename T>
	matrix_t<T>::matrix_t(){}

	template<typename T>
	matrix_t<T>::matrix_t(size_t _nrows, size_t _ncols) : matrix(_nrows, std::vector<T>(_ncols))
	{
		nrows = _nrows;
		ncols = _ncols;
	}

	template<typename T>
	matrix_t<T>::~matrix_t(){}

	template<typename T>
	vector<T>& matrix_t<T>::operator[](size_t row)
	{
		return matrix[row];
	}

	template<typename T>
	matrix_t<T> matrix_t<T>::operator*(matrix_t<T> matrix1) const
	{
		if(this->get_ncols() != matrix1.get_nrows())
		{
			throw 1;
		}

		matrix_t<T> product(this->nrows, matrix1.ncols);

		for(size_t cur_row = 0; cur_row < product.get_nrows(); cur_row++)
		{
			T dot_product;
			for(size_t cur_col = 0; cur_col < product.get_ncols(); cur_col++)
			{
				dot_product = 0;
				for(size_t i = 0; i < matrix1.get_nrows(); i++)
				{
					dot_product += this->matrix[cur_row][i] * matrix1[i][cur_col];
				}
				product[cur_row][cur_col] = dot_product;
			}
		}

		return product;
	}

	template<typename T>
	void matrix_t<T>::traverse(void (*fun)(size_t, size_t, T&))
	{
		for(size_t i = 0; i < nrows; i++)
		{
			for(size_t j = 0; j < ncols; j++)
			{
				fun(i,j,(*this)[i][j]);
			}
		}
	}

}

int main()
{
	std::ifstream stream("input.txt",std::ios_base::in);
	std::matrix_t<int> matrix[2];
	size_t nrows, ncols;

	for(char r = 0; r < 2; r++)
	{
		stream >> nrows >> ncols;
		matrix[r] = std::matrix_t<int>(nrows,ncols);
		matrix[r].traverse<std::ifstream&>
		(
			[](size_t i, size_t j, int& elem, std::ifstream & stream) -> void
			{
				stream >> elem;
			},
			stream
		);
	}

	try
	{
		std::matrix_t<int> product = matrix[0]*matrix[1];

		product.traverse
		(
			[](size_t i, size_t j, int& elem) -> void
			{
				if(j == 0)
				{
					std::cout << std::endl;
				}
				std::cout << elem << '|';
			}
		);
		std::cout << std::endl;
	}
	catch(...)
	{
		std::cout << "El numero de columnas de la primera matriz no es igual al numero de filas de la segunda matriz." << std::endl;
	}


	stream.close();
	return 0;
}
