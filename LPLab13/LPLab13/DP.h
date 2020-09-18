#pragma once
#define SEPARATER '|'

namespace  GM
{
	struct Data
	{
		bool result;
		char* text;
		int lines = 1;
		int positionErr = 0;
	};

	void dataProceesing(unsigned char* text, wchar_t* out, std::fstream* stream);
	void checkSetOfData(unsigned char* start, unsigned char* end, GM::Data* ptrData);
}