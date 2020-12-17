#include "GRB.h"
#define GRB_ERROR_SERIES 600
#include <string.h>

namespace GRB
{	
	Rule::Chain::Chain(short size, GRBALPHABET s, ...)
	{
		nt = new GRBALPHABET[this->size = size];

		int* ptr = (int*)& s;
		for (short i = 0; i < size; i++)
			nt[i] = (GRBALPHABET)ptr[i];
	}

	Rule::Rule(GRBALPHABET nn, int iderror, short size, Chain c, ...)
	{
		this->nn = nn;
		this->iderror = iderror;
		this->chains = new Chain[this->size = size];

		Chain* ptr = &c;
		for (int i = 0; i < size; i++)
				this->chains[i] = ptr[i];
	}

	Greibach::Greibach(GRBALPHABET startN, GRBALPHABET stbottomT, short size, Rule r, ...)
	{
		this->startN = startN;
		this->stbottomT = stbottomT;
		this->rules = new Rule[this->size = size];
		Rule* ptr = &r;
		for (int i = 0; i < size; i++)
			rules[i] = ptr[i];
	}

	short Greibach::getRule(GRBALPHABET nn, Rule& rule)
	{
		short rc = -1, k = 0;

		while (k < size && rules[k].nn != nn)
			k++;

		if (k < size)
			rule = rules[rc = k];

		return rc;
	}

	Rule Greibach::getRule(short n)
	{
		Rule rc;
		if (n < size)
			rc = rules[n];
		return rc;
	}

	char* Rule::getCRule(char* b, short nchain)
	{
		char buf[200];
		b[0] = Chain::alphabet_to_char(nn);
		b[1] = '-';
		b[2] = '>';
		b[3] = 0;
		chains[nchain].getCChain(buf);
		strcat_s(b, sizeof(buf) + 5, buf);

		return b;
	}

	short Rule::getNextChain(GRBALPHABET t, Rule::Chain& pchain, short j)
	{
		short rc = -1;
			
		while (j < size && chains[j].nt[0] != t && chains[j].nt[0] != 0)
			j++;

		rc = (j < size ? j : -1);
		if (rc >= 0)
			pchain = chains[rc];
		return rc;
	}

	char* Rule::Chain::getCChain(char* b)
	{
		for (int i = 0; i < size; i++)
			b[i] = Chain::alphabet_to_char(nt[i]);
		b[size] = 0x00;
		return b;
	}

	Greibach getGreibach() { return greibach; }
}
#define NS(n) Rule::Chain::N(n)
#define TS(n) Rule::Chain::T(n)

	Greibach greibach(NS('S'), TS('$'), 6,
		Rule(NS('S'), GRB_ERROR_SERIES + 0, 
			2,	//Íåâåðíàÿ ñòðóêòóðà ïðîãðàììû
			Rule::Chain(7, TS('m'), TS('{'), NS('N'), TS('r'), NS('E'), TS(';'), TS('}')),
			Rule::Chain(13, TS('t'), TS('f'), TS('i'), TS('('), NS('F'), TS(')'), TS('{'), NS('N'), TS('r'), NS('E'), TS(';'), TS('}'), NS('S'))
		),
		Rule(NS('N'), GRB_ERROR_SERIES + 1,
			9,	//îøèáî÷íûé îïåðàòîð
			Rule::Chain(4, TS('d'), TS('t'), TS('i'), TS(';')),
			Rule::Chain(5, TS('d'), TS('t'), TS('i'), TS(';'), NS('N')),
			Rule::Chain(4, TS('i'), TS('='), NS('E'), TS(';')),
			Rule::Chain(5, TS('i'), TS('='), NS('E'), TS(';'), NS('N')),
			Rule::Chain(8, TS('d'), TS('t'), TS('f'), TS('i'), TS('('), NS('F'), TS(')'), TS(';')),
			Rule::Chain(9, TS('d'), TS('t'), TS('f'), TS('i'), TS('('), NS('F'), TS(')'), TS(';'), NS('N')),
			Rule::Chain(3, TS('r'), NS('E'), TS(';')),
			Rule::Chain(3, TS('p'), NS('E'), TS(';')),
			Rule::Chain(4, TS('p'), NS('E'), TS(';'), NS('N'))
		),
		Rule(NS('E'), GRB_ERROR_SERIES + 2, 
			8,	//âûðàæåíèå
			Rule::Chain(1, TS('i')),
			Rule::Chain(1, TS('l')),
			Rule::Chain(3, TS('('), NS('E'), TS(')')),
			Rule::Chain(4, TS('i'), TS('('), NS('W'), TS(')')),
			Rule::Chain(2, TS('i'), NS('M')),
			Rule::Chain(2, TS('l'), NS('M')),
			Rule::Chain(4, TS('('), NS('E'), TS(')'), NS('M')),
			Rule::Chain(5, TS('i'), TS('('), NS('W'), TS(')'), NS('M'))
		),
		Rule(NS('M'), GRB_ERROR_SERIES + 1,
			2,	//Îøèáî÷íûé îïåðàòîð
			Rule::Chain(2, TS('v'), NS('E')),
			Rule::Chain(3, TS('v'), NS('E'), NS('M'))
		),
		Rule(NS('F'), GRB_ERROR_SERIES + 3, 2,	// ïàðàìåòðû ôóíêöèè ïðè îïðåäåëåíèè
			Rule::Chain(2, TS('t'), TS('i')),
			Rule::Chain(4, TS('t'), TS('i'), TS(','), NS('F'))
		),
		Rule(NS('W'), GRB_ERROR_SERIES + 4, 4, //ïàðàìåòðû âûçûâàåìîé ô-öèè
			Rule::Chain(1, TS('i')),
			Rule::Chain(1, TS('l')),
			Rule::Chain(3, TS('i'), TS(','), NS('W')),
			Rule::Chain(3, TS('l'), TS(','), NS('W'))
		)
	);

	Greibach getGreibach() { return greibach; }

}
