#include "stdafx.h"
#include "tableEntry.h"


tableEntry::tableEntry()
{
}

tableEntry::tableEntry(int symb, char tp, int lock) :
	symbol(symb), type(tp), lockation(lock)
{
}


tableEntry::~tableEntry()
{
}

int tableEntry::getSymbol()
{
	return symbol;
}

char tableEntry::getType()
{
	return type;
}

int tableEntry::getLockation()
{
	return lockation;
}
