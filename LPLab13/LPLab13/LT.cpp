#include "stdafx.h"
#define KEYWORDS "integer, string, function, declare, return, print"

namespace LT							// ������� ������
{
	LexTable �reate(int size) {

		LexTable lex;
		lex.maxsize = LT_MAXSIZE;
		lex.size = size;
		Entry* table;
		return lex;
	}

	void Add(LexTable& lextable, Entry entry) {

	}
}