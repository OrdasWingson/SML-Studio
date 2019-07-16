#include "stdafx.h"

#include <iostream>
using std::cout;
using std::endl;
#include <string>
using std::getline;
using std::string;
using std::strtok;
#include <fstream>
using std::ofstream;
using std::ifstream;
using std::ios;

#include "compiler.h"
#include "postfixMath.h"


compiler::compiler(string path) :
	fPath(path), comandItter(0), varItter(999)
{
	for (int i = 0; i < 1000; i++)
	{
		flags[i] = -1;
	}

	
}

compiler::~compiler()
{
}



void compiler::start()
{
	ifstream fReader(fPath, ios::in | ios::binary);

	if (!fReader.is_open())
	{
		cout << "File is damaged\n";
	}
	else
	{
		string s; // ���� ����� ������ ��������� ������
		while (getline(fReader, s)) { // ���� �� ��������� ����� ����� ������ ��������� ������ � ���������� (s)
			cout << s << endl; // � ����� ������ �� ����� �� ��� ���������������� ������ (��� ������ �� � ����)
			handleCode(s); //�������� ������ �����������
		}
		
	}
	fReader.close(); 
}

void compiler::handleCode(string stringOfCode)
{
	char *word;
	char *tokenOfCode = new char[stringOfCode.length() + 1]; //������� ���������� ���������
	strcpy(tokenOfCode, stringOfCode.c_str()); //����������� string  � char
	word = strtok(tokenOfCode, " "); // ��������� ������ �� ������
//******************************************************************************************************************************
	int lockation; //��� ��������� �������
	int lineNumber = atoi(word); 
	if (!equalSymbols(lineNumber)) //����� ���� ������ ������
	{
		symbolTable.push_back(tableEntry(lineNumber, 'L', comandItter));
	}
	word = strtok(NULL, " ");
	for (int i = 0; i < NUMBER_OF_COMAND; i++) //
	{
		if (strcmp(comandName[i], word) == 0)
		{
			switch (i)
			{
			case 0:
			{
				return;
			}
			case 1: //input
			{
				Sml[comandItter] = 10 * 1000;
				
				word = strtok(NULL, " ");
				if (!equalSymbols(*word))
				{
					symbolTable.push_back(tableEntry(*word, 'V', varItter));
					Sml[comandItter] += varItter;
				}
				varItter--;
				comandItter++;
				return;
			}
			case 2:
			{
				postfixMath postfix;

				Sml[comandItter] = 20 * 1000; //���������� ������� ����������
				int locationVarible = 0;
				word = strtok(NULL, " ");
				if (!equalSymbols(*word)) // ���� ������ ����� � ��� ��� � ������� \\ && isalpha(*word)
				{
					symbolTable.push_back(tableEntry(*word, 'V', varItter)); //��������� � �������
					locationVarible = varItter--;
				}
				else //���� ���� � ������� �� ����� �� �������
				{
					locationVarible += getSymbLockation(*word);
				}
				strtok(NULL, " ");
				
				word = strtok(NULL, " ");
				while (word != NULL)
				{
					if (isalpha(*word))
					{
						Sml[comandItter] += getSymbLockation(*word);
						comandItter++;
					}
					word = strtok(NULL, " ");
				}


				//cout << "\nGet postfix-> " << postfix.getPostfix("12+x-2*x") << '\n' << '\n';

				return;
			}
			default:
				break;
			}			
		}
	}
	
//******************************************************************************************************************************
	delete[] tokenOfCode;
}

void compiler::saveCode()
{
	/*bool isLine = true;
	while (word != NULL) //���� ����� �� ����
	{
		compilation(word, isLine);
		cout << word << '\n';
		word = strtok(NULL, " "); //���������� ���������	
	}*/	
}


void compiler::compilation(char * tokken, bool &isLine)
{
//	int ggg;
//	if (isLine)
//	{
//		int lineNumber = atoi(tokken);
//		if (!equalSymbols(lineNumber, ggg))
//		{
//			symbolTable.push_back(tableEntry(lineNumber,'L', comandItter));
//		}
//		isLine = false;
//	}
//	else
//	{		
//		for (int i = 0; i < NUMBER_OF_COMAND; i++) //
//		{
//			if (strcmp(comandName[i], tokken) == 0 )
//			{
//				switch (i)
//				{
//				case 0:
//				{
//					return;
//				}
//				case 1:
//				{
//					Sml[comandItter] = 10 * 1000;
//				}
//				default:
//					break;
//				}
//				return;
//			}						
//		}
//		if (!equalSymbols(*tokken, ggg))
//		{
//			symbolTable.push_back(tableEntry(*tokken, 'V', varItter));
//		}
//
//
//	}
//
}

bool compiler::equalSymbols(int symb)
{
	for (auto iter = symbolTable.begin(); iter != symbolTable.end(); iter++)
	{
		if (iter->getSymbol() == symb)
		{
			return true;
		}
	}
	return false;
}

int compiler::getSymbLockation(int symb)
{
	for (auto iter = symbolTable.begin(); iter != symbolTable.end(); iter++)
	{
		if (iter->getSymbol() == symb)
		{
			return iter->getLockation();
		}
	}
	return 0;
}

