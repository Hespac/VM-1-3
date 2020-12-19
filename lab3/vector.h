#pragma once
#include "matrix.h"
class vector : public matrix {
	public:
		vector();
		explicit vector(int, double* =NULL);
		vector(int,double...);//конструктор для инициализации вектора заданного размера заданными значениями
		vector(int,double(*)(int));
		vector(const vector&);
		vector(const matrix&);
		~vector();
		double operator[] (int) const;
		double& operator[] (int);
		virtual bool is_matrix() const; //

		vector& operator = (const matrix&);
};


