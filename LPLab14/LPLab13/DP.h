#pragma once
#include "LT.h"
#include "IT.h"
#define SEPARATER '|'

namespace  GM
{
	struct Data
	{
		bool switch_string = false;			// читать все символы, если строка
		int count_lines = 0;				// количество строк
		int count = 0;				// номер идентификатора в таблице лексем
		char token;							// возвращает хранит лексему
		char prefix[PREFIX_SIZE];		// сохранение префикса (область видимости)
		bool visibility = false;
		bool global = false;
	};
	
	char token_rekognizer(char* string, IT::Entry*);
	void dataProcesing(unsigned char*, std::fstream*, LT::LexTable*, IT::IdTable*);
	bool alphaCirillicDigit(char);
}