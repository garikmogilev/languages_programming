#pragma once
#include <iostream>
#include <tchar.h>


namespace FST
{
	struct RELATION							//11 ребро :символ->вершина графа переходов КА
	{
		char symbol;						// символ перехода
		short nnode;						// номер смежной вершины
		RELATION(char с = 0x00,				// символ перехода
			short ns = NULL);				// новое состояние												
	};

	struct NODE								// вершина графа переходов
	{
		short n_relation;					// количество инциндентных ребер
		RELATION* relations;				// инцидентные ребра
		NODE();
		NODE(
			short n,						// количество инциндентных ребер
			RELATION rel, ...				// список ребер
		);
	};

	struct FST
	{
		unsigned char* string;				//цепочка (строка, завершатся 0x00 ) 
		short position = 0;					//текущая позиция в цепочке 
		short nstates;						//количество состояний автомата
		NODE* nodes;						//граф переходов: [0] -начальное состояние, [nstate-1]-конечное
		short* rstates;						//возможные состояния автомата на данной позиции.
		FST(
			const char* s,					//цепочка (строка, завершатся 0x00 ) 
			short ns,						//количество состояний автомата 
			NODE n, ...						//список состояний (граф переходов)
		);
	};

	bool execute(							// выполнить распознавание цепочки 
		FST& fst							//недетерминировнный конечный автомат
	);
};
