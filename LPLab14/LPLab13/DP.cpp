#include "stdafx.h"
#define TOKEN token_rekognizer(string)

#include "../generator_graphs/graphs.h"


namespace GM
{
	void dataProcesing(unsigned char* text, wchar_t* out, std::fstream* stream, LT::LexTable* lextable,IT::IdTable* idtable)
	{
		std::fstream fout(out, std::ios::out);
		unsigned char* start = text;
		unsigned char* end = start;
		bool switch_string = false;
		int count_lines = 0;
		int count_lexems = 0;
		char token;
		char prefix[ID_MAXSIZE + 1];
		char identificator[ID_MAXSIZE + 1];

		while (true)
		{
			if (!*end) break;

				if ((!alphaCirillicDigit (*end) || !isalnum(*start)) && !switch_string)
				{
					char* string = new  char[end - start + 2];
					strncpy(string, (char*)start, end - start);
					string[end - start] = STR_ENDL;

					token = token_rekognizer(string, idtable);

					LT::Entry entry = LT::Create(token, count_lines);
					//IT::GetEntry 
					if (entry.lexema[0] == LEX_ID) {
						strncpy(idtable->table->id, string, ID_MAXSIZE);
						entry.idxTI = count_lexems;
					}
					else
						entry.idxTI = LT_TI_NULLXDX;
 
					LT::Add(lextable, entry);


					if (entry.lexema[0] == LEX_ID) {
						if ((idtable->table[idtable->current_size].iddatatype) && (idtable->table[idtable->current_size].idtype))
							strncpy_s(idtable->table[idtable->current_size++].id, string, ID_MAXSIZE);
						else if (idtable->table[idtable->current_size].iddatatype)
						{
							idtable->table[idtable->current_size].idtype = IT::IDTYPE::P;
							strncpy_s(idtable->table[idtable->current_size++].id, string, ID_MAXSIZE);
						}
						else
						{
							idtable->table[idtable->current_size].idtype = IT::IDTYPE::L;
						}
						std::cout << idtable->table[idtable->current_size - 1].id << std::endl;
					}
					start = end;
					count_lexems++;

					delete[] string;
				}
				
				

				if (*end == '\'') {
					if (switch_string)
						switch_string = false;
					else
						switch_string = true;
				}

				if ((*end == SPACE || *end == SEPARATER) && !switch_string) {
					if (*end == SEPARATER)
						count_lines++;
					start = end;
					start++;
					end = start;
				}
			end++;

		}

		for (size_t i = 0; i < idtable->current_size; i++)
		{
			std::cout << "IDentif" << i << std::endl;
			std::cout << "dt: " << idtable->table[i].iddatatype << std::endl;
			std::cout << "dd: " << idtable->table[i].idtype << std::endl;
			std::cout << "id: " << idtable->table[i].id << std::endl;


		}
		
		int uqu = 0;
		fout.width(4);
		fout.setf(std::ios::left);
		fout << lextable->table[0].sn;
		for (size_t i = 0; i < lextable->size; i++)
		{
			if (uqu != lextable->table[i].sn) {
				fout << std::endl;
				fout.width(4);
				fout.setf(std::ios::left);
				fout << lextable->table[i].sn;
				uqu = lextable->table[i].sn;
			}
			fout << lextable->table[i].lexema;
		}
	}


char token_rekognizer(char* string, IT::IdTable* idtable) {
	bool result = false;

	switch (string[0]) {
		case '\'':
		{
			FST::FST graph_literal(string, 3,
				FST::NODE(1, FST::RELATION('\'', 1)),
				FST::NODE(35,
					FST::RELATION('a', 1),
					FST::RELATION('b', 1),
					FST::RELATION('c', 1),
					FST::RELATION('d', 1),
					FST::RELATION('e', 1),
					FST::RELATION('f', 1),
					FST::RELATION('g', 1),
					FST::RELATION('h', 1),
					FST::RELATION('k', 1),
					FST::RELATION('l', 1),
					FST::RELATION('m', 1),
					FST::RELATION('n', 1),
					FST::RELATION('o', 1),
					FST::RELATION('p', 1),
					FST::RELATION('q', 1),
					FST::RELATION('r', 1),
					FST::RELATION('s', 1),
					FST::RELATION('t', 1),
					FST::RELATION('u', 1),
					FST::RELATION('v', 1),
					FST::RELATION('w', 1),
					FST::RELATION('x', 1),
					FST::RELATION('y', 1),
					FST::RELATION('z', 1),
					FST::RELATION('1', 1),
					FST::RELATION('2', 1),
					FST::RELATION('3', 1),
					FST::RELATION('4', 1),
					FST::RELATION('5', 1),
					FST::RELATION('6', 1),
					FST::RELATION('7', 1),
					FST::RELATION('8', 1),
					FST::RELATION('9', 1),
					FST::RELATION('0', 1),
					FST::RELATION('\'',2)),
						FST::NODE());
			if (result = execute(graph_literal)) {
				return LEX_LITERAL;
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
				FST::NODE(10,
					FST::RELATION('1', 0),
					FST::RELATION('2', 0),
					FST::RELATION('3', 0),
					FST::RELATION('4', 0),
					FST::RELATION('5', 0),
					FST::RELATION('6', 0),
					FST::RELATION('7', 0),
					FST::RELATION('8', 0),
					FST::RELATION('9', 0),
					FST::RELATION('0', 0)
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
		case '=':
		{
			FST::FST graph(string, 1,
				FST::NODE(1,
					FST::RELATION('=', 0)
				));
			if (result = execute(graph)) {
				return LEX_EQUALS;
			}

		}
		case '^':
		{
			FST::FST graph(string, 1,
				FST::NODE(1,
					FST::RELATION('^', 0)
				));
			if (result = execute(graph)) {
				return '^';
			}

		}
		case 'd':
		{
			FST::FST graph_declare(string, 8,
				FST::NODE(1, FST::RELATION('d', 1)),
				FST::NODE(1, FST::RELATION('e', 2)),
				FST::NODE(1, FST::RELATION('c', 3)),
				FST::NODE(1, FST::RELATION('l', 4)),
				FST::NODE(1, FST::RELATION('a', 5)),
				FST::NODE(1, FST::RELATION('r', 6)),
				FST::NODE(1, FST::RELATION('e', 7)),
				FST::NODE());
			if (result = execute(graph_declare)) {
				idtable->table[idtable->current_size].idtype = IT::IDTYPE::V;
				return LEX_DECLARE;
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
				idtable->table[idtable->current_size].idtype = IT::IDTYPE::F;
				return LEX_FUNCTION;
			}

		}
		case 'i':
		{
			FST::FST graph_integer(string, 8,
				FST::NODE(1, FST::RELATION('i', 1)),
				FST::NODE(1, FST::RELATION('n', 2)),
				FST::NODE(1, FST::RELATION('t', 3)),
				FST::NODE(1, FST::RELATION('e', 4)),
				FST::NODE(1, FST::RELATION('g', 5)),
				FST::NODE(1, FST::RELATION('e', 6)),
				FST::NODE(1, FST::RELATION('r', 7)),
				FST::NODE());
			if (result = execute(graph_integer)) {
				idtable->table[idtable->current_size].iddatatype = IT::IDDATATYPE::INT;
				return LEX_INTEGER;
			}
			FST::FST graph_if(string, 3,
				FST::NODE(1, FST::RELATION('i', 1)),
				FST::NODE(1, FST::RELATION('f', 2)),
				FST::NODE());
			if (result = execute(graph_if)) {
				return LEX_IF;
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
				idtable->table[idtable->current_size].idtype = IT::IDTYPE::F;
				return LEX_MAIN;
			}

		}
		case 'p':
		{
			FST::FST graph_print(string, 6,
				FST::NODE(1, FST::RELATION('p', 1)),
				FST::NODE(1, FST::RELATION('r', 2)),
				FST::NODE(1, FST::RELATION('i', 3)),
				FST::NODE(1, FST::RELATION('n', 4)),
				FST::NODE(1, FST::RELATION('t', 5)),
				FST::NODE());
			if (result = execute(graph_print)) {
				return LEX_PRINT;
			}

		}
		case 'r':
		{
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
				idtable->table[idtable->current_size].iddatatype = IT::IDDATATYPE::STR;
				return LEX_STRING;
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