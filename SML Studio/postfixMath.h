#ifndef POSTFIXMATH_H
#define POSTFIXMATH_H

#include "Stack.h"
#include <string>
using std::string;
#include <list>
using std::list;
#include"tableEntry.h"

class postfixMath
{
public:
	postfixMath();
	~postfixMath();
	int getAswer(string); //������������ ��� ��������� ������ ���������	
	string getPostfix(string);	//������������ ��� ��������� SML ���������
	bool isNumber(string); //������� �������� �������� �� ����� ������ ��� �������������� �����
	bool isOperator(char); // �������� �� ���������� ������	

private:
	const string expression; //���������
	string* postfixPtr; //��������� ��� �������� ������������� ���������
	string postfix;
	Stack<char> postfixStack; //���� ���������� �� ���������� � ����������� ���������
	Stack<int> solutionStack; //���� ��� ���������� ����������

	//��������������� �������

	string* convert(string); //������� �������� �� ���������� � �����������						 
	string* convertSml(string); //������� �������� �� ���������� � ����������� ��� ��������� SML �����
	int solution(string*);	
	int precedence(char, char); //��������� ����������� ������
	string* separator(string); //��������� �����
	bool is_integer(const string &); //�������� �������� �� ������ ������
	
};

#endif