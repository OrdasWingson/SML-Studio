#pragma once
class tableEntry
{
public:
	tableEntry();
	tableEntry(int,char,int);
	~tableEntry();
	int getSymbol();
	char getType();
	int getLockation();
private:
	int symbol; //��� ����������, ����� ������, ���������
	char type; //C-��������� L--����� ������ V-����������
	int lockation; //����� ������ ������
};

 