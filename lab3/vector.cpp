#include "stdafx.h"

vector :: vector()
{
}


vector :: vector(int size, double* ptr) : matrix(size,1,ptr)
{
}


vector :: vector(int size, double a ...) : matrix(size,1,&a)
{
}


vector :: vector(int size, double (* ptr)(int)) : matrix(size,1)
{
	for(int i=0; i<n; i++) arr[i]=ptr(i);
}

vector :: vector (const vector& v) : matrix(v)
{
}


vector :: vector (const matrix& o)
{
	*this = o;;
}

vector :: ~vector()
{
}

double vector :: operator[] (int i) const
{
	if(i<0 || i>=n) throw Exception("Index is very big!",ind);
	return arr[i];
}

double& vector :: operator[] (int i)
{
	if(i<0 || i>=n) throw Exception("Index is very big!",ind);
	return arr[i];
}

vector& vector :: operator = (const matrix& A)
{
	if(!A.matr_is_vec()) throw Exception("It is impossible to copy!",ind,A.get_ind());
	((matrix&)*this) = A;
	return *this;
}

bool vector :: is_matrix() const
{
	return false;
}