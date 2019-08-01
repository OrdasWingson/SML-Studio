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
	int flags[BIT_NUMBER]; //����� ��� �������� ������� �� ����
	string fPath; //���� � �����
	list<tableEntry> symbolTable; //������� ��������
	int varItter; //�������� ��� ����������
	int comandItter;//�������� ��� ������ 
	int Sml[BIT_NUMBER]; //��� SML
	char * comandName[NUMBER_OF_COMAND] = {"rem", "input", "let", "if", "goto", "print", "end"}; //������������ ������

	void handleCode(string); //���������� �����
	void saveCode(string); //���������� � ����� ����������� �����������
	void compilation(char*, bool&); //������� ����������, ������ �������� �������� ������ ������������ �������� �� ����� ������� ������(1-is line number)
	bool equalSymbols(int); //����� ���������� �� ������� ��������
	bool equalSymbols(int, char); //����� ���������� �� ������� ��������
	int getSymbLockation(int); //��������� ������ ������ �������
	void printTable(); //
	void printArraySml();
	void secondHandlCode();//������ ������
	char* strToChr(string);
	void addToTable(char*);//���������� � ������� ��������
};

#endif