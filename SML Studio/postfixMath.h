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

	void convertToPostfix();
	string getPostfix();
	void convert();
private:
	const string expression;
	string infix;
	string postfix;
	Stack<char> postfixStack;

	//вспомогательные функции
	bool isOperator(char);
	int precedence(char, char);
};

#endif