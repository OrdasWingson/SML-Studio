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
	int getAswer(string); //используется для получения ответа выражения	
	string getPostfix(string);	//используется для обработки SML выражения
	bool isNumber(string); //функция проверки является ли токен числом для действительных чисел
	bool isOperator(char); // является ли оператором символ	

private:
	const string expression; //выражение
	string* postfixPtr; //указатель для хранения сепарировного выражения
	string postfix;
	Stack<char> postfixStack; //стек обработкаи из инфиксного в постфиксное выражение
	Stack<int> solutionStack; //стек для вычисления результата

	//вспомогательные функции

	string* convert(string); //функция перехода из инфиксного в постфиксный						 
	string* convertSml(string); //функция перехода из инфиксного в постфиксный для кодировки SML языка
	int solution(string*);	
	int precedence(char, char); //сравнение старшинства знаков
	string* separator(string); //сепаратор чисел
	bool is_integer(const string &); //проверка является ли строка числом
	
};

#endif