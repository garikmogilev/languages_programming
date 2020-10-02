#pragma once
#include "LT.h"
#include "IT.h"
#define SEPARATER '|'

namespace  GM
{
	struct Data
	{
		bool switch_string = false;			// ������ ��� �������, ���� ������
		int count_lines = 0;				// ���������� �����
		int count = 0;				// ����� �������������� � ������� ������
		char token;							// ���������� ������ �������
		char prefix[PREFIX_SIZE];		// ���������� �������� (������� ���������)
		bool visibility = false;
		bool global = false;
	};
	
	char token_rekognizer(char* string, IT::Entry*);
	void dataProcesing(unsigned char*, std::fstream*, LT::LexTable*, IT::IdTable*);
	bool alphaCirillicDigit(char);
}