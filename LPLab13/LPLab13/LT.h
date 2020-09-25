#pragma once
#define LEXEMA_FIXSIZE	1			// фиксированный размер лексемы
#define	LT_MAXSIZE		4096		// максимальное количество строк в таблице лексем	
#define	LT_TI_NULLXDX	0xffffffff	// нет элемента таблицы идентификаторов				
#define	LEX_INTEGER		't'			// лексема для integer
#define	LEX_STRING		't'			// лексема для string
#define	LEX_ID			'i'			// лексема для идентификатора
#define	LEX_LITERAL		'l'			// лексема для литерала
#define	LEX_FUNCTION	'f'			// лексема для function
#define	LEX_DECLARE		'd'			// лексема для declare
#define	LEX_RETURN		'r'			// лексема для return
#define	LEX_PRINT		'p'			// лексема для print
#define LEX_MAIN		'm'			// лексема для main
#define LEX_IF			'h'			// лексема для if
#define	LEX_SEMICOLON	';'			// лексема для ;
#define	LEX_COMMA		','			// лексема для ,
#define	LEX_LEFTBRACE	'{'			// лексема для {
#define	LEX_RIGHTBRACE	'}'			// лексема для }
#define	LEX_LEFTHESIS	'('			// лексема для (
#define	LEX_RIGHTESIS	')'			// лексема для )
#define	LEX_EQUALS		'='			// лексема для =
#define	LEX_PLUS		'v'			// лексема для +
#define	LEX_MINUS		'v'			// лексема для -
#define	LEX_STAR		'v'			// лексема для *
#define	LEX_DIRSLASH	'v'			// лексема для /


namespace LT							// таблица лексем
{
	struct Entry						// строка таблицы лексем
	{
		char lexema[LEXEMA_FIXSIZE];	// лексема
		int sn;							// номер строки в исходном тексте
		int idxTI;						// индекс в таблице идентификаторов или LT_TI_NULLIDX
	};

	struct LexTable						// экземпляр таблицы лексем
	{
		int maxsize;					// емкость таблицы лексем < LT_MAXSIZE
		int size;						// текущий размер таблицы лексем < maxsize
		Entry* table;					// массив строк таблицы лексем
	};

	LexTable Сreate(int size);					// создать таблицу лексем
	void Add(LexTable& lextable, Entry entry);	// добавление лексем
	Entry GetEntry(LexTable& lextable, int n);	// получить строку таблицы лексем
	void Delete(LexTable& lextable);			// удалить таблицу лексем (освободить память)

};