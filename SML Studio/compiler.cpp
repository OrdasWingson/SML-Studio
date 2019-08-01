#include "stdafx.h"

#include <iostream>
using std::cout;
using std::endl;
#include <iomanip>
using std::setw;
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


compiler::compiler() :
	 comandItter(0), varItter(999)
{
	for (int i = 0; i < 1000; i++)
	{
		flags[i] = -1;
	}

	
}

compiler::~compiler()
{
}



void compiler::start(string path)
{
	fPath = path;
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
		secondHandlCode();
		printTable();
		printArraySml();
		saveCode("C:\\Users\\����\\Desktop\\sml.sml");
	}
	fReader.close(); 
}

void compiler::handleCode(string stringOfCode)
{
	if(stringOfCode[stringOfCode.size() - 1] == '\r') //�������� �������
		stringOfCode.erase(stringOfCode.size()-1);
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
			case 0: //rem
			{
				break;
			}
			case 1: //input
			{
				Sml[comandItter] = 10 * BIT_NUMBER;
				
				word = strtok(NULL, " ");
				if (!equalSymbols(*word))
				{
					symbolTable.push_back(tableEntry(*word, 'V', varItter));
					Sml[comandItter] += varItter;
				}
				varItter--;
				comandItter++;
				break;
			}
			case 2: //let
			{
				postfixMath postfix;
				Stack<int> stack;
				
				int locationVarible = 0; //���������� ��� ������ ������ ���������� ��� ������������
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
				strtok(NULL, " "); //��������� ���� �����
				char* equation = strtok(NULL, "\r"); //�������� ��������� ������� �� �������� ����� ��� ���������� ���������
				char* postfixEquation = strToChr(postfix.getPostfix(equation));//�������� ����������� ���������
				/*cout << postfixEquation << " < - - - \n";*/
				/*��������� � ������� �������� ���������� �������*/		
				word = strtok(equation, " "); 		
				while (word != NULL) //���� ����� �� ����
				{
					addToTable(word);
					//if(postfix.isNumber(word))
					//{
					//	symbolTable.push_back(tableEntry(atoi(word), 'C', varItter)); //��������� � �������
					//	varItter--;
					//}
					//else 
					//{
					//	//������������������� ����������
					//	
					//}
					
					word = strtok(NULL, " ");					
				}
				
				word = strtok(postfixEquation, " "); //�������� ������������ ���������
				
				while (word != NULL) //������������ ���������
				{
					if (isalpha(*word))
					{
						stack.push(getSymbLockation(*word)); //���� ����� ���������� ��������� ��� � ����
					}
					else if (postfix.isNumber(word))
					{
						stack.push(getSymbLockation(atoi(word))); //���� ����� ����� ��������� � ����
					}
					else if(postfix.isOperator(*word))
					{
						//�������� ����� �������� � ���������� 
						string sign = "+*/-";
						int operatorSml = 0;
						for (int i = 0; i < sign.size(); i++)
						{
							if (*word == sign[i])
							{
								switch (i)
								{
								case 0: //��������
								{
									operatorSml = 30 * BIT_NUMBER;
									break;
								}
								case 1: //�������
								{
									operatorSml = 33 * BIT_NUMBER;
									break;
								}
								case 2: //���������
								{
									operatorSml = 32 * BIT_NUMBER;
									break;
								}
								case 3: //���������
								{
									operatorSml = 31 * BIT_NUMBER;
									break;
								}
								default:
									break;
								}
								break;
							}

						}

						int x;
						stack.pop(x);
						int y;
						stack.pop(y);
						//���� ����� �������� ����������� �� ����� � ������ ����������
						Sml[comandItter++] = 20 * BIT_NUMBER + y; //���������� ����� � �����������
						Sml[comandItter++] = operatorSml + x; //��������� �������� ��� �������������
						Sml[comandItter++] = 21 * BIT_NUMBER + varItter; //���������� �� ������������ � ������ ���������
						
					}
					word = strtok(NULL, " ");
				}
				Sml[comandItter++] = 20 * BIT_NUMBER + varItter; //���������� ����� � �����������
				Sml[comandItter++] = 21 * BIT_NUMBER + locationVarible; //��������� �������� ��� �������������
				varItter--;
				break;
			}
			case 3: //if
			{
				int addres; //����� ������ ��������
				char *operatorBool;
				word = strtok(NULL, " "); // �������� ������ ����������
				Sml[comandItter++] = 20 * BIT_NUMBER + getSymbLockation(*word); //��������� ��������� � ����������� (�������� �������� ������� ����������
				
				operatorBool = strtok(NULL, " "); //�������� ��������
				word = strtok(NULL, " ");// �������� ������ ����������

				if (!equalSymbols(*word)) //���� ��� ������� � ������� �� ��������� ���
				{
					addToTable(word);
				}

				Sml[comandItter++] = 31 * BIT_NUMBER + getSymbLockation(*word); //�������� ������ �� ������������

				word = strtok(NULL, " "); //����� �� ���������� goto
				addres = atoi(strtok(NULL, " ")); //�������� ������
				if (!equalSymbols(addres, 'L'))
				{
					flags[comandItter] = addres;
					addres = 0;
				}
				
				if (strcmp(operatorBool, "==") == 0) //�������� ��������
				{
					Sml[comandItter++] = 42 * BIT_NUMBER + addres; //���� ����
				}
				else if (strcmp(operatorBool, "<") == 0)
				{
					Sml[comandItter++] = 41 * BIT_NUMBER + addres; //���� �����
				}

				break;
			}
			case 4: //goto
			{
				int addres = atoi(strtok(NULL, " ")); //�������� ������
				if (!equalSymbols(addres, 'L'))
				{
					flags[comandItter] = addres;
					addres = 0;
				}
				Sml[comandItter++] = 40 * BIT_NUMBER + addres; //��������� �� ������
				break;
			}
			case 5: //print
			{
				word = strtok(NULL, " ");
				if (!equalSymbols(*word)) //���� ��� ������� � ������� �� ��������� ���
				{
					//�������������� ����������
				}
				Sml[comandItter++] = 11 * BIT_NUMBER + getSymbLockation(*word);

				break;
			}
			case 6: //end
			{
				Sml[comandItter++] = 43 * BIT_NUMBER;
				break;
			}
			default:
				break;
			}
			delete[] tokenOfCode;
			break;
		}
	}//����� for	
//******************************************************************************************************************************
	
}

void compiler::saveCode(string path)
{
	ofstream fWriter(path, ios::out | ios::binary);
	if (fWriter.is_open())
	{
		for (int i = 0; i < BIT_NUMBER; i++)
		{
			fWriter << Sml[i] << "\t";
		}
	}
	fWriter.close();
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

bool compiler::equalSymbols(int symb, char type)
{
	for (auto iter = symbolTable.begin(); iter != symbolTable.end(); iter++)
	{
		if (iter->getSymbol() == symb && iter->getType() == type)
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

void compiler::printTable()
{
	for (auto iter = symbolTable.begin(); iter != symbolTable.end(); iter++)
	{
		cout << "Symbol " << setw(4) << iter->getSymbol() << " Type " << iter->getType() << " Location " << iter->getLockation() <<"\n";
	}
	cout << "\n";
}

void compiler::printArraySml()
{
	for (int i = 1; i <= 1000; i++)
	{
		cout << setw(6) << Sml[i - 1] << "   ";
		if (i % 8 == 0)
		{
			cout << '\n';
		}
	}
	cout << "\n";
}

void compiler::secondHandlCode()
{
	for (int i = 0; i < BIT_NUMBER; i++)
	{
		if (flags[i] != -1)
		{
			Sml[i] += getSymbLockation(flags[i]);
		}
	}
}


char* compiler::strToChr(string str)
{
	char *tokenOfCode = new char[str.length() + 1]; //������� ���������� ���������
	strcpy(tokenOfCode, str.c_str()); //����������� string  � char
	tokenOfCode[str.size()] = '\0'; // don't forget the terminating 0
	return tokenOfCode;
}

void compiler::addToTable(char* symb)
{
	postfixMath postfix;
	if (postfix.isNumber(symb))
	{
		symbolTable.push_back(tableEntry(atoi(symb), 'C', varItter)); //��������� � �������
		Sml[varItter] = atoi(symb);
		varItter--;
	}
	else if (isalpha(*symb))
	{
		symbolTable.push_back(tableEntry(*symb, 'V', varItter)); //��������� � �������
		varItter--;
	}
	

}

