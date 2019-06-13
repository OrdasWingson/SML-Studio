#include "stdafx.h"
#include "postfixMath.h"






postfixMath::postfixMath(string mathWord):
	expression(mathWord)
{
	infix = mathWord;

}

postfixMath::~postfixMath()
{

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
}


void postfixMath::convertToPostfix()
{
	char symbol; //символ
	char stackSymb; //символ в стеке
	int i = 0; //итератор
	int ip = 0; //итератор постфикса
	infix = infix + ')'; //вносим скобку в ификснй массив для указания конца строки
	postfixStack.push('('); //вносим скобку в стек для указания конца стека

	while (!postfixStack.isStackEmpty())//пока стек не пуст
	{
		symbol = infix[i];//сохраняем первый символ в переменную
		
		if (isOperator(symbol))//если символ не оператор
		{
			if (symbol == '(')//если символ правая скобка
			{
				postfixStack.push(symbol);	//запихиваем символ	в стек		
			}
			else
			{
				postfixStack.pop(stackSymb); //выталкиваем символ из стека
				while (precedence(symbol, stackSymb) != -1)
				{
					postfixStack.pop(postfix[ip]);
					ip++;
				}
				postfixStack.push(stackSymb);
			}
		}
		else
		{
			postfix += infix[i];
			
		}


		i++;
	}

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

string postfixMath::getPostfix()
{
	return postfix;
}

