﻿#include "stdafx.h"
#define TOKEN	token_rekognizer(data.string, &ENTRY);
#define ENTRY	idtable->table[idtable->current_size]

//#include "../generator_graphs/graphs.h"


namespace GM
{
	void dataProcesing(unsigned char* text, std::fstream* stream, LT::LexTable* lextable, IT::IdTable* idtable)
	{

		unsigned char* start = text;
		unsigned char* end = start;
		Data data;

		while (true)
		{
			if (!*end) break;

			if ((!alphaCirillicDigit(*end) || !alphaCirillicDigit(*start)) && !data.switch_string)
			{
				if (data.negativeValue) {
					start--;
					data.negativeValue = false;
				}

				data.string = new  char[end - start + 2];
				strncpy(data.string, (char*)start, end - start);
				data.string[end - start] = STR_ENDL;

				if (*data.string == NEGATIVE && lextable->table[lextable->size - 1].lexema[0] == LEX_EQUALS)
					data.negativeValue = true;

				data.token = TOKEN;												// ðàñïîçíàòü ëåêñåìó

				if (!data.token)
					throw ERROR_THROW_LINE(128, data.count_lines);				// ëåêñåìà íå ðàñïîçíàíà

				LT::Entry entryLT = LT::Create(data.token, data.count_lines);

				switch (data.token) {
				case LEX_LEFTBRACE:
					data.visibility_in_body = true;
					break;
				case LEX_RIGHTBRACE:
					data.visibility_in_body = false;
					memset(data.prefix, STR_ENDL, PREFIX_SIZE);
					break;
				case LEX_RIGHTESIS:
					data.visibility_in_parametres = false;
					data.global = false;
					break;
				case LEX_FUNCTION:
					if (data.declare)
						data.global = true;
					data.declare = false;
					break;
				case LEX_DECLARE:
					data.declare = true;
					break;
				case LEX_LITERAL:
					LiteralCreate(*idtable, data.string, data.count_lines, data.negativeValue);
					break;
				case EXPRESSIONS:
					entryLT.expression[0] = data.string[0];
					entryLT.expression[1] = STR_ENDL;
					break;
				case LEX_ID:
				case LEX_MAIN:
					/*if (ENTRY.idtype == IT::IDTYPE::F)*/
						/*if (!(bool)ENTRY.iddatatype)
							throw ERROR_THROW_LINE(127, data.count_lines);*/
					IdentificatorCreate(idtable, data);
					if ((bool)ENTRY.iddatatype || data.token == LEX_MAIN)
					{
						entryLT.idxTI = data.count++;
					}
					else
						entryLT.idxTI = ENTRY.idxfirstLE;

					IT::Add(*idtable, ENTRY);
					break;
				}

				LT::Add(lextable, entryLT);

				start = end;
				delete[] data.string;
			}

			if (*end == LITERAL) {
				if (data.switch_string)
					data.switch_string = false;
				else
					data.switch_string = true;
			}

			if ((*end == SPACE || *end == SEPARATER) && !data.switch_string) {
				if (*end == SEPARATER)
					data.count_lines++;
				start = end;
				start++;
				end = start;
			}

			end++;
		}
	}

	void IdentificatorCreate(IT::IdTable* idtable, Data& data)
	{

		switch (ENTRY.idtype) {
		case IT::IDTYPE::F:
		{
			if (data.global)
			{
				strncpy_s(data.extPrefix, data.string, PREFIX_SIZE);
				strncpy_s(ENTRY.id, data.string, ID_MAXSIZE);
				//strncpy_s(data.prefix, data.string, PREFIX_SIZE);
				//strcpy_s(ENTRY.prefix, VISIBLE_GLOBAL);
				//strncpy_s(ENTRY.extFunct, data.string, ID_MAXSIZE);
				//strncpy_s(ENTRY.prefix, VISIBLE_GLOBAL, EXT_FUNCTION);
			}
			else
			{
				strncpy_s(data.prefix, data.string, PREFIX_SIZE);
				strncpy_s(ENTRY.id, data.string, ID_MAXSIZE);
			}
			data.visibility_in_parametres = true;
			data.global = false;
			ENTRY.idxfirstLE = data.count;
			break;
		}
		case IT::IDTYPE::V:
		{
			strncpy_s(ENTRY.prefix, data.prefix, PREFIX_SIZE);
			strncpy_s(ENTRY.id, data.string, ID_MAXSIZE);
			ENTRY.idxfirstLE = data.count;
			break;
		}
		default:
		{
			/*if (!data.visibility_in_parametres)
				throw ERROR_THROW_LINE(124, data.count_lines);*/
			if (ENTRY.iddatatype)
			{
				ENTRY.idtype = IT::IDTYPE::P;
				if (data.visibility_in_parametres)
					strncpy_s(ENTRY.prefix, data.prefix, PREFIX_SIZE);
				strncpy_s(ENTRY.id, data.string, ID_MAXSIZE);
				ENTRY.idxfirstLE = data.count;
			}
			else
			{
				strncpy_s(ENTRY.id, data.string, ID_MAXSIZE);
				strncpy_s(ENTRY.prefix, data.prefix, PREFIX_SIZE);
				ENTRY.idxfirstLE = IT::IsId(*idtable, data.string, data.prefix, data.count_lines);
			}
			break;
		}
		}
	}

