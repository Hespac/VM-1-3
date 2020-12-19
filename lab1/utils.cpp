#include "pch.h"

void reader(int& method, char* s, double& a, double& b, double& eps)
{
	ifstream ff("input.txt");
	if (!ff.good()) throw "открытия файла";

	ff >> method;
	ff >> s;
	ff >> a;
	ff >> b;
	ff >> eps;

	cout
		<< "method: " << method << endl
		<< "Функция: " << s << endl
		<< "A, B: [" << a << ";" << b << ']' << endl
		<< "Eps: " << eps << endl;
}

void record(double o, double ex, double eps, char* s)
{
	ofstream file("output.txt");
	if (!file.good()) throw "открытия файла";

	file << fixed
		 << setprecision((int)-log10(eps));
		
	file << o << endl
		<< fabs(f(o, 0)) << endl
		 << scientific << ex << endl;
}
