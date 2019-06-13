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
}


void postfixMath::convertToPostfix()
{
	char symbol; //������
	char stackSymb; //������ � �����
	int i = 0; //��������
	int ip = 0; //�������� ���������
	infix = infix + ')'; //������ ������ � ������� ������ ��� �������� ����� ������
	postfixStack.push('('); //������ ������ � ���� ��� �������� ����� �����

	while (!postfixStack.isStackEmpty())//���� ���� �� ����
	{
		symbol = infix[i];//��������� ������ ������ � ����������
		
		if (isOperator(symbol))//���� ������ �� ��������
		{
			if (symbol == '(')//���� ������ ������ ������
			{
				postfixStack.push(symbol);	//���������� ������	� ����		
			}
			else
			{
				postfixStack.pop(stackSymb); //����������� ������ �� �����
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

string postfixMath::getPostfix()
{
	return postfix;
}

