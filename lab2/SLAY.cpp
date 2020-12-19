#include "stdafx.h"

double ident(int i, int j) { return i == j; }

pair<matrix, matrix> B_C(const matrix& A)
{
	matrix B(A.get_n());
	matrix C(A.get_n(), A.get_n(), ident);

	for (int i = 0; i < B.get_n(); i++)
	{
		for (int j = i; j < B.get_n(); j++)
		{
			double sum = 0;
			for (int k = 0; k <= i - 1; k++) sum += B[j][k] * C[k][i];
			B[j][i] = A[j][i] - sum;

			if (i<B.get_n() - 1 && j>i)
			{
				sum = 0;
				for (int k = 0; k <= i - 1; k++) sum += B[i][k] * C[k][j];
				if (fabs(B[i][i]) < 1e-22) C[i][j] = (A[i][j] - sum) / 1e-22;
				else C[i][j] = (A[i][j] - sum) / B[i][i];
			}
		}
	}

	return make_pair(move(B), move(C));
}

matrix decomp(const matrix& A, const matrix& b, const matrix& B, const matrix& C)
{
	matrix y(A.get_n(), 1);

	for (int i = 0; i < A.get_n(); i++)
	{
		double sum = 0;
		//���������� ������ y
		for (int k = 0; k < i; k++) sum += B[i][k] * y[k][0];
		if (fabs(B[i][i]) < 1e-22) y[i][0] = (b[i][0] - sum) / 1e-22;
		else y[i][0] = (b[i][0] - sum) / B[i][i];
	}

	cout << "y:" << endl << y << endl;

	matrix x(A.get_n(), 1);
	//���������� ������ x
	for (int i = A.get_n() - 1; i >= 0; i--)
	{
		double sum = 0;
		for (int k = i + 1; k < A.get_n(); k++) sum += C[i][k] * x[k][0];
		x[i][0] = y[i][0] - sum;
	}

	return x;
}

matrix inverse(const matrix& A)//�������� �������
{
	auto BC = B_C(A);
	matrix B = BC.first;
	matrix C = BC.second;
	
	matrix X(A.get_n());
	//���������� �������� �������
	for (int i = 0; i < A.get_n(); i++)
	{
		matrix e(A.get_n(), 1);
		e[i][0] = 1;

		matrix x = decomp(A, e, B, C);
		for (int j = 0; j < A.get_n(); j++) X[j][i] = x[j][0];
	}

	cout << "Inverse:" << endl << X << endl;

	matrix E(A.get_n(), A.get_n(), ident);//��������� �������
	matrix eps = A * X - E;//������� �������

	cout << "Eps:" << endl << scientific << eps << endl;
	cout << "Norm eps: " << eps.Norm() << endl;

	return X;
}

double decomp_det(const matrix& A)//������������
{
	auto BC = B_C(A);
	matrix C = BC.second;

	//���������� ������������ �������� �������
	double det = 1;
	for (int i = 0; i < C.get_n(); i++) det *= C[i][i];

	cout << "Det: " << det << endl;

	return det;
}

matrix decomposition(const matrix& A,const matrix& b)//����� ������������
{
	auto BC = B_C(A);
	matrix B = BC.first;//������� B
	matrix C = BC.second;//������� C

	cout << "B:" << endl << B << endl;
	cout << "C:" << endl << C << endl;

	matrix x = decomp(A,b,B,C);//������ ������� x
	cout << "X:" << endl << x << endl;

	matrix eps = A*x-b;//������ �������
	cout << "Eps:" << endl << scientific << eps << endl;
	cout << "Norm eps: " << eps.Norm() << endl;

	return x;
}
