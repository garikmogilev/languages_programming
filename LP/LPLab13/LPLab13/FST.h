#pragma once
#include <iostream>
#include <tchar.h>


namespace FST
{
	struct RELATION							//11 ����� :������->������� ����� ��������� ��
	{
		char symbol;						// ������ ��������
		short nnode;						// ����� ������� �������
		RELATION(char � = 0x00,				// ������ ��������
			short ns = NULL);				// ����� ���������												
	};

	struct NODE								// ������� ����� ���������
	{
		short n_relation;					// ���������� ������������ �����
		RELATION* relations;				// ����������� �����
		NODE();
		NODE(
			short n,						// ���������� ������������ �����
			RELATION rel, ...				// ������ �����
		);
	};

	struct FST
	{
		unsigned char* string;				//������� (������, ���������� 0x00 ) 
		short position = 0;					//������� ������� � ������� 
		short nstates;						//���������� ��������� ��������
		NODE* nodes;						//���� ���������: [0] -��������� ���������, [nstate-1]-��������
		short* rstates;						//��������� ��������� �������� �� ������ �������.
		FST(
			const char* s,					//������� (������, ���������� 0x00 ) 
			short ns,						//���������� ��������� �������� 
			NODE n, ...						//������ ��������� (���� ���������)
		);
	};

	bool execute(							// ��������� ������������� ������� 
		FST& fst							//������������������ �������� �������
	);
};
