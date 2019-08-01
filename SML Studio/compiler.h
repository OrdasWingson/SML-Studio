#ifndef COMPILER_H
#define COMPILER_H

#include <string>
using std::string;
#include <list>
using std::list;
#include "tableEntry.h"

#define NUMBER_OF_COMAND 7
#define BIT_NUMBER 1000

class compiler
{
public:
	compiler();
	~compiler();
	void start(string);

private:
	int flags[BIT_NUMBER]; //флаги для провекри прохода по коду
	string fPath; //пуль к файлу
	list<tableEntry> symbolTable; //таблица символов
	int varItter; //итератор для переменных
	int comandItter;//итератор для команд 
	int Sml[BIT_NUMBER]; //код SML
	char * comandName[NUMBER_OF_COMAND] = {"rem", "input", "let", "if", "goto", "print", "end"}; //перечисление команд

	void handleCode(string); //обработчик строк
	void saveCode(string); //СОХРАНЕНИЕ в файле результатов обработчика
	void compilation(char*, bool&); //функция компиляции, второй аргумент является флагом показывающим является ли токен номером строки(1-is line number)
	bool equalSymbols(int); //поиск совпадений по таблице символов
	bool equalSymbols(int, char); //поиск совпадений по таблице символов
	int getSymbLockation(int); //получение номера памяти символа
	void printTable(); //
	void printArraySml();
	void secondHandlCode();//второй проход
	char* strToChr(string);
	void addToTable(char*);//добавление в таблицу символов
};

#endif