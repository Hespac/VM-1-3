#include "pch.h"

int main()
{
	setlocale(LC_ALL, "RUS");

	int method;
	char s[1024];
	double a, b;
	double eps;

	try
	{
		reader(method, s, a, b, eps);

		char *rs = CreatePolStr(s, 0);
		if (a >= b) throw "B должно быть больше A";

		switch (method)
		{
		case 0://Проверка всеми методами
			dichotomy(rs, a, b, eps);
			mhord(rs, a, b, eps);
			newton(rs, a, b, eps);
			mcombined(rs, a, b, eps);
			miteration(rs, a, b, eps);
			mgoldSec(rs, a, b, eps);
			break;
		case 1://Метод дихотомии
			dichotomy(rs, a, b, eps);
			break;
		case 2://Метод хорд
			mhord(rs, a, b, eps);
			break;
		case 3://Метод Ньютона
			newton(rs, a, b, eps);
			break;
		case 4://Комбинированный метод
			mcombined(rs, a, b, eps);
			break;
		case 5://Метод итераций
			miteration(rs, a, b, eps);
			break;
		case 6://Метод золотого сечения
			mgoldSec(rs, a, b, eps);
			break;
		default:
			throw "Недопустимый номер метода";
		}
	}
	catch (char* a) { cout << "Ошибка: " << a << endl; }
	catch (int b) { cout << "Ошибка номер: " << b << endl; }
	catch (...) { cout << "Непредвиденная ошибка" << endl; }

	system("pause");
}
