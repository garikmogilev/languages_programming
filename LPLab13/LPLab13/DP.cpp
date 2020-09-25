#include "stdafx.h"
#define TOKEN token_rekognizer(string)

#include "../generator_graphs/graphs.h"


namespace GM
{
	void dataProceesing(unsigned char* text, wchar_t* outs, std::fstream* stream)
	{
		LT::LexTable tableLEX = LT::Ñreate(LT_MAXSIZE);
		Out::OUT out = Out::getout(outs);
		out.streamLog = &stream;

		GM::Data data;
		GM::Data* ptrData = &data;

		unsigned char* start = text;
		unsigned char* end = start;
		bool switch_string = false;
		char token;

		while (true)
		{
			if (!*end) break;

				if ((!alphaCirillicDigit (*end) || !isalnum(*start)) && !switch_string)
				{
					token = checkSetOfData(start, end, ptrData);
					//writeOut(out, ptrData);
					start = end;

					delete[] ptrData->text;
				}
			
				if (*end == '\'') {
					if (switch_string)
						switch_string = false;
					else
						switch_string = true;
				}

				if ((*end == SPACE || *end == SEPARATER) && !switch_string) {
					start = end;
					start++;
					end = start;
				}
			end++;

		}
		/*LT::LexTable tableLEX = LT::Ñreate(LT_MAXSIZE);
		LT::Entry entry;
		entry.lexema[0] = TOKEN;
		entry.sn = 0;
		entry.idxTI = LT_TI_NULLXDX;
		LT::Add(tableLEX, entry);*/
		Out::close(out);
	}

	char checkSetOfData(unsigned char* start, unsigned char* end, GM::Data* ptrData)
	{
		char* string = new  char[end - start + 2];
		strncpy(string, (char*)start, end - start);
		string[end - start] = STR_ENDL;
		char token;

		token = TOKEN;

		std::cout.width(20);
		std::cout.setf(std::ios::left);
		std::cout << string;
		std::cout.width(10);
		std::cout << token;
		std::cout << std::endl;
		return token;
	}

	char token_rekognizer(char* string) {
		bool result = false;
		ANALISES_TOKEN;
	}

	bool alphaCirillicDigit(char symbol) {
		if (isalpha(symbol))
			return true;
		else if (isdigit(symbol))
			return true;
		else if (symbol >= 'à' && symbol <= 'ÿ')
			return true;
		else
			return false;
	}
}