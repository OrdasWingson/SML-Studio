#pragma once
class tableEntry
{
public:
	tableEntry();
	~tableEntry();
private:
	int symbol; //��� ����������, ����� ������, ���������
	char type; //C-��������� L--����� ������ V-����������
	int lockation; //����� ������ ������
};

