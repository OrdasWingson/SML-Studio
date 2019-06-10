// SML Studio.cpp: определяет точку входа для консольного приложения.
//
#include "stdafx.h"
#include <iostream>
using namespace std;
#include "postfixMath.h"

int main()
{
	setlocale(LC_ALL, "Rus");
	/*postfixMath post("(6+2)*5-8/4");
	post.convert();
	cout << "-> " << post.getPostfix() << '\n';*/
	postfixMath post2("2-4*(10-1)");
	post2.convert();
	cout << "-> " << post2.getPostfix() << '\n';
	system("pause");
	
    return 0;
}

