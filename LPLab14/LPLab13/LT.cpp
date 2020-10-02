#include "stdafx.h"

namespace LT							// ������� ������
{
	LexTable �reate(int size) 
	{

		LexTable lexTable;
		lexTable.maxsize = LT_MAXSIZE;
		lexTable.size = 0;
		lexTable.table = new Entry[LT_MAXSIZE];

		return lexTable;
	}

	Entry Create(char token, int count, int &idInIdTable)
	{
		Entry entry;
		entry.lexema[0] = token;
		entry.lexema[1] = STR_ENDL;
		entry.sn = count;

		if (token == LEX_ID) {
			entry.idxTI = idInIdTable;
		}
		else
			entry.idxTI = LT_TI_NULLXDX;

		return entry;
	}

	void Add(LexTable* lextable, Entry entry) 
	{
		if (lextable->size > lextable->maxsize)
			throw ERROR_THROW(110);
		lextable->table[lextable->size++] = entry;
	}
	void PrintTableLex(LexTable* lextable,wchar_t* out)
	{
		std::fstream fout(out, std::ios::out);
		int uqu = 0;
		fout.width(4);
		fout.setf(std::ios::left);
		fout << lextable->table[0].sn;
		for (size_t i = 0; i < lextable->size; i++)
		{
			if (uqu != lextable->table[i].sn) {
				fout << std::endl;
				fout.width(4);
				fout.setf(std::ios::left);
				fout << lextable->table[i].sn;
				uqu = lextable->table[i].sn;
			}
			fout << lextable->table[i].lexema;
			if (lextable->table[i].idxTI != LT_TI_NULLXDX)
				fout << "(" << lextable->table[i].idxTI << ")"; //�������
		}
		fout.close();
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
