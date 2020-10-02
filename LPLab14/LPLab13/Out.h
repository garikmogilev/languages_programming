#pragma once

namespace Out 
{
	struct OUT {
		wchar_t outfile[PARM_MAX_SIZE];
		std::fstream* streamOut;
		std::fstream** streamLog;
	};

	OUT getout(wchar_t outfile[]);
	//void writeOut(Out::OUT out, GM::Data* ptrdata);
	void close(Out::OUT out);


	
}