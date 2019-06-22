#ifndef POSTFIXMATH_H
#define POSTFIXMATH_H

#include "Stack.h"
#include <string>
using std::string;

class postfixMath
{
public:
	postfixMath(string);
	~postfixMath();

	void solution();
	string getPostfix();	
	void convert(); //������� �������� �� ���������� � �����������
private:
	const string expression; //���������
	string* infixPtr; //��������� ��� �������� ������������� ��������� - �������� �� �����
	string infix;
	string postfix;
	Stack<char> postfixStack; //���� ���������� �� ���������� � ����������� ���������
	Stack<int> solutionStack; //���� ��� ���������� ����������

	//��������������� �������

	bool isOperator(char); // �������� �� ���������� ������
	int precedence(char, char); //��������� ����������� ������
	string* separator(string); //��������� �����
	bool is_integer(const string &); //�������� �������� �� ������ ������
	
};

#endif