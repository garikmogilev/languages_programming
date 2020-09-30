#include "stdafx.h"

namespace LT							// таблица лексем
{
	LexTable Сreate(int size) 
	{

		LexTable lexTable;
		lexTable.maxsize = LT_MAXSIZE;
		lexTable.size = 0;
		lexTable.table = new Entry[LT_MAXSIZE];

		return lexTable;
	}

	Entry Create(char token, int count)
	{
		Entry entry;
		entry.lexema[0] = token;
		entry.lexema[1] = STR_ENDL;
		entry.sn = count;
		return entry;
	}

	void Add(LexTable* lextable, Entry entry) 
	{
		if (lextable->size > lextable->maxsize)
			throw ERROR_THROW(110);
		lextable->table[lextable->size++] = entry;
	}

	Entry GetEntry(LexTable& lextable, int n) 
	{
		if (n >= 0 && n < lextable.maxsize)
			return lextable.table[n];
	}
	
	void Delete(LexTable& lextable)
	{
		delete[] lextable.table;
		lextable.table = nullptr;

	}
}
