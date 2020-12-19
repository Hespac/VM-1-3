#pragma once
#include "stdafx.h"
#include <iostream>
using namespace std;

class matrix {
	private:
		double* arr; //указатель на начало матрицы
		int n,m;
		static int count; //счётчик
		int ind; //индивидуальный номер
	public:
		matrix();
		matrix(int,int,const double* =NULL);
		matrix(int,int,double(*)(int,int));
		explicit matrix(int,const double* =NULL);
		matrix(const matrix&);
		~matrix(); 
		int get_n() const;
		int get_m() const;
		bool isMultable(const matrix&) const; 
		bool isSumable(const matrix&) const;
		double max_elem() const;
		double min_elem() const;
		matrix& operator = (const matrix&); 
		matrix& operator += (const matrix&);
		matrix& operator -= (const matrix&);
		matrix& operator *= (double);
		matrix& operator *= (const matrix&);
		const double* operator [] (int) const;
		double* operator [] (int);
		double Norm() const 
		{
			double num = 0;
			for(int i = 0; i < n*m; i++) num += arr[i]*arr[i];
			return sqrt(num);
		}

		//прототипы дружественных функций
		friend ostream& operator << (ostream&, const matrix&);
		friend matrix operator + (const matrix&,const matrix&);
		friend matrix operator - (const matrix&,const matrix&);
		friend matrix operator * (const matrix&,double);
		friend matrix operator * (double,const matrix&);
		friend matrix operator * (const matrix&,const matrix&);
	};
class Exception
	{
	public:
		const char* message;
		int id;
		int id2;	
		Exception(const char *str, int _id1, int _id2 = 0) : message(str), id(_id1), id2(_id2) {}
	};