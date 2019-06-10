#pragma once
class tableEntry
{
public:
	tableEntry();
	~tableEntry();
private:
	int symbol; //имя переменной, номер строки, константа
	char type; //C-константа L--номер строки V-переменная
	int lockation; //номер ячейки памяти
};

