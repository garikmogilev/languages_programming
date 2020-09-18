#include "stdafx.h"
#define KEYWORDS "integer, string, function, declare, return, print"

namespace LT							// таблица лексем
{
	LexTable Сreate(int size) {

		LexTable lex;
		lex.maxsize = LT_MAXSIZE;
		lex.size = size;
		Entry* table;
		return lex;
	}

	void Add(LexTable& lextable, Entry entry) {

	}
}