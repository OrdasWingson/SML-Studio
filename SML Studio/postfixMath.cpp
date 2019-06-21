#include "stdafx.h"
#include "postfixMath.h"
#include <iostream>
using std::cout;//������ �����






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
	char symbol; //������
	char stackSymb; //������ � �����
	int i = 0; //��������
	int ip = 0; //�������� ���������
	infix += ')'; //������ ������ � ������� ������ ��� �������� ����� ������
	postfixStack.push('('); //������ ������ � ���� ��� �������� ����� �����

	while (infix[i] !='\0')//���� ���� �� ���� !postfixStack.isStackEmpty()
	{
		symbol = infix[i];//��������� ������ ������ � ����������
		if (!isdigit(symbol)) //���� ������ �� �������� ������
		{
			postfix += ' ';
			
			if (symbol == '(')//���� ������ ����� ������
			{
				postfixStack.push(symbol);	//���������� ������	� ����	
				i++;
				continue;
			}
			if (symbol == ')')
			{
				while (isOperator(postfixStack.stackTop()) || postfixStack.stackTop() != '(') //���� ������ ���� ��������
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
					if (isOperator(postfixStack.stackTop())) //���� ������ ���� ��������
					{
						if (precedence(symbol, postfixStack.stackTop()) < 0) //���������� �� �������� ��������
						{
							postfixStack.pop(stackSymb); //������������ ���� �������� ����� ��� ������ �� ��������
							postfix += stackSymb; // ��������� � ��������
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
		postfixStack.pop(stackSymb); //������������ ���� �������� ����� ��� ������ �� ��������
		if (stackSymb == '(') continue;
		postfix += stackSymb; // ��������� � ��������
	}
	
	infixPtr = separator(postfix);

	int iter = 0;
	while (infixPtr[iter] != "\0")
	{
		cout << "\n " + infixPtr[iter];
		iter++;
	}
}



void postfixMath::solution()
{

}

//���������� �������� �� ������
bool postfixMath::isOperator(char symb)
{
	char sign[6] = "+-*/%";
	if (strchr(sign, symb) != 0)
		return true;
	else
		return false;
}

//����������� ��������
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
	string *operandArray = new string[equation.size()+1]; //������ ����������
	string separated = ""; 
	int iter = 0;
	for (int i = 0; i <= equation.size(); i++) //�������� �� ������������ �������
	{
		if (isdigit(equation[i])) //���� ������� - �����
		{
			separated += equation[i];	//��������� � ���������		
		}
		else
		{	
			if (separated != "") //���� ��������� �� ����
			{
				operandArray[iter] = separated; //��������� ����� � ���������
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

