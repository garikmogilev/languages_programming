#pragma once
#include "LT.h"
#include "IT.h"
#define SEPARATER '|'
#define NEGATIVE '-'

namespace  GM
{
	
	struct Data
	{
		bool switch_string;					// acces all symbol for literal
		int count_lines;					// counts lines in array
		int count;	   						// number lexema
		char token;							// saved returned token
		char prefix[PREFIX_SIZE];			// prefix for parametres and variables
		char extprefix[PREFIX_SIZE];		// prefix for parametres and variables
		bool visibility_in_body;			// visibility for body function
		bool global;						// global visibility
		bool declare;						// variable declare
		bool visibility_in_parametres;		// visible for parametres
		char* string = nullptr;				// ptr for string
		bool negativeValue = false;			// negative values for string or may be other types
		char extPrefix[EXT_PREFIX];			// prefix for extencions function
		Data()
		{
			switch_string = false;
			count_lines = 1 ;
			count = 0;
			token = 0;
			memset(prefix, 0, PREFIX_SIZE);
			visibility_in_body = false;
			global = false;
			visibility_in_parametres = false;
		}
	};
	
	char token_rekognizer(char* string, IT::Entry*);								// returned token
	void dataProcesing(unsigned char*, std::fstream*, LT::LexTable*, IT::IdTable*);	// data processing all expressions
	void IdentificatorCreate(IT::IdTable*, Data&);									// add identifier
	bool alphaCirillicDigit(char);													// checked symbol (latin, cirilic or digit)
}