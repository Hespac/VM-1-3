#include "stdafx.h"
#include "SLAY.h"

void reader(int& m, matrix& A, matrix& b)
{
	ifstream f("input.txt");
	if (!f.good()) throw "File not found!";

	int n;
	f >> m >> n;

	A = matrix(n);
	b = matrix(n, 1);

	for (int i = 0; i < n * n; i++)
	{
		f >> A[i / n][i % n];
		if (i % n == n - 1) f >> b[i / n][0];
	}
}

int main()
{
	int m;
	matrix A, b;

	reader(m, A, b);

	auto f = freopen("output.txt", "w", stdout);

	switch (m)
	{
	case 1:
		decomposition(A,b);
		break;
	case 2:
		decomp_det(A);
		break;
	case 3:
		inverse(A);
		break;
	default:
		cout << "Error!";
		break;
	}

	if (f) fclose(f);

	system("pause");
}
