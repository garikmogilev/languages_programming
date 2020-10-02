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

			if (entry.idtype != IT::IDTYPE::L)
				if (entry.iddatatype == IT::IDDATATYPE::INT)
					idtable.table[idtable.current_size].value.vint = TI_INT_DEFAULT;
				else if (entry.iddatatype == IT::IDDATATYPE::STR)
				{
					idtable.table[idtable.current_size].value.vstr->len = TI_STR_DEFAULT;
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

	int IsId(IdTable& idtable, char id[ID_MAXSIZE + 1], char prefix[ID_MAXSIZE + 1]) {
		for (size_t i = 0; i < idtable.current_size; i++)
		{
			if (!strcmp(idtable.table[i].id, id))
				return i;
		}
		return LT_TI_NULLXDX;
	}

	int IsLiteral(IdTable& idtable, char* str) {
		for (size_t i = 0; i < idtable.current_size; i++)
		{
			if (!strcmp(idtable.table[i].value.vstr->str, str))
				return i;
		}
		return LT_TI_NULLXDX;
	}

	int IsLiteral(IdTable& idtable, int vint) {
		for (size_t i = 0; i < idtable.current_size; i++)
		{
			if (idtable.table[i].value.vint == vint)
				return i;
		}
		return LT_TI_NULLXDX;
	}

	void PrintIdTable(const wchar_t* out, IdTable& idtable)
	{
		std::fstream fout(out, std::ios::out);

		fout.setf(std::ios::left);
		fout.width(15); fout << "visible";
		fout.width(15);	fout << "variable"; \
		fout.width(15); fout << "type"; 
		fout.width(15); fout << "value int";
		fout.width(15); fout << "value str" << std::endl;

			for (size_t i = 0; i < idtable.current_size; i++)
			{
				if (idtable.table[i].idtype == IT::IDTYPE::V) {

					fout.width(15); fout << idtable.table[i].prefix;
					fout.width(15); fout << idtable.table[i].id;
					//fout.width(15); fout << idtable.table[i].extFunct;

					if (idtable.table[i].iddatatype == IT::IDDATATYPE::INT) {
						fout.width(15); fout << "integer ";
						fout.width(15); fout << idtable.table[i].value.vint;
						fout.width(15); fout << "-";
					}
					if (idtable.table[i].iddatatype == IT::IDDATATYPE::STR) {
						fout.width(15); fout << "string ";
						fout.width(15); fout << "-";
						fout.width(15); fout << (int)idtable.table[i].value.vstr->len;
					}
					
					fout << std::endl;
				}
				
			}
			fout << std::endl;
			fout.setf(std::ios::left);
			fout.width(15); fout << "function";
			fout.width(15); fout << "visible";
			fout.width(15);	fout << "type" << std::endl;

			for (size_t i = 0; i < idtable.current_size; i++)
			{
				if (idtable.table[i].idtype == IT::IDTYPE::F) {

					if (idtable.table[i].id[0]) {
						fout.width(15); fout << idtable.table[i].id;
						fout.width(15); fout << idtable.table[i].prefix;
					}
					else
					{
						fout.width(15); fout << idtable.table[i].extFunct;
						fout.width(15); fout << idtable.table[i].prefix;
					}

					if (idtable.table[i].iddatatype == IT::IDDATATYPE::INT) {
						fout.width(15); fout << "integer ";
					}
					if (idtable.table[i].iddatatype == IT::IDDATATYPE::STR) {
						fout.width(15); fout << "string ";
					}

					fout << std::endl;
				}

			}
			fout << std::endl;
			fout.setf(std::ios::left);
			fout.width(15); fout << "visible";
			fout.width(15); fout << "parametr";
			fout.width(15);	fout << "type" << std::endl;

			for (size_t i = 0; i < idtable.current_size; i++)
			{
				if (idtable.table[i].idtype == IT::IDTYPE::P) {

					if (idtable.table[i].id[0]) {
						fout.width(15); fout << idtable.table[i].prefix;
						fout.width(15); fout << idtable.table[i].id;
					}

					if (idtable.table[i].iddatatype == IT::IDDATATYPE::INT) {
						fout.width(15); fout << "integer ";
					}

					if (idtable.table[i].iddatatype == IT::IDDATATYPE::STR) {
						fout.width(15); fout << "string ";
					}

					fout << std::endl;
				}

			}

			fout << std::endl;
			fout.setf(std::ios::left);
			fout.width(15); fout << "type";
			fout.width(15);	fout << "value";
			fout.width(15);	fout << "size" << std::endl;

			for (size_t i = 0; i < idtable.current_size; i++)
			{
				if (idtable.table[i].idtype == IT::IDTYPE::L) {

					if (idtable.table[i].iddatatype == IT::IDDATATYPE::INT) {
						fout.width(15); fout << "integer";
						fout.width(15); fout << idtable.table[i].value.vint;
						fout.width(15); fout << "----";
					}

					if (idtable.table[i].iddatatype == IT::IDDATATYPE::STR) {
						fout.width(15); fout << "string ";
						fout.width(15); fout << idtable.table[i].value.vstr->str;
						fout.width(15); fout << (int)idtable.table[i].value.vstr->len;

					}

					fout << std::endl;
				}

			}
		fout.close();
	}

	void Delete(IdTable& idtable) {
		delete[] idtable.table;
		idtable.table = nullptr;
	}
}