// SML Studio.cpp: определяет точку входа для консольного приложения.
// TODO числа с операцией разници заменить на отрицательные, операцию сменить на сложение.
//изменения нужны в функции сепарации в postfixMath.cpp

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
		
	}
	catch(char *str)
	{
		cout << str << endl;
		path = "C:\\Users\\Иван\\Desktop\\helloworld.txt"; 
	}
	
	
	compilerSML.start(path);
	system("pause");
    return 0;
}

