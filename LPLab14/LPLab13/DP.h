#pragma once
#include "LT.h"
#include "IT.h"
#define SEPARATER '|'

namespace  GM
{
	struct Data
	{
		
	};
	
	char token_rekognizer(char* string, IT::IdTable*);
	void dataProcesing(unsigned char*, wchar_t*, std::fstream*, LT::LexTable*, IT::IdTable*);
	bool alphaCirillicDigit(char);
}