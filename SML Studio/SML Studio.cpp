// SML Studio.cpp: определяет точку входа для консольного приложения.
//
#include "stdafx.h"
#include <iostream>
using namespace std;
#include "postfixMath.h"

int main()
{
	setlocale(LC_ALL, "Rus");
	postfixMath post("1-2*(18-5)+6/3"); //"(66+22)*5-8/4"//-24
	post.convert();
	postfixMath post2("(66+22)*5-8/4"); //-4
	post2.convert();	

	system("pause");
    return 0;
}

