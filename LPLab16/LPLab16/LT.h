#pragma once
#include "cstring"
#define LEXEMA_FIXSIZE	1			// size length lexema
#define	LT_MAXSIZE		4096		// maximal size lexem	
#define	LT_TI_NULLXDX	0xffffffff	// not link table ID			
#define	LEX_INTEGER		't'			// type data integer
#define	LEX_BYTE		't'			// type data byte
#define	LEX_STRING		't'			// type data string
#define	LEX_ID			'i'			// ������� ��� ��������������
#define	LEX_LITERAL		'l'			// ������� ��� ��������
#define	LEX_FUNCTION	'f'			// ������� ��� function
#define	LEX_DECLARE		'd'			// ������� ��� declare
#define	LEX_RETURN		'r'			// ������� ��� return
#define	LEX_PRINT		'p'			// ������� ��� print
#define LEX_MAIN		'm'			// ������� ��� main
#define	LEX_SEMICOLON	';'			// ������� ��� ;
#define	LEX_COMMA		','			// ������� ��� ,
#define	LEX_LEFTBRACE	'{'			// ������� ��� {
#define	LEX_RIGHTBRACE	'}'			// ������� ��� }
#define	LEX_LEFTHESIS	'('			// ������� ��� (
#define	LEX_RIGHTESIS	')'			// ������� ��� )
#define	LEX_ASSIGN		'='			// ������� ��� =
#define	LEX_PLUS		'v'			// ������� ��� +
#define	LEX_MINUS		'v'			// ������� ��� -
#define	LEX_STAR		'v'			// ������� ��� *
#define	LEX_DIRSLASH	'v'			// ������� ��� /
#define EXPRESSIONS		'v'			// ������ ��� ���� ���������
#define LEX_LESS		'c'			// symbol compare <
#define LEX_MORE		'c'			// symbol compare >
#define LEX_EQUALS		'c'			// symbol compare ==
#define LEX_NOT_EQUALS	'c'			// symbol compare !=
#define LEX_XOR			'b'			// symbol compare ^
#define LEX_INVERSION	'b'			// symbol compare ~
#define LEX_AND			'b'			// symbol compare |
#define LEX_OR			'b'			// symbol compare &
#define LEX_WRITE		'w'			// write to console
#define LEX_WRITEL		'w'			// write to console


namespace LT									// ������� ������
{
	struct Entry								// ������ ������� ������
	{
		char lexema[LEXEMA_FIXSIZE + 1];		// �������
		char expression[LEXEMA_FIXSIZE + 1];	// ��������� +,-,/,*
		int sn;									// ����� ������ � �������� ������
		int idxTI;								// ������ � ������� ��������������� ��� LT_TI_NULLIDX
		Entry()
		{
			memset(lexema, 0x00, LEXEMA_FIXSIZE + 1);
			memset(expression, 0x00, LEXEMA_FIXSIZE + 1);
			sn = 0;
			idxTI = LT_TI_NULLXDX;
		}
		Entry(char a, int i) {
			lexema[0] = a;
			lexema[1] = 0x00;
			sn = i;
		}
	};

	struct LexTable								// ��������� ������� ������
	{
		int maxsize;							// ������� ������� ������ < LT_MAXSIZE
		int size = 0;							// ������� ������ ������� ������ < maxsize
		Entry* table;							// ������ ����� ������� ������
	};

	LexTable Create(int);						// ������� ������� ������
	Entry Create(char, int);
	void Add(LexTable*, Entry);					// ���������� ������
	Entry GetEntry(LexTable&, int);				// �������� ������ ������� ������
	void PrintTableLex(LexTable*, wchar_t*);		// ���������� ������� ������
	void Delete(LexTable&);						// ������� ������� ������ (���������� ������)

};