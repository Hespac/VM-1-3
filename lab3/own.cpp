#include "stdafx.h"

double ident(int i, int j) {return i==j;}

//значение полинома степени
double eval(const double* factor, int n, double x)
{
	double r=factor[n];
	for(int i=n-1; i>=0; i--) r = r*x+factor[i];
	return r;
}

//первая производная для полинома
double* deriv(const double* factor, int n)
{
	double* d = new double[n];
	for(int i=1; i<=n; i++) d[i-1] = i*factor[i];
	return d;
}

void check_val(const matrix& A, double v, int k)//Вывод кратности собственных чисел и векторов
{
	cout << left << "Собственные число: " << v << endl;
	cout << "Кратность: " << k << endl;
}

void find_check_vec(const matrix& A, double v, int k, const matrix& s)
{
	vector y(A.get_n());
	y[A.get_n()-1] = 1;
	double pow = 1;
	for(int j=A.get_n()-2; j>=0; j--)
	{
		pow *= v;
		y[j] = pow;
	}

	vector x = s*y;

	cout << left <<"Собственное число: " << v << endl;
	cout << "Cобственный вектор: " << endl << x << endl;
	cout << "Кратность: " << k << endl;
}

//нахождение собственных чисел и/или векторов
void eigen_v(const matrix& A, int m)
{
	matrix A1 = A;
	matrix P; //матрица Фробениуса
	matrix S(A.get_n(),ident); //произведение всех матриц М
	matrix S1(A.get_n(),ident);
	 
	for(int k=A.get_n()-2; k>=0; k--)
	{
		//матрица М
		matrix M(A.get_n(),ident);
		for(int j=0; j<A.get_n(); j++)
			M[k][j] = -A1[k+1][j]/A1[k+1][k];
		M[k][k] = 1/A1[k+1][k];

		//матрица М1 (обратная для M)
		matrix M1(A.get_n(), ident);
		for(int j=0; j<A.get_n(); j++) M1[k][j] = A1[k+1][j];

		S*=M;
		S1=M1*S1;
		A1 = M1*A1*M;
	}

	P=S1*A*S;
	cout << "Матрица Фробениуса:" << endl << left << P << endl;

	//полином
	double* arr = new double[A.get_n()+1];
	for(int i=0; i<A.get_n(); i++) 
		if(A.get_n()%2==0) arr[i] = - P[0][A.get_n()-i-1];
		else arr[i] =  P[0][A.get_n()-i-1];
	arr[A.get_n()] = (A.get_n()%2==0) ? 1 : -1;

	//собственные числа/вектора
	double eps = 1e-5, pred = -10, delta = 1e-4;
	int sum = 0;
	for(double l = pred; l<10 && sum<A.get_n(); l+=eps) {
		if(fabs(eval(arr,A.get_n(),l)) < delta) {
			pred = l;
			while(fabs(eval(arr,A.get_n(),l+eps)) < delta) l+=eps;
			double ll = (l+pred)/2.0;
			int k=1;
			double* ptr;
			for(ptr = deriv(arr,A.get_n()); fabs(eval(ptr,A.get_n()-k,ll))<delta; k++)
			{
				double* p = ptr;
				ptr = deriv(ptr,A.get_n()-k);
				delete[] p;
			}
			delete [] ptr;
			sum+=k;
			if(m==1) check_val(A,ll,k);
			else find_check_vec(A,ll,k,S);
		}
	}

	delete[] arr;
}
