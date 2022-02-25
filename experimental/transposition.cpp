#include <stdio.h>
#include <stdlib.h>

void show_matrix(int ** matrix, size_t nrows, size_t ncols)
{
	putchar('\n');
	for(size_t i = 0; i < nrows; i++)
	{
		for(size_t j = 0; j < ncols; j++)
		{
			printf("%d|",*(*(matrix+i)+j));
		}
		putchar('\n');
	}
	putchar('\n');
}


void transposition_nxn(int ** matrix, size_t nxn)
{
	for(size_t i = 0; i < nxn; i++)
	{
		for(size_t j = i+1; j < nxn; j++)
		{
			int aux = matrix[i][j];
			matrix[i][j] = matrix[j][i];
			matrix[j][i] = aux;
		}
	}
}

void transposition(int ** &matrix, size_t &nrows, size_t &ncols)
{
	if(nrows == ncols)
	{
		transposition_nxn(matrix, nrows);
	}
	else
	{
		size_t new_nrows = ncols;
		size_t new_ncols = nrows;

		if(new_nrows > nrows)
		{
			matrix = (int**)realloc(matrix, sizeof(int*)*new_nrows);
			for(size_t i = nrows; i < new_nrows; i++)
			{
				matrix[i] = (int*)malloc(sizeof(int)*new_ncols);
			}
			transposition_nxn(matrix,new_nrows);
			for(size_t i = 0; i < new_nrows; i++)
			{
				matrix[i] = (int*)realloc(matrix[i],sizeof(int)*new_ncols);
			}
		}
		else
		{
			for(size_t i = 0; i < new_nrows; i++)
			{
				matrix[i] = (int*)realloc(matrix[i], sizeof(int)*new_ncols);
			}
			transposition_nxn(matrix,new_ncols);
			matrix = (int**)realloc(matrix,sizeof(int*)*new_nrows);
		}

		ncols = new_ncols;
		nrows = new_nrows;
	}
}


int main()
{
	FILE * stream = fopen("input.txt","r");
	int ** matrix;
	size_t nrows, ncols;

	fscanf(stream, "%u%u", &nrows, &ncols);

	matrix = (int**)malloc(sizeof(int*)*nrows);
	for(size_t i = 0; i < nrows; i++)
	{
		matrix[i] = (int*)malloc(sizeof(int)*ncols);;
		for(size_t j = 0; j < ncols; j++)
		{
			fscanf(stream, "%d", *(matrix+i)+j);
		}
	}

	transposition(matrix, nrows, ncols);

	show_matrix(matrix,nrows,ncols);

	for(size_t i = 0; i < nrows; i++)
	{
		free(matrix[i]);
	}
	free(matrix);

	fclose(stream);
	return 0;
}
