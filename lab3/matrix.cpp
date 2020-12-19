#include "stdafx.h"

int matrix :: count=0;

//констуктор по умолчанию
matrix :: matrix()
{
	m=0;
	n=0;
	arr=NULL;
	ind=++count;
}

//конструктор, инициализирующий прямоугольную матрицу
matrix :: matrix(int sizen, int sizem, const double* ptr)
{
	ind=++count;
	if(sizen<0 || sizem<0) throw Exception("Matrix size must be positiv!",ind);
	
	n=sizen; m=sizem;
	if(n==0 || m==0)
	{
		arr=NULL;
		n=m=0;
	}
	else arr = new double[n*m];

	for(int i=0; i<n*m; i++) arr[i]= ptr? ptr[i] : 0.0;
}

//конструктор, инициализирующий матрицу по вызванной функции
matrix :: matrix(int sizen, int sizem, double (* ptr)(int, int))
{
	ind=++count;
	if(sizen<0 || sizem<0) throw Exception("Matrix size must be positiv!",ind);
	
	n=sizen; m=sizem;
	if(n==0 || m==0)
	{
		arr=NULL;
		n=m=0;
	}
	else arr = new double[n*m];

	for(int i=0; i<n*m; i++) arr[i]= ptr(i/m,i%m);
}

//конструктор, инициализирующий квадратную матрицу
matrix :: matrix(int size, const double* ptr)
{
	ind=++count;
	if(size<0) throw Exception("Matrix size must be positiv!",ind);
	
	n=size; m=size;
	if(n==0) arr=NULL;
	else arr = new double[n*n];

	for(int i=0; i<n*n; i++) arr[i]= ptr? ptr[i] : 0.0;
}

//конструктор, инициализирующий матрицу по вызванной функции
matrix :: matrix(int size, double (* ptr)(int, int))
{
	ind=++count;
	if(size<0) throw Exception("Matrix size must be positiv!",ind);
	
	n = m = size;
	if(n==0 || m==0)
	{
		arr=NULL;
		n=m=0;
	}
	else arr = new double[n*m];

	for(int i=0; i<n*m; i++) arr[i]= ptr(i/m,i%m);
}

//конструктор копирования
matrix :: matrix (const matrix& mas)
{
	ind=++count;
	n=mas.n; m=mas.m;
	if(n>0 && m>0) arr = new double[n*m];
	else arr=NULL;

	for(int i=0; i<n*m; i++) arr[i]=mas.arr[i];
}

//деструктор
matrix :: ~matrix()
{
	if(arr != NULL) delete [] arr;
}

//получить количество строк и столбцов матрицы
int matrix :: get_n() const
{
	return n;
}
int matrix :: get_m() const
{
	if(!is_matrix()) throw Exception("It is impossible to get m!",ind);
	return m;
}
int matrix :: get_ind() const
{
	return ind;
}

//проверка на возможность умножения двух матриц
bool matrix :: isMultable(const matrix& A) const
{
	return (m==A.n);
}

//проверка на возможность умножения двух матриц
bool matrix :: isSumable(const matrix& A) const
{
	return (n==A.n) && (m==A.m);
}

//норма матрицы
double matrix :: norm() const 
{
	double num = 0;
	for(int i = 0; i < n*m; i++) num += arr[i]*arr[i];
	return sqrt(num);
}

//поиск максимального элемента
double matrix :: max_elem() const
{
	if (n==0) throw Exception("Matrix is empty!",ind);

	double max=arr[0];
	for(int i=0; i<n*m; i++) if(arr[i]>max) max=arr[i];
	return max;
}

//поиск минимального элемента
double matrix :: min_elem() const
{
	if (n==0 || m==0) throw Exception("Matrix is empty!",ind);

	double min=arr[0];
	for(int i=0; i<n*m; i++) if(arr[i]<min) min=arr[i];
	return min;
}

matrix& matrix :: operator = (const matrix& A)
{
	if(n*m!=A.n*A.m)
	{
		if(arr != NULL) delete [] arr;
		if (A.n>0 && A.m>0) arr = new double[A.n*A.m];
		else arr=NULL;
	}
	n=A.n; m=A.m;
	for(int i=0; i<n*m; i++) arr[i]=A.arr[i];
	return *this;
}

matrix& matrix :: operator += (const matrix& A)
{
	if(!isSumable(A)) throw Exception("It is impossible to sum!",ind,A.ind);
	for(int i=0; i<n*m; i++) arr[i]+=A.arr[i];
	return *this;
}

matrix& matrix :: operator -= (const matrix& A)
{
	if(!isSumable(A)) throw Exception("It is impossible to div!",ind,A.ind);
	for(int i=0; i<n*m; i++) arr[i]-=A.arr[i];
	return *this;
}

matrix& matrix :: operator *= (double sc)
{
	if (n==0) throw Exception("Matrix is empty!",ind);
	for(int i=0; i<n*m; i++) arr[i]*=sc;
	return *this;
}

matrix& matrix :: operator *= (const matrix& A)
{
	if (!isMultable(A)) throw Exception("It is impossible to mult!",ind,A.ind);
	matrix C = *this;
	if(arr != NULL) delete [] arr;
	m=A.m;
	arr = new double[n*m];
	for(int i=0; i<n; i++)
		for(int j=0; j<m; j++)
		{
			arr[i*m+j]=0;
			for(int k=0; k<A.n; k++) arr[i*m+j]+=C.arr[i*C.m+k]*A.arr[k*A.m+j];
		}
	return *this;

}

matrix operator + (const matrix& A, const matrix& B)
{
	matrix C=A;
	C += B;
	return C;
}

matrix operator - (const matrix& A, const matrix& B)
{
	matrix C=A;
	C-=B;
	return C;
}

matrix operator * (const matrix& A,double sc)
{
	matrix C=A;
	C*=sc;
	return C;
}
matrix operator * (double sc,const matrix& A)
{
	return A*sc;
}

matrix operator * (const matrix& A,const matrix& B)
{
	matrix C=A;
	C*=B;
	return C;
}

ostream & operator << (ostream& o, const matrix& A)
{
	streamsize w=o.width();
	if(!w) w=5;
	streamsize p=o.precision();
	if(!p) p=2;
	for(int i=0;i<A.n;i++,cout<<"\n")
		for(int j=0;j<A.m;j++) cout<<setw(w)<<setprecision(p)<<A.arr[i*A.m+j];
	return o;
}

const double* matrix :: operator [] (int i) const
{
	if(!is_matrix()) throw Exception("It is necessary to use other indexsation!",ind);
	if(arr==NULL || i>=n || i<0) throw Exception("Index is very big!",ind);
	return arr+i*m;
}

double* matrix :: operator [] (int i)
{
	if(!is_matrix()) throw Exception("It is necessary to use other indexsation!",ind);
	if(arr==NULL || i>=n || i<0) throw Exception("Index is very big!",ind);
	return arr+i*m;
}

bool matrix :: is_matrix() const
{
	return true;
}

bool matrix :: matr_is_vec() const
{
	return m<=1;
}