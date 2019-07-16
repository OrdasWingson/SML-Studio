#ifndef COMPILER_H
#define COMPILER_H

#include <string>
using std::string;
#include <list>
using std::list;
#include "tableEntry.h"

#define NUMBER_OF_COMAND 7

class compiler
{
public:
	compiler(string);
	~compiler();
	void start();

private:
	int flags[1000]; //флаги для провекри прохода по коду
	string fPath; //пуль к файлу
	list<tableEntry> symbolTable; //таблица символов
	int varItter; //итератор для переменных
	int comandItter;//итератор для команд 
	int Sml[1000]; //код SML
	char * comandName[NUMBER_OF_COMAND] = {"rem", "input", "let", "print", "goto", "if", "end"}; //перечисление команд

	void handleCode(string); //обработчик строк
	void saveCode(); //СОХРАНЕНИЕ в файле результатов обработчика
	void compilation(char*, bool&); //функция компиляции, второй аргумент является флагом показывающим является ли токен номером строки(1-is line number)
	bool equalSymbols(int); //поиск совпадений по таблице символов
	int getSymbLockation(int); //получение номера памяти символа
};

#endif