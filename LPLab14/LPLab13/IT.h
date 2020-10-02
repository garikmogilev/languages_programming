#pragma once

#define ID_MAXSIZE		5								// ������������ ���������� ������� � ��������������
#define	PREFIX_SIZE		10
#define EXT_FUNCTION	10
#define TI_MAXSIZE		4096							// ������������ ���������� ��-�� � ������� ��������������� 
#define TI_INT_DEFAULT	0x00000000						// �������� �� ��������� ��� ���� integer 
#define TI_STR_DEFAULT	0x00							// �������� �� ��������� ��� ���� string 
#define TI_NULLIDX		0xffffffff						// ��� �������� ������� ���������������
#define TI_STR_MAXSIZE	255
#define VISIBLE_GLOBAL  "::"

#define PARM_ID_DEFAULT_EXT L"file.id.txt"				// ����� ��������������� � ���������

namespace IT											// ������� �������������
{
	enum IDDATATYPE { NUL = 0, INT = 1, STR = 2 };		// ���� ������ ���������������: integer, string
	enum IDTYPE { N = 0, V = 1, F = 2, P = 3, L = 4};	// ���� ���������������: ����������, �������, ��������, �������

	struct Entry										// ������ ������� ���������������
	{
		int idxfirstLE = TI_NULLIDX;					//  
		char id[ID_MAXSIZE + 1];						// ������������� (������������� ��������� �� ID_MAXSIZE
		char prefix[PREFIX_SIZE];	
		char extFunct[EXT_FUNCTION];					// ������� ��������� 
		IDDATATYPE	iddatatype = NUL;					// ��� ������
		IDTYPE	idtype = N;								// ��� ��������������
		union
		{
			int vint = NULL;							// �������� integer
			struct
			{
				unsigned char len;						// ��������� �������� � string
				char str[TI_STR_MAXSIZE - 1];			// ������� string
			} 
			vstr[TI_STR_MAXSIZE];						// �������� string
		}value;											// �������� ��������������
	};

	struct IdTable										// ��������� ������� ���������������
	{
		int maxsize;									// ������� ������� ��������������� < TI_MAXSIZE
		int current_size;								// ������� ������ ������� ��������������� < maxsize
		Entry* table;									// ������ ����� ������� ���������������
	};

	IdTable Create(int);
	void Add(IdTable&, Entry);							// �������� � ������ ���������������
	Entry GetEntry(IdTable&, int n);					// �������� ������ ������� ���������������
	Entry AddLiteral(Entry&);							// 
	int IsId(IdTable&, char[], char[]);					// ������� : ������� ������ (���� ����), TI_NULLIDX(���� ���)
	int IsLiteral(IdTable&, char*);							// ������ IT_TI_NULLIDX ���� ���� ��� ���������� �������������
	int IsLiteral(IdTable&, int);						// 
	void PrintIdTable(const wchar_t* in, IdTable&);		// ������ ������� ���������������
	void Delete(IdTable&);								// ������� ������� ������ (���������� �����)
}