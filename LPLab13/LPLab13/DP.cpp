 #include "stdafx.h"

namespace GM
{
	void dataProceesing(unsigned char* text,wchar_t* outs, std::fstream* stream)
	{

		Out::OUT out = Out::getout(outs);
		out.streamLog = &stream;

		GM::Data data;
		GM::Data* ptrData = &data;

		unsigned char* start = text;
		unsigned char* end = start;

		while(true)
		{

			if (*end == SEPARATER || *end == STR_ENDL)
			{
				checkSetOfData(start, end, ptrData);
				writeOut(out, ptrData);

				if (!*end) break;

				data.lines++;
				start = end;
				start++;

				delete[] ptrData->text;
			}

			end++;
			
		}
		Out::close(out);
	}

	void checkSetOfData(unsigned char* start, unsigned char* end, GM::Data* ptrData)
	{
		int size = (end - start); 
		//bool result;
		char* string = new  char[size + 2];

		strncpy(string, (char*)start, size);
		string[size] = STR_ENDL;

		FST::FST check(GRAPH);

		//result = execute(check);

		strncpy(string, (char*)start, size+1);
		string[size+1] = STR_ENDL;

		//if(!result)
		//ptrData->positionErr = check.position;

		ptrData->text = string;
		//ptrData->result = result;
		string = nullptr;
	}
}