
#include <iostream>
#include "Header.h"
#include <stdlib.h>
#include <iterator>
#include <vector>
#include <algorithm>    // std::for_each
#include <stdio.h>    // std::for_each
#include<initializer_list>
using namespace std;

void set_pdataINITe(int sizeINIT, double* pdataINIT)
{
	cout << "Введите  вектор";
	for (int i = 0; i < sizeINIT; i++)
	{
		cin >> pdataINIT[i];
	}
	cout << endl;
}

int main()
{setlocale(LC_ALL, "ru");

	int szvec1;
	cout << "Введите размер 1 вектора" << endl;;
	cin >> szvec1;
	double* vec1massiv = new double[szvec1];
	set_pdataINITe(szvec1, vec1massiv);
	tlist<double> b(szvec1, vec1massiv);
	b.output();
	cout << endl;
	tlist<double> t{ 50,48949,194894,14894 };
	t.output();
	cout << endl;
}
