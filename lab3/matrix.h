#pragma once

#include <iostream>

using namespace std;

class matrix {
	protected:
		double* arr; //указатель на начало матрицы
		int n,m;
		int ind; //индивидуальный номер
		static int count; //счётчик
	public:
		matrix();
		matrix(int,int,const double* =NULL);
		explicit matrix(int,const double* =NULL);
		matrix(int,int,double(*)(int,int));
		matrix(int,double(*)(int,int));
		matrix(const matrix&);
		~matrix();
		int get_n() const;
		int get_m() const;
		int get_ind() const;
		bool isMultable(const matrix&) const;
		bool isSumable(const matrix&) const;
		double norm() const;
		double max_elem() const; 
		double min_elem() const;
		matrix& operator = (const matrix&); 
		matrix& operator += (const matrix&);
		matrix& operator -= (const matrix&);
		matrix& operator *= (double);
		matrix& operator *= (const matrix&);
		const double* operator [] (int) const;
		double* operator [] (int);
		virtual bool is_matrix() const; //
		bool matr_is_vec() const;
		friend ostream& operator << (ostream&, const matrix&);

	};

//прототипы внешних функций
matrix operator + (const matrix&,const matrix&);
matrix operator - (const matrix&,const matrix&);
matrix operator * (const matrix&,double);
matrix operator * (double,const matrix&);
matrix operator * (const matrix&,const matrix&);

class Exception
{
public:
	const char* message;
	int id, id2;
	Exception(const char *str, int _id1, int _id2 = 0) : message(str), id(_id1), id2(_id2) {}
};