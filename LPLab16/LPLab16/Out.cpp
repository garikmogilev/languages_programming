#include "stdafx.h"

namespace Out
{
	OUT getout(wchar_t outfile[])
	{
		OUT out;
		out.streamOut = new std::fstream;
		out.streamOut->open(outfile, std::ios::out);

		if (out.streamOut->fail())
			throw ERROR_THROW(113);

		wcscpy_s(out.outfile, outfile);

		return out;
	}

	void writeOut(Out::OUT out, GM::Data* data)
	{
		if (data->result)
			*(out.streamOut) << data->text;
		else
			**(out.streamLog) << "������ ������� " << data->text \
			<< " �� ������� \"" << data->text[data->positionErr] \
			<< "\" ������� " << (data->positionErr + 1) \
			<< " ������ " << data->lines << IN_CODE_ENDL;
	}

	void close(Out::OUT out) 
	{
		delete out.streamOut;
		out.streamOut = nullptr;
	}
}