#include "stdafx.h"
#include "compiler.h"


compiler::compiler()
{
	for (int i = 0; i < 1000; i++) {
		flags[i] = -1;
	}
}


compiler::~compiler()
{
}
