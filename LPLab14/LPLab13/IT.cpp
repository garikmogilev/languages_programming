#include "stdafx.h"
#define ENTRY	idtable.table[idtable.current_size]
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
			throw ERROR_THROW(122);

	}

	Entry GetEntry(IdTable& idtable, int n)
	{
			return idtable.table[n];
	}

	int IsId(IdTable& idtable, char* id,char* prefix, int line) {
		for (int i = 0; i < idtable.current_size; i++)
		{
			if (!strcmp(idtable.table[i].id, id) && (!strcmp(idtable.table[i].prefix, prefix)))
			{
				if (idtable.table[i].idtype == IT::F)
					throw ERROR_THROW_LINE(125, line);
				if (idtable.table[i].idtype == IT::V)
					throw ERROR_THROW_LINE(126, line);
			}
			else if (!strcmp(idtable.table[i].extFunct, id))
				if (idtable.table[i].idtype == IT::F)
					throw ERROR_THROW_LINE(125, line);
		}
		return LT_TI_NULLXDX;
	}

	int IsLiteral(IdTable& idtable, char* str) {
		for (int i = 0; i < idtable.current_size; i++)
		{
			if (!strcmp(idtable.table[i].value.vstr->str, str))
				return i;
		}
		return LT_TI_NULLXDX;
	}

	int IsLiteral(IdTable& idtable, int vint) {
		for (int i = 0; i < idtable.current_size; i++)
		{
			if (idtable.table[i].value.vint == vint)
				return i;
		}
		return LT_TI_NULLXDX;
	}

	void LiteralCreate(IdTable& idtable, char* string, int countLine,bool& negativeValue)
	{
		if (long long value = (atoll(string))) {
			
			if (negativeValue)
				value = value* (-1);

			if (value > INT_MAX || value < INT_MIN)
				throw ERROR_THROW_LINE(121, countLine);
			if (IsLiteral(idtable, (int)value) == LT_TI_NULLXDX || !value) {
				idtable.table[idtable.current_size].idtype = IT::IDTYPE::L;
				idtable.table[idtable.current_size].iddatatype = IT::IDDATATYPE::INT;
				idtable.table[idtable.current_size].value.vint = (int)value;
				IT::Add(idtable, idtable.table[idtable.current_size]);
			}
		}
		else
		{
			int size = (strlen(string) - 2);						// -2 - минус ковычки

			if (size > TI_STR_MAXSIZE)
				throw ERROR_THROW_LINE(123, countLine);

			char temp[TI_STR_MAXSIZE];
			strncpy_s(temp, (string + 1), size);

			if (IsLiteral(idtable, temp) == LT_TI_NULLXDX) {
				idtable.table[idtable.current_size].idtype = IT::IDTYPE::L;
				idtable.table[idtable.current_size].iddatatype = IT::IDDATATYPE::STR;
				strcpy_s(idtable.table[idtable.current_size].value.vstr->str, temp);
				idtable.table[idtable.current_size].value.vstr->len = (char)(size);
				IT::Add(idtable, idtable.table[idtable.current_size]);
				//ResetTypes(idtable.table[idtable.current_size]);
			}
		}
	}

	void PrintIdTable(const wchar_t* out, IdTable& idtable)
	{
		short lengthRow = 20;
		std::fstream fout(out, std::ios::out);

		char buffer[48];
		time_t rawtime;
		struct tm* timeinfo;
		time(&rawtime);
		timeinfo = localtime(&rawtime);
		strftime(buffer, 48, "%d-%m-%Y --%A-- %H:%M:%S ", timeinfo);

		fout << "ID table, modified time: " << buffer << IN_CODE_ENDL << IN_CODE_ENDL;

		fout.setf(std::ios::left);
		fout.width(lengthRow); fout << "visible";
		fout.width(lengthRow);	fout << "variable"; \
		fout.width(lengthRow); fout << "type"; 
		fout.width(lengthRow); fout << "value int";
		fout.width(lengthRow); fout << "value str" << IN_CODE_ENDL;

			for (int i = 0; i < idtable.current_size; i++)
			{
				if (idtable.table[i].idtype == IT::IDTYPE::V) {
					fout.width(lengthRow);
					fout << idtable.table[i].prefix;
					fout.width(lengthRow);
					fout << idtable.table[i].id;
					//fout.width(lengthRow); fout << idtable.table[i].extFunct;

					if (idtable.table[i].iddatatype == IT::IDDATATYPE::INT) {
						fout.width(lengthRow); fout << "integer ";
						fout.width(lengthRow); fout << idtable.table[i].value.vint;
						fout.width(lengthRow); fout << "-";
					}
					if (idtable.table[i].iddatatype == IT::IDDATATYPE::STR) {
						fout.width(lengthRow); fout << "string ";
						fout.width(lengthRow); fout << "-";
						fout.width(lengthRow); fout << (int)idtable.table[i].value.vstr->len;
					}
					
					fout << IN_CODE_ENDL;
				}
				
			}
			fout << IN_CODE_ENDL;
			fout.setf(std::ios::left);
			fout.width(lengthRow); fout << "visible";
			fout.width(lengthRow); fout << "function";
			fout.width(lengthRow);	fout << "type" << IN_CODE_ENDL;

			for (int i = 0; i < idtable.current_size; i++)
			{
				if (idtable.table[i].idtype == IT::IDTYPE::F) {

					if (idtable.table[i].id[0]) {
						fout.width(lengthRow); fout << idtable.table[i].prefix;
						fout.width(lengthRow); fout << idtable.table[i].id;
					}
					else
					{
						fout.width(lengthRow); fout << idtable.table[i].prefix;
						fout.width(lengthRow); fout << idtable.table[i].extFunct;
					}

					if (idtable.table[i].iddatatype == IT::IDDATATYPE::INT) {
						fout.width(lengthRow); fout << "integer ";
					}
					if (idtable.table[i].iddatatype == IT::IDDATATYPE::STR) {
						fout.width(lengthRow); fout << "string ";
					}

					fout << IN_CODE_ENDL;
				}

			}
			fout << IN_CODE_ENDL;
			fout.setf(std::ios::left);
			fout.width(lengthRow); fout << "visible";
			fout.width(lengthRow); fout << "parameter";
			fout.width(lengthRow);	fout << "type" << IN_CODE_ENDL;

			for (int i = 0; i < idtable.current_size; i++)
			{
				if (idtable.table[i].idtype == IT::IDTYPE::P) {

					if (idtable.table[i].id[0]) {
						fout.width(lengthRow); fout << idtable.table[i].prefix;
						fout.width(lengthRow); fout << idtable.table[i].id;
					}

					if (idtable.table[i].iddatatype == IT::IDDATATYPE::INT) {
						fout.width(lengthRow); 
						fout << "integer ";
					}

					if (idtable.table[i].iddatatype == IT::IDDATATYPE::STR) {
						fout.width(lengthRow); 
						fout << "string ";
					}

					fout << IN_CODE_ENDL;
				}

			}

			fout << IN_CODE_ENDL;
			fout.setf(std::ios::left);
			fout.width(lengthRow); fout << "type";
			fout.width(lengthRow);	fout << "size(string)";
			fout << "value" << IN_CODE_ENDL;

			for (int i = 0; i < idtable.current_size; i++)
			{
				if (idtable.table[i].idtype == IT::IDTYPE::L) {

					if (idtable.table[i].iddatatype == IT::IDDATATYPE::INT) {
						fout.width(lengthRow); fout << "integer";
						fout.width(lengthRow); fout << "------";
						fout.width(lengthRow); fout << idtable.table[i].value.vint;
						
					}

					if (idtable.table[i].iddatatype == IT::IDDATATYPE::STR) {
						fout.width(lengthRow); fout << "string ";
						fout.width(lengthRow); fout << (int)idtable.table[i].value.vstr->len;
						fout.width(lengthRow); fout << idtable.table[i].value.vstr->str;
					}

					fout << IN_CODE_ENDL;
				}

			}
		fout.close();
	}

	void Delete(IdTable& idtable) {
		delete[] idtable.table;
		idtable.table = nullptr;
	}
}