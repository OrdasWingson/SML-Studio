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
		string s; // сюда будем класть считанные строки
		int count = 1;//номер строки
		while (getline(fReader, s)) { // пока не достигнут конец файла класть очередную строку в переменную (s)
			//cout << s << endl; // и снова вывожу на экран но уже модифицированную строку (без записи ее в файл)
			if (s == "") continue;
			string sentece = std::to_string(count) + " " + s;
			handleCode(sentece); //передаем строку обработчику	
			count++;
		}
		secondHandlCode();
		printTable();
		printArraySml();
		saveCode(fPath);

	}
	fReader.close(); 
}

void compiler::handleCode(string stringOfCode)
{
	if(stringOfCode[stringOfCode.size() - 1] == '\r') //удаление каретки
		stringOfCode.erase(stringOfCode.size()-1);
	char *word;
	char *tokenOfCode = new char[stringOfCode.length() + 1]; //создаем символьный указатель
	strcpy(tokenOfCode, stringOfCode.c_str()); //конвертация string  в char
	word = strtok(tokenOfCode, " "); // разбиение строки на токены
//******************************************************************************************************************************
	int lockation; //для получения локации
	int lineNumber = atoi(word); 
	if (!equalSymbols(lineNumber)) //здесь идет запись строки
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
				
				int locationVarible = 0; //переменная для записи адреса переменной для присваивания
				word = strtok(NULL, " ");
				if (!equalSymbols(*word)) // если символ буква и его нет в таблице \\ && isalpha(*word)
				{
					symbolTable.push_back(tableEntry(*word, 'V', varItter)); //добавляем в таблицу
					locationVarible = varItter--;
					
				}
				else //если есть в таблице то берем ее локейшн
				{
					locationVarible += getSymbLockation(*word, 'V');
				}
				strtok(NULL, " "); //убирается знак равно
				char* equation = strtok(NULL, "\r"); //получаем выражение стоящее за символом равно для дальнейшей обработки
				char* postfixEquation = strToChr(postfix.getPostfix(equation));//получаем постфиксное вырожение
				cout << postfixEquation << " < - - - \n";
				/*добовляем в таблицу символов оставшиеся символы*/		
				word = strtok(equation, " "); 		
				while (word != NULL) //пока токен не пуст
				{
					addToTable(word);
					
					word = strtok(NULL, " ");					
				}
				
				word = strtok(postfixEquation, " "); //начинаем обрабатывать выражение
				
				while (word != NULL) //обрабатываем выражение
				{
					if (isalpha(*word))
					{
						stack.push(getSymbLockation(*word, 'V')); //если токен переменная добавляем его в стек
					}
					else if (postfix.isNumber(word))
					{
						stack.push(getSymbLockation(atoi(word),'C')); //если токен цифра добавляем в стек
					}
					else if(postfix.isOperator(*word))
					{
						//выясняем какой оператор в переменной 
						string sign = "+/*-";
						int operatorSml = 0;
						for (int i = 0; i < sign.size(); i++)
						{
							if (*word == sign[i])
							{
								switch (i)
								{
								case 0: //сложение
								{
									operatorSml = 30 * BIT_NUMBER;
									break;
								}
								case 1: //деление
								{
									operatorSml = 32 * BIT_NUMBER;
									break;
								}
								case 2: //умножение
								{
									operatorSml = 33 * BIT_NUMBER;
									break;
								}
								case 3: //вычитание
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
						//если токен оператор выталкиваем из стека и создам инструкции
						Sml[comandItter++] = 20 * BIT_NUMBER + y; //записываем адрес в аккамулятор
						Sml[comandItter++] = operatorSml + x; //совершаем операцию над аккомулятором
						Sml[comandItter++] = 21 * BIT_NUMBER + varItter; //записываем из аккамулятора в память результат
						
					}
					word = strtok(NULL, " ");
				}
				Sml[comandItter++] = 20 * BIT_NUMBER + varItter; //записываем адрес в аккамулятор
				Sml[comandItter++] = 21 * BIT_NUMBER + locationVarible; //совершаем операцию над аккомулятором
				varItter--;
				break;
			}
			case 3: //if
			{
				int addres; //адрес ячейки перехода
				char *operatorBool;
				word = strtok(NULL, " "); // получаем первую переменную				
				Sml[comandItter++] = 20 * BIT_NUMBER + getSymbLockation(*word); //добавляем переменую в аккомулятор (добавить проверку наличия переменной
				
				operatorBool = strtok(NULL, " "); //получаем операцию
				word = strtok(NULL, " ");// получаем вторую переменную				
				if (!equalSymbols(*word)) //если нет символа в таблице то добавляем его
				{
					addToTable(word); //ошибка при распозновании переменной и флага
				}

				Sml[comandItter++] = 31 * BIT_NUMBER + getSymbLockation(getNumbOfSymb(word)); //вычитаем символ из аккомулятора
				
				word = strtok(NULL, " "); //здесь мы пропускаем goto
				addres = atoi(strtok(NULL, " ")); //получаем адресс
				if (!equalSymbols(addres, 'F'))
				{
					flags[comandItter] = addres;
					addres = 0;
				}
				else
				{
					addres = getSymbLockation(addres, 'F');
				}
				
				if (strcmp(operatorBool, "==") == 0) //получаем операцию
				{
					Sml[comandItter++] = 42 * BIT_NUMBER + addres; //если ноль
				}
				else if (strcmp(operatorBool, "<") == 0)
				{
					Sml[comandItter++] = 41 * BIT_NUMBER + addres; //если минус
				}
				else if (strcmp(operatorBool, ">") == 0)
				{

				}

				break;
			}
			case 4: //goto
			{				
				int index = atoi(strtok(NULL, " ")); //получаем адресс
				if (!equalSymbols(index, 'F'))
				{
					flags[comandItter] = index;
					index = 0;
				}
				Sml[comandItter++] = 40 * BIT_NUMBER + getSymbLockation(index); //переходим по адресу
				break;
			}
			case 5: //print
			{
				word = strtok(NULL, " ");
				if (!equalSymbols(*word)) //если нет символа в таблице то добавляем его
				{
					//несуществующая переменная
				}
				Sml[comandItter++] = 11 * BIT_NUMBER + getSymbLockation(*word);

				break;
			}
			case 6: //end
			{
				Sml[comandItter++] = 43 * BIT_NUMBER;
				break;
			}
			case 7: //flag
			{
				word = strtok(NULL, " "); // получаем имя флага
				symbolTable.push_back(tableEntry(atoi(word), 'F', comandItter)); //добавляем в таблицу
				break;
			}
			case 8: //var
			{
				word = strtok(NULL, " "); // получаем имя переменной
				int varAdr = 0;
				if (!equalSymbols(*word))
				{
					varAdr = varItter--;
					symbolTable.push_back(tableEntry(*word, 'V', varAdr)); //добавляем в таблицу
				}
				else
				{
					varAdr = getSymbLockation(*word, 'V');
				}
				
				//доработать вар
				word = strtok(NULL, " "); //убираем равно
				word = strtok(NULL, " ");//получаем переменную
				if (isalpha(*word))
				{
					Sml[comandItter++] = 20 * BIT_NUMBER + getSymbLockation(*word, 'V');
					Sml[comandItter++] = 21 * BIT_NUMBER + varAdr;
				}
				else
				{
					Sml[varAdr] = atoi(word);
				}
				
				break;
			}
			case 9: //text
			{
				Sml[comandItter] = 13 * BIT_NUMBER + varItter;

				word = strtok(NULL, ";"); // получаем слово
				//здесь посимвольно добавляем данные
				int i = 0;
				while (word[i] != NULL)
				{
					Sml[varItter--] = word[i];
					i++;
				}
				Sml[varItter--] = 0;
				comandItter++;
				break;
			}
			default:
				break;
			}
			delete[] tokenOfCode;
			break;
		}
	}//конец for	
//******************************************************************************************************************************
	
}

void compiler::saveCode(string path)
{
	string newNemePath = path;
	int indx = newNemePath.find('.');
	newNemePath = newNemePath.substr(0, indx)+".SML";
	ofstream fWriter(newNemePath, ios::out | ios::binary);
	if (fWriter.is_open())
	{
		for (int i = 0; i < BIT_NUMBER; i++)
		{
			fWriter << Sml[i] << " ";
		}
		fWriter << "\0";
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

int compiler::getSymbLockation(int symb, char typ)
{
	for (auto iter = symbolTable.begin(); iter != symbolTable.end(); iter++)
	{
		if (iter->getSymbol() == symb && iter->getType() == typ)
		{
			return iter->getLockation();
		}
	}
	return 0;
}

void compiler::printTable()
{
	//cout << "Symbol " << setw(4) << iter->getSymbol() << " Type " << iter->getType() << " Location " << iter->getLockation() << "\n";
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

int compiler::getNumbOfSymb(char* symb)
{
	if (isalnum(*symb))
	{
		return atoi(symb);
	}
	else
	{
		return *symb;
	}
	return 0;
}

void compiler::secondHandlCode()
{
	for (int i = 0; i < BIT_NUMBER; i++)
	{
		if (flags[i] != -1)
		{
			Sml[i] += getSymbLockation(flags[i], 'F');
		}
		
	}
}


char* compiler::strToChr(string str)
{
	char *tokenOfCode = new char[str.length() + 1]; //создаем символьный указатель
	strcpy(tokenOfCode, str.c_str()); //конвертация string  в char
	tokenOfCode[str.size()] = '\0'; // don't forget the terminating 0
	return tokenOfCode;
}

void compiler::addToTable(char* symb)
{
	postfixMath postfix;
	if (postfix.isNumber(symb))
	{
		symbolTable.push_back(tableEntry(atoi(symb), 'C', varItter)); //добавляем в таблицу
		Sml[varItter] = atoi(symb);
		varItter--;
	}
	else if (isalpha(*symb))
	{
		symbolTable.push_back(tableEntry(*symb, 'V', varItter)); //добавляем в таблицу
		varItter--;
	}
	

}