	char token_rekognizer(char* string, IT::Entry* entry) {
		bool result = false;

		switch (string[0]) {
		
		case '|':
		{
			FST::FST graph(string, 1,
				FST::NODE(1,
					FST::RELATION('|', 0)
				));
			if (result = execute(graph)) {
				return LEX_NOT_EQUALS;
				break;
			}

		}
		case '&':
		{
			FST::FST graph(string, 1,
				FST::NODE(1,
					FST::RELATION('&', 0)
				));
			if (result = execute(graph)) {
				return LEX_AND;
				break;
			}

		}
		case '(':
		{
			FST::FST graph(string, 1,
				FST::NODE(1,
					FST::RELATION('(', 0)
				));
			if (result = execute(graph)) {
				return LEX_LEFTHESIS;
				break;
			}

		}
		case ')':
		{
			FST::FST graph(string, 1,
				FST::NODE(1,
					FST::RELATION(')', 0)
				));
			if (result = execute(graph)) {
				return LEX_RIGHTESIS;
			}

		}
		case '*':
		{
			FST::FST graph(string, 1,
				FST::NODE(1,
					FST::RELATION('*', 0)
				));
			if (result = execute(graph)) {
				return LEX_STAR;
				break;
			}

		}
		case '+':
		{
			FST::FST graph(string, 1,
				FST::NODE(1,
					FST::RELATION('+', 0)
				));
			if (result = execute(graph)) {
				return LEX_PLUS;
			}

		}
		case ',':
		{
			FST::FST graph(string, 1,
				FST::NODE(1,
					FST::RELATION(',', 0)
				));
			if (result = execute(graph)) {
				return LEX_COMMA;
				break;
			}

		}
		case '-':
		{
			FST::FST graph(string, 1,
				FST::NODE(1,
					FST::RELATION('-', 0)
				));
			if (result = execute(graph)) {
				return LEX_MINUS;
			}

		}
		case '/':
		{
			FST::FST graph(string, 1,
				FST::NODE(1,
					FST::RELATION('/', 0)
				));
			if (result = execute(graph)) {
				return LEX_DIRSLASH;
			}

		}
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9':
		case '0':
		{
			FST::FST graph_digit(string, 1,
				FST::NODE(11,
					FST::RELATION('1', 0),
					FST::RELATION('2', 0),
					FST::RELATION('3', 0),
					FST::RELATION('4', 0),
					FST::RELATION('5', 0),
					FST::RELATION('6', 0),
					FST::RELATION('7', 0),
					FST::RELATION('8', 0),
					FST::RELATION('9', 0),
					FST::RELATION('0', 0),
					FST::RELATION('-', 0)
				));
			if (result = execute(graph_digit)) {
				return LEX_LITERAL;
			}

		}
		case ';':
		{
			FST::FST graph(string, 1,
				FST::NODE(1,
					FST::RELATION(';', 0)
				));
			if (result = execute(graph)) {
				return LEX_SEMICOLON;
			}

		}
		case '<':
		{
			FST::FST graph(string, 1,
				FST::NODE(1,
					FST::RELATION('<', 0)
				));
			if (result = execute(graph)) {
				return LEX_LESS;
				break;
			}

		}
		case '>':
		{
			FST::FST graph(string, 1,
				FST::NODE(1,
					FST::RELATION('<', 0)
				));
			if (result = execute(graph)) {
				return LEX_MORE;
				break;
			}

		}
		case '=':
		{
			FST::FST graph(string, 3,
				FST::NODE(1, FST::RELATION('=', 1)),
				FST::NODE(1, FST::RELATION('=', 2)),
				FST::NODE());
			if (result = execute(graph)) {
				return LEX_EQUALS;
			}

			FST::FST graph_assign(string, 1,
				FST::NODE(1,
					FST::RELATION('=', 0)
				));
			if (result = execute(graph_assign)) {
				return LEX_ASSIGN;
			}

		}case '!':
		{
			FST::FST graph(string, 3,
				FST::NODE(1, FST::RELATION('!', 1)),
				FST::NODE(1, FST::RELATION('=', 2)),
				FST::NODE());
			if (result = execute(graph)) {
				return LEX_NOT_EQUALS;
			}

		}
		case '^':
		{
			FST::FST graph(string, 1,
				FST::NODE(1,
					FST::RELATION('^', 0)
				));
			if (result = execute(graph)) {
				return LEX_XOR;
				break;
			}
		}
		case 'd':
		{
			FST::FST graph_date(string, 5,
				FST::NODE(1, FST::RELATION('d', 1)),
				FST::NODE(1, FST::RELATION('a', 2)),
				FST::NODE(1, FST::RELATION('t', 3)),
				FST::NODE(1, FST::RELATION('e', 4)),
				FST::NODE());
			if (result = execute(graph_date)) {
				entry->idtype = IT::IDTYPE::F;
				return LEX_ID;
				break;
			}

		}
		case 'f':
		{
			FST::FST graph_function(string, 9,
				FST::NODE(1, FST::RELATION('f', 1)),
				FST::NODE(1, FST::RELATION('u', 2)),
				FST::NODE(1, FST::RELATION('n', 3)),
				FST::NODE(1, FST::RELATION('c', 4)),
				FST::NODE(1, FST::RELATION('t', 5)),
				FST::NODE(1, FST::RELATION('i', 6)),
				FST::NODE(1, FST::RELATION('o', 7)),
				FST::NODE(1, FST::RELATION('n', 8)),
				FST::NODE());
			if (result = execute(graph_function)) {
				entry->idtype = IT::IDTYPE::F;
				return LEX_FUNCTION;
			}

		}
		case 'i':
		{
			FST::FST graph_include(string, 8,
				FST::NODE(1, FST::RELATION('i', 1)),
				FST::NODE(1, FST::RELATION('n', 2)),
				FST::NODE(1, FST::RELATION('c', 3)),
				FST::NODE(1, FST::RELATION('l', 4)),
				FST::NODE(1, FST::RELATION('u', 5)),
				FST::NODE(1, FST::RELATION('d', 6)),
				FST::NODE(1, FST::RELATION('e', 7)),
				FST::NODE());
			if (result = execute(graph_include)) {
				return LEX_ID;
				break;
			}

		}
		case 'm':
		{
			FST::FST graph_main(string, 5,
				FST::NODE(1, FST::RELATION('m', 1)),
				FST::NODE(1, FST::RELATION('a', 2)),
				FST::NODE(1, FST::RELATION('i', 3)),
				FST::NODE(1, FST::RELATION('n', 4)),
				FST::NODE());
			if (result = execute(graph_main)) {
				//entry->iddatatype = IT::IDDATATYPE::INT;
				entry->idtype = IT::IDTYPE::F;
				return LEX_MAIN;
			}
		}
		case 'r':
		{
			FST::FST graph_randome(string, 8,
				FST::NODE(1, FST::RELATION('r', 1)),
				FST::NODE(1, FST::RELATION('a', 2)),
				FST::NODE(1, FST::RELATION('n', 3)),
				FST::NODE(1, FST::RELATION('d', 4)),
				FST::NODE(1, FST::RELATION('o', 5)),
				FST::NODE(1, FST::RELATION('m', 6)),
				FST::NODE(1, FST::RELATION('e', 7)),
				FST::NODE());
			if (result = execute(graph_randome)) {
				entry->idtype = IT::IDTYPE::F;
				return LEX_ID;
				break;
			}
			FST::FST graph_return(string, 7,
				FST::NODE(1, FST::RELATION('r', 1)),
				FST::NODE(1, FST::RELATION('e', 2)),
				FST::NODE(1, FST::RELATION('t', 3)),
				FST::NODE(1, FST::RELATION('u', 4)),
				FST::NODE(1, FST::RELATION('r', 5)),
				FST::NODE(1, FST::RELATION('n', 6)),
				FST::NODE());
			if (result = execute(graph_return)) {
				return LEX_RETURN;
				break;
			}

		}
		case 'u':
		{
			FST::FST graph_uint(string, 5,
				FST::NODE(1, FST::RELATION('u', 1)),
				FST::NODE(1, FST::RELATION('i', 2)),
				FST::NODE(1, FST::RELATION('n', 3)),
				FST::NODE(1, FST::RELATION('t', 4)),
				FST::NODE());
			if (result = execute(graph_uint)) {
				return LEX_INTEGER;
				break;
			}
			FST::FST graph_ubyte(string, 6,
				FST::NODE(1, FST::RELATION('u', 1)),
				FST::NODE(1, FST::RELATION('b', 2)),
				FST::NODE(1, FST::RELATION('y', 3)),
				FST::NODE(1, FST::RELATION('t', 4)),
				FST::NODE(1, FST::RELATION('e', 5)),
				FST::NODE());
			if (result = execute(graph_ubyte)) {
				return LEX_BYTE;
				break;
			}

		}
		case 's':
		{
			FST::FST graph_string(string, 7,
				FST::NODE(1, FST::RELATION('s', 1)),
				FST::NODE(1, FST::RELATION('t', 2)),
				FST::NODE(1, FST::RELATION('r', 3)),
				FST::NODE(1, FST::RELATION('i', 4)),
				FST::NODE(1, FST::RELATION('n', 5)),
				FST::NODE(1, FST::RELATION('g', 6)),
				FST::NODE());
			if (result = execute(graph_string)) {
				return LEX_STRING;
				break;
			}

		}
		case 'w':
		{
			FST::FST graph_write(string, 6,
				FST::NODE(1, FST::RELATION('w', 1)),
				FST::NODE(1, FST::RELATION('r', 2)),
				FST::NODE(1, FST::RELATION('i', 3)),
				FST::NODE(1, FST::RELATION('t', 4)),
				FST::NODE(1, FST::RELATION('e', 5)),
				FST::NODE());
			if (result = execute(graph_write)) {
				return LEX_WRITE;
				break;
			}
			FST::FST graph_writeline(string, 10,
				FST::NODE(1, FST::RELATION('w', 1)),
				FST::NODE(1, FST::RELATION('r', 2)),
				FST::NODE(1, FST::RELATION('i', 3)),
				FST::NODE(1, FST::RELATION('t', 4)),
				FST::NODE(1, FST::RELATION('e', 5)),
				FST::NODE(1, FST::RELATION('l', 6)),
				FST::NODE(1, FST::RELATION('i', 7)),
				FST::NODE(1, FST::RELATION('n', 8)),
				FST::NODE(1, FST::RELATION('e', 9)),
				FST::NODE());
			if (result = execute(graph_writeline)) {
				return LEX_WRITEL;
				break;
			}
		}
		case '{':
		{
			FST::FST graph(string, 1,
				FST::NODE(1,
					FST::RELATION('{', 0)
				));
			if (result = execute(graph)) {
				return LEX_LEFTBRACE;
			}

		}
		case '}':
		{
			FST::FST graph(string, 1,
				FST::NODE(1,
					FST::RELATION('}', 0)
				));
			if (result = execute(graph)) {
				return LEX_RIGHTBRACE;
			}

		}
		case '~':
		{
			FST::FST graph(string, 1,
				FST::NODE(1,
					FST::RELATION('~', 0)
				));
			if (result = execute(graph)) {
				return LEX_INVERSION;
				break;
			}
		}

		default:
		{
			FST::FST graph_identificator(string, 1,
				FST::NODE(26,
					FST::RELATION('a', 0),
					FST::RELATION('b', 0),
					FST::RELATION('c', 0),
					FST::RELATION('d', 0),
					FST::RELATION('e', 0),
					FST::RELATION('f', 0),
					FST::RELATION('g', 0),
					FST::RELATION('h', 0),
					FST::RELATION('i', 0),
					FST::RELATION('j', 0),
					FST::RELATION('k', 0),
					FST::RELATION('l', 0),
					FST::RELATION('m', 0),
					FST::RELATION('n', 0),
					FST::RELATION('o', 0),
					FST::RELATION('p', 0),
					FST::RELATION('q', 0),
					FST::RELATION('r', 0),
					FST::RELATION('s', 0),
					FST::RELATION('t', 0),
					FST::RELATION('u', 0),
					FST::RELATION('v', 0),
					FST::RELATION('w', 0),
					FST::RELATION('x', 0),
					FST::RELATION('y', 0),
					FST::RELATION('z', 0)),
				FST::NODE());
			if (result = execute(graph_identificator)) {
				return LEX_ID;
				break;
			}
		}
		}
		return 0;
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