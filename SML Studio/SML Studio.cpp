// SML Studio.cpp: определ€ет точку входа дл€ консольного приложени€.
// TODO числа с операцией разници заменить на отрицательные, операцию сменить на сложение.
//изменени€ нужны в функции сепарации в postfixMath.cpp

#include "stdafx.h"
#include <iostream>
using namespace std;
#include "postfixMath.h"
#include "compiler.h"

int main(int argc, char *argv[])
{
	setlocale(LC_ALL, "Rus");
	string path;
	compiler compilerSML;

	try 
	{
		if(argv[1] == NULL)
			throw "File Not Found";
		path = (argv[1]);
		compilerSML.start(path);		
		return 0;
		
	}
	catch(char *str)
	{
		cout << str << endl;
		path = "C:\\Users\\»ван\\Desktop\\sml\\inc.sc"; //диагностика
		//return 1;
	}
	compilerSML.start(path);
	return 0;
}

