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
	const string expression; //выражение
	string* postfixPtr; //указатель для хранения сепарировного выражения
	string postfix;
	Stack<char> postfixStack; //стек обработкаи из инфиксного в постфиксное выражение
	Stack<int> solutionStack; //стек для вычисления результата

	//вспомогательные функции

	string* convert(string); //функция перехода из инфиксного в постфиксный
	int solution(string*);
	bool isOperator(char); // является ли оператором символ
	int precedence(char, char); //сравнение старшинства знаков
	string* separator(string); //сепаратор чисел
	bool is_integer(const string &); //проверка является ли строка числом
	
};

#endif