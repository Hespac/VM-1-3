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


matrix :: matrix (const matrix& mas)
{
	ind=++count;
	n=mas.n; m=mas.m;
	if(n>0 && m>0) arr = new double[n*m];
	else arr=NULL;

	for(int i=0; i<n*m; i++) arr[i]=mas.arr[i];;
}


matrix :: ~matrix()
{
	if(arr != NULL) delete [] arr;
}


int matrix :: get_n() const
{
	return n;
}
int matrix :: get_m() const
{
	return m;
}


bool matrix :: isMultable(const matrix& A) const
{
	return (m==A.n);
}


bool matrix :: isSumable(const matrix& A) const
{
	return (n==A.n) && (m==A.m);
}


double matrix :: max_elem() const
{
	if (n==0) throw Exception("Matrix is empty!",ind);

	double max=arr[0];
	for(int i=0; i<n*m; i++) if(arr[i]>max) max=arr[i];
	return max;
}

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
			for(int k=0; k<A.n; k++) arr[i*m+j]+=C[i][k]*A[k][j];
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
	if (!A.isMultable(B)) throw Exception("It is impossible to mult",A.ind,B.ind);

	matrix C(A.n,B.m);
	for(int i=0; i<A.n; i++)
		for(int j=0; j<B.m; j++)
			for(int k=0; k<A.m; k++) C[i][j]+=A[i][k]*B[k][j];
	return C;
}

ostream & operator << (ostream& o, const matrix& A)
{
	streamsize w=o.width();
	streamsize p=o.precision();
	for(int i=0;i<A.n;i++,cout<<"\n")
		for(int j=0;j<A.m;j++) cout<<setw(w)<<setprecision(p)<<A[i][j]<<"\t";
	return o;
}

const double* matrix :: operator [] (int i) const
{
	if(arr==NULL || i>=n || i<0) throw Exception("Index is very big!",ind);
	return arr+i*m;
}

double* matrix :: operator [] (int i)
{
	if(arr==NULL || i>=n || i<0) throw Exception("Index is very big!",ind);
	return arr+i*m;
}

matrix operator& (const matrix& A,const matrix& B)
{
	if(A.get_n()!=B.get_n()) throw("It is impossible!\n");
	matrix C(A.get_n(),A.get_m()+B.get_m());
	for(int i=0; i<A.get_n(); i++)
		for(int j=0; j<A.get_m(); j++) C[i][j] = A[i][j];
	for(int i=0; i<B.get_n(); i++)
		for(int j=0; j<B.get_m(); j++) C[i][j+A.get_m()] = B[i][j];
	
	return C;
}