// SML Studio.cpp: определяет точку входа для консольного приложения.
// TODO числа с операцией разници заменить на отрицательные, операцию сменить на сложение.
//изменения нужны в функции сепарации в postfixMath.cpp

#include "stdafx.h"
#include <iostream>
using namespace std;
#include "postfixMath.h"

int main()
{
	setlocale(LC_ALL, "Rus");
	postfixMath post("1-2*(18-5)+6/3"); //"(66+22)*5-8/4"//-23
	post.convert();
	postfixMath post2("8/4-(15+3)*2"); //-34
	post2.convert();
	postfixMath post3("7-5+2-6+8-5-5+4+1"); //1 "5-4/4+2-2*(2-1+3)"-2
	post3.convert();

	system("pause");
    return 0;
}

