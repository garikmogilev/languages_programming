#include "stdafx.h"

namespace IT
{
	IdTable Create(int size)
	{
		IdTable idtable;
		idtable.current_size = 0;
		idtable.maxsize = size;
		idtable.table = new Entry[size];
		return idtable;
	}

	void Add(IdTable& idtable, Entry entry)
	{

		if (idtable.current_size < idtable.maxsize)
		{
			idtable.table[idtable.current_size] = entry;
			if (entry.iddatatype == IT::IDDATATYPE::INT)
				idtable.table[idtable.current_size].value.vint = TI_INT_DEFAULT;
			else if (entry.iddatatype == IT::IDDATATYPE::STR)
			{
				idtable.table[idtable.current_size].value.vint = TI_STR_DEFAULT;
				idtable.table[idtable.current_size].value.vstr->len = 0;
			}

			idtable.current_size++;
		}
		else
			throw ERROR_THROW(121);

	}

	Entry GetEntry(IdTable& idtable, int n)
	{
		if(n < idtable.current_size && n >= 0)
		return idtable.table[n];
	}

	int IsId(IdTable& idtable, char id[ID_MAXSIZE]) {
		for (size_t i = 0; i < idtable.current_size; i++)
		{
			if (strcmp(idtable.table[i].id, id) == 0)
				return i;
			else
				return LT_TI_NULLXDX;
		}
	}

	void Delete(IdTable& idtable) {
		delete[] idtable.table;
		idtable.table = nullptr;
	}
}