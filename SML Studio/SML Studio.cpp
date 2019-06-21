// SML Studio.cpp: определяет точку входа для консольного приложения.
//
#include "stdafx.h"
#include <iostream>
using namespace std;
#include "postfixMath.h"

int main()
{
	setlocale(LC_ALL, "Rus");
	postfixMath post("1-2*(18-5)+3/3"); //"(66+22)*5-8/4"
	post.convert();
	cout << "-> " << post.getPostfix() << '\n';
	//postfixMath post2("1-2*(8-5)+3/3"); //-4
	//post2.convert();
	//cout << "-> " << post2.getPostfix() << '\n';
	
	//post.separator("(62+332)*15-128/24");

	system("pause");
    return 0;
}

