#pragma once
#define ID_MAXSIZE		5								// ������������ ���������� ������� � ��������������
#define	PREFIX_SIZE		10
#define EXT_FUNCTION	10
#define EXT_PREFIX		10
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
		int idxfirstLE;									//  
		char id[ID_MAXSIZE + 1];						// ������������� (������������� ��������� �� ID_MAXSIZE
		char prefix[PREFIX_SIZE];						// ������� ���������
		char extFunct[EXT_FUNCTION];					// ������� �������
		IDDATATYPE iddatatype;							// ��� ������
		IDTYPE idtype ;									// ��� ��������������
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

		Entry()
		{
			idxfirstLE = TI_NULLIDX;
			memset(prefix, 0x00, PREFIX_SIZE);
			memset(id, 0x00, ID_MAXSIZE);
			memset(extFunct, 0x00, EXT_FUNCTION);
			iddatatype = NUL;
			idtype = N;
		}
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
	int IsId(IdTable&, char[],char[],int);				// ������� : ������� ������ (���� ����), TI_NULLIDX(���� ���)
	int IsLiteral(IdTable&, char*);						// ������ IT_TI_NULLIDX ���� ���� ��� ���������� �������������
	int IsLiteral(IdTable&, int);						// ������ IT_TI_NULLIDX ���� ���� ��� ���������� �������������
	void LiteralCreate(IdTable&, char*, int, bool&);	// �������� ������� � �������
	void PrintIdTable(const wchar_t* in, IdTable&);		// ������ ������� ���������������
	void Delete(IdTable&);								// ������� ������� ������ (���������� �����)
}