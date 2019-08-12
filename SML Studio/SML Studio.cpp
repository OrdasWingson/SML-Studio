// SML Studio.cpp: ���������� ����� ����� ��� ����������� ����������.
// TODO ����� � ��������� ������� �������� �� �������������, �������� ������� �� ��������.
//��������� ����� � ������� ��������� � postfixMath.cpp

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
		path = "C:\\Users\\����\\Desktop\\sml\\inc.sc"; //�����������
		//return 1;
	}
	compilerSML.start(path);
	return 0;
}

