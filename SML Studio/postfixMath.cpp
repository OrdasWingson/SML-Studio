#include "stdafx.h"
#include "postfixMath.h"
#include <iostream>
using std::cout;//убрать потом
#include <regex>
using std::regex_match;







postfixMath::postfixMath(string mathWord):
	expression(mathWord)
{
	infix = mathWord;

}

postfixMath::~postfixMath()
{
	delete[] infixPtr;

}

void postfixMath::convert()
{
	char symbol; //символ
	char stackSymb; //символ в стеке
	int i = 0; //итератор
	int ip = 0; //итератор постфикса
	infix += ')'; //вносим скобку в ификснй массив для указания конца строки
	postfixStack.push('('); //вносим скобку в стек для указания конца стека

	while (infix[i] !='\0')//пока стек не пуст !postfixStack.isStackEmpty()
	{
		symbol = infix[i];//сохраняем первый символ в переменную
		if (!isdigit(symbol)) //если символ не является цифрой
		{
			postfix += ' ';
			
			if (symbol == '(')//если символ левая скобка
			{
				postfixStack.push(symbol);	//запихиваем символ	в стек	
				i++;
				continue;
			}
			if (symbol == ')')
			{
				while (isOperator(postfixStack.stackTop()) || postfixStack.stackTop() != '(') //если символ знак операции
				{
					postfixStack.pop(stackSymb);
					postfix += stackSymb;
				}

				postfixStack.pop(stackSymb);
			}
			else 
			{
				while (true)
				{
					if (isOperator(postfixStack.stackTop())) //если символ знак операции
					{
						if (precedence(symbol, postfixStack.stackTop()) < 0) //сравниваем по иерархии операции
						{
							postfixStack.pop(stackSymb); //выталкивеаем если операция равна или больше по иерархии
							postfix += stackSymb; // добавляем в постфикс
						}
						else
						{
							postfixStack.push(symbol);
							break;
						}
					}
					else
					{
						postfixStack.push(symbol);
						break;
					}
				}
			}
		}
		else
		{
			postfix += symbol;
		}
		i++;
	}
	while (!postfixStack.isStackEmpty())
	{
		postfixStack.pop(stackSymb); //выталкивеаем если операция равна или больше по иерархии
		if (stackSymb == '(') continue;
		postfix += stackSymb; // добавляем в постфикс
	}
	
	infixPtr = separator(postfix);

	int iter = 0;
	while (infixPtr[iter] != "\0")
	{
		cout << "\n " + infixPtr[iter];
		iter++;
	}
	solution();
}


//функция вычисления результата
void postfixMath::solution()
{
	int iter = 0;
	string sign = "+-*/%";
	int operand;
	int x;
	int y;

	while (infixPtr[iter][0] != '\0')
	{
		if (is_integer(infixPtr[iter]))
		{			
			solutionStack.push(std::stoi(infixPtr[iter]));
		}
		else
		{
			solutionStack.pop(y);
			solutionStack.pop(x);
			for (int i = 0; i < sign.size(); i++)
			{
				if (infixPtr[iter][0] == sign[i])
				{
					operand = i;
					break;
				}
				
			}

			switch (operand)
			{
			case 0:
			{
				solutionStack.push(x + y);
				break;
			}
			case 1:
			{
				solutionStack.push(x - y);
				break;
			}
			case 2:
			{
				solutionStack.push(x * y);
				break;
			}
			case 3:
			{
				solutionStack.push(x / y);
				break;
			}
			default:
				break;
			}			
		}
		iter++;
	}
	cout << "\nsolution is " << solutionStack.stackTop() << "\n";
	
}

bool postfixMath::is_integer(const string & s)
{
	return regex_match(s, std::regex("-?[0-9]+([.][0-9]+)?"));
}

//определяет является ли цифрой
bool postfixMath::isOperator(char symb)
{
	char sign[6] = "+-*/%";
	if (strchr(sign, symb) != 0)
		return true;
	else
		return false;
}

//старшинство символов
int postfixMath::precedence(char symbOperation, char symbStack)
{
	string sign = "+-*/%";
	int hierarchyArray[] = { 0,0,1,1,2 };
	int symbOperationHeirarchy;
	int symbStackHeirarchy;



	for (int i = 0; i < sign.size(); i++)
	{
		if (symbOperation == sign[i])
		{
			symbOperationHeirarchy = hierarchyArray[i];
		}
		if (symbStack == sign[i])
		{
			symbStackHeirarchy = hierarchyArray[i];
		}
	}

	if (symbOperationHeirarchy < symbStackHeirarchy) return -1;
	if (symbOperationHeirarchy == symbStackHeirarchy) return 0;
	if (symbOperationHeirarchy > symbStackHeirarchy) return 1;

}

string* postfixMath::separator(string equation)
{
	string *operandArray = new string[equation.size()+1]; //массив указателей
	string separated = ""; 
	int iter = 0;
	for (int i = 0; i <= equation.size(); i++) //проходим по постфиксному массиву
	{
		if (isdigit(equation[i])) //если элемент - число
		{
			separated += equation[i];	//добавляем в сепаратор		
		}
		else
		{	
			if (separated != "") //если сепаратор не пуст
			{
				operandArray[iter] = separated; //добавляем число в указатель
				iter++;
			}
			
			separated = equation[i];
			if (separated != " ")
			{
				operandArray[iter] = equation[i];
				iter++;
			}	
			separated = "";
			
		}
	}

	return operandArray;
	
}

string postfixMath::getPostfix()
{
	return postfix;
}

