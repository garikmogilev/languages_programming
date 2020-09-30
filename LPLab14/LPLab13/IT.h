#pragma once

#define ID_MAXSIZE		5								// максимальное количество сиволов в идентификаторе
#define TI_MAXSIZE		4096							// максимальное количество эл-ов в таблице идентификаторов 
#define TI_INT_DEFAULT	0x00000000						// значение по умолчанию дл€ типа integer 
#define TI_STR_DEFAULT	0x00							// значение по умолчанию дл€ типа string 
#define TI_NULLIDX		0xffffffff						// нет элемента таблицы идентификаторов
#define TI_STR_MAXSIZE	255

#define PARM_ID_DEFAULT_EXT L".id.txt"					//дл€ файла с итогом лексического анализa(идентификаторы и литералы)

namespace IT											// таблица идентификатов
{
	enum IDDATATYPE { NUL = 0, INT = 1, STR = 2 };		// типы данных идентификаторов: integer, string
	enum IDTYPE { N = 0, V = 1, F = 2, P = 3, L = 4 };	// типы идентификаторов: переменна€, функци€, параметр, лексема

	struct Entry										// строка таблицы идентификаторов
	{
		int idxfirstLE = TI_NULLIDX;					//  
		char id[ID_MAXSIZE + 1];						// идентификатор (автоматически усекаетс€ до ID_MAXSIZE
		char visibility[ID_MAXSIZE + 1];				// область видимости 
		IDDATATYPE	iddatatype = NUL;					// тип данных
		IDTYPE	idtype = N;								// тип идентификатора
		union
		{
			int vint = NULL;							// значение integer
			struct
			{
				unsigned char len;						// количесво символов в string
				char str[TI_STR_MAXSIZE - 1];			// символы string
			} 
			vstr[TI_STR_MAXSIZE];						// значение string
		}value;											// значение идентификатора
	};

	struct IdTable										// экземпл€р таблицы идентификаторов
	{
		int maxsize;									// емкость таблицы идентификаторов < TI_MAXSIZE
		int current_size;								// текущий размер таблицы идентификаторов < maxsize
		Entry* table;									// массив строк таблицы идентификаторов
	};

	IdTable Create(int size);
	void Add(IdTable& idtable, Entry entry);			// добавить в строку идентификаторов
	Entry GetEntry(IdTable& idtable, int n);			// получить строку таблицы идентификаторов
	int IsId(IdTable& idtable, char id[ID_MAXSIZE]);	// возврат : возврат строки (если есть), TI_NULLIDX(если нет)
	//void PrintIdTable(const wchar_t* in);
	void Delete(IdTable&);								// удалить таблицу лексем (освободить место)
}