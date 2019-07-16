#ifndef POSTFIXMATH_H
#define POSTFIXMATH_H

#include "Stack.h"
#include <string>
using std::string;

class postfixMath
{
public:
	postfixMath();
	~postfixMath();
	int getAswer(string);	
	string getPostfix(string);	
	
private:
	const string expression; //���������
	string* postfixPtr; //��������� ��� �������� ������������� ���������
	string postfix;
	Stack<char> postfixStack; //���� ���������� �� ���������� � ����������� ���������
	Stack<int> solutionStack; //���� ��� ���������� ����������

	//��������������� �������

	string* convert(string); //������� �������� �� ���������� � �����������
	int solution(string*);
	bool isOperator(char); // �������� �� ���������� ������
	int precedence(char, char); //��������� ����������� ������
	string* separator(string); //��������� �����
	bool is_integer(const string &); //�������� �������� �� ������ ������
	
};

#endif