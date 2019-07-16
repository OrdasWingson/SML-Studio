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
	int flags[1000]; //����� ��� �������� ������� �� ����
	string fPath; //���� � �����
	list<tableEntry> symbolTable; //������� ��������
	int varItter; //�������� ��� ����������
	int comandItter;//�������� ��� ������ 
	int Sml[1000]; //��� SML
	char * comandName[NUMBER_OF_COMAND] = {"rem", "input", "let", "print", "goto", "if", "end"}; //������������ ������

	void handleCode(string); //���������� �����
	void saveCode(); //���������� � ����� ����������� �����������
	void compilation(char*, bool&); //������� ����������, ������ �������� �������� ������ ������������ �������� �� ����� ������� ������(1-is line number)
	bool equalSymbols(int); //����� ���������� �� ������� ��������
	int getSymbLockation(int); //��������� ������ ������ �������
};

#endif