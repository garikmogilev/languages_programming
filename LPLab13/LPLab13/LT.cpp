#include "stdafx.h"
#define KEYWORDS "integer, string, function, declare, return, print"

namespace LT							// таблица лексем
{
	LexTable Сreate(int size) 
	{

		LexTable lexT;
		lexT.maxsize = LT_MAXSIZE;
		lexT.size = 0;
		Entry* table = new Entry[LT_MAXSIZE];
		return lexT;
	}

	void Add(LexTable& lextable, Entry entry) 
	{
		if (lextable.size > lextable.maxsize)
			throw ERROR_THROW(110);
		lextable.table[lextable.size++] = entry;
	}

	Entry GetEntry(LexTable& lextable, int n) 
	{
		if (n < lextable.maxsize && n >= 0)
			return lextable.table[n];
	}
	
	void Delete(LexTable& lextable)
	{
		delete[] lextable.table;
		lextable.table = nullptr;

	}
}
