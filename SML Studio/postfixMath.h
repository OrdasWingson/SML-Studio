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
	void convert(); //функция перехода из инфиксного в постфиксный
private:
	const string expression; //выражение
	string* infixPtr; //указатель для хранения сепарировного выражения - возможно не нужен
	string infix;
	string postfix;
	Stack<char> postfixStack; //стек обработкаи из инфиксного в постфиксное выражение
	Stack<int> solutionStack; //стек для вычисления результата

	//вспомогательные функции

	bool isOperator(char); // является ли оператором символ
	int precedence(char, char); //сравнение старшинства знаков
	string* separator(string); //сепаратор чисел
	bool is_integer(const string &); //проверка является ли строка числом
	//bool haveOlderOperator(); //проверка на наличие ставрших операторов
	
};

#endif