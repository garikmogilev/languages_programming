#pragma once
#define GRAPH (const char*)string,\
9,\
/*0*/FST::NODE(1, FST::RELATION('a', 1)),\
/*1*/FST::NODE(3, FST::RELATION('b', 1), FST::RELATION('b', 2), FST::RELATION('b', 6)),\
/*2*/FST::NODE(1, FST::RELATION('c', 3)),\
/*3*/FST::NODE(4, FST::RELATION('d', 2), FST::RELATION('d', 5), FST::RELATION('d', 6), FST::RELATION('f', 4)),\
/*4*/FST::NODE(3, FST::RELATION('g', 2), FST::RELATION('g', 4), FST::RELATION('g', 6)),\
/*5*/FST::NODE(3, FST::RELATION('e', 2), FST::RELATION('e', 5), FST::RELATION('e', 6)),\
/*6*/FST::NODE(2, FST::RELATION('b', 6), FST::RELATION('b', 7)),\
/*7*/FST::NODE(1, FST::RELATION('h', 8)),\
/*8*/FST::NODE()

namespace Out 
{
	struct OUT {
		wchar_t outfile[PARM_MAX_SIZE];
		std::fstream* streamOut;
		std::fstream** streamLog;
	};

	OUT getout(wchar_t outfile[]);
	void writeOut(Out::OUT out, GM::Data* ptrdata);
	void close(Out::OUT out);


	
}