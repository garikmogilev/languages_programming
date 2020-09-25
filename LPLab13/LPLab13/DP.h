#pragma once
#define SEPARATER '|'

namespace  GM
{
	struct Data
	{
		bool result = false;
		char* text = nullptr;
		int lines = 1;
		int positionErr = 0;
	};
	
	char token_rekognizer(char* string);
	void dataProceesing(unsigned char* text, wchar_t* out, std::fstream* stream);
	char checkSetOfData(unsigned char* start, unsigned char* end, GM::Data* ptrData);
	bool alphaCirillicDigit(char symbol);
}