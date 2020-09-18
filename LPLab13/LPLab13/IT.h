#pragma once

#define ID_MAXSIZE		5				// максимальное количество сиволов в идентификаторе
#define TI_MAXSIZE		4096			// максимальное количество эл-ов в таблице идентификаторов 
#define TI_INT_DEFAULT	0x00000000		// значение по умолчанию дл€ типа integer 
#define TI_STR_DEFAULT	0x00			// значение по умолчанию дл€ типа string 
#define TI_NULLIDX		0xffffffff		// нет элемента таблицы идентификаторов
#define TI_STR_MAXSIZE	255

#define PARM_ID_DEFAULT_EXT L".id.txt" //дл€ файла с итогом лексического анализa(идентификаторы и литералы)

namespace IT	// таблица идентификатов
{
	enum IDDATATYPE { INT = 1, STR = 2 };						// типы данных идентификаторов: integer, string
	enum IDTYPE { V = 1, F = 2, P = 3, L = 3 };					// типы идентификаторов: переменна€, функци€, параметр, лексема

	struct Entry						// строка таблицы идентификаторов
	{
		int idxfirstLE;
		char id[ID_MAXSIZE];			// идентификатор (автоматически усекаетс€ до ID_MAXSIZE
		IDDATATYPE	iddatatype;			// тип данных
		IDTYPE	idtype;					// тип идентификатора
		union
		{
			int vint;					// значение integer
			struct
			{
				unsigned char len;			// количесво символов в string
				char str[TI_STR_MAXSIZE - 1];	// символы string
			} 
			vstr[TI_STR_MAXSIZE];	// значение string
		}value;	// значение идентификатора

		Entry();
		Entry(const char* parrentFunc, const char* id, IDDATATYPE iddatatype, IDTYPE idtype);
	};

	struct IdTable // экземпл€р таблицы идентификаторов
	{
		int maxsize;				// емкость таблицы идентификаторов < TI_MAXSIZE
		int current_size;			// текущий размер таблицы идентификаторов < maxsize
		Entry* table;				// массив строк таблицы идентификаторов

		IdTable (int size);

		void Add(IdTable& idtable, Entry entry);
		Entry GetEntry(IdTable& idtable, int n);
		int IsId(IdTable& idtable, char id[ID_MAXSIZE]);
		void PrintIdTable(const wchar_t* in);
		void Delete();
	};
}