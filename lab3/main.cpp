#include "stdafx.h"

void reader(int& m, matrix& A)
{
	ifstream f("input.txt");
	if (!f.good()) throw "File not found!";

	int n;
	f >> m >> n;

	A = matrix(n);
	for (int i = 0; i < n * n; i++) f >> A[i / n][i % n];
}

int main()
{
	int m;
	matrix A;

	reader(m, A);

	auto f = freopen("output.txt", "w", stdout);
	eigen_v(A, m);
	fclose(f);

	system("pause");
}
