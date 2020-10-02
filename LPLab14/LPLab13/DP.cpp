#include "stdafx.h"
#define TOKEN token_rekognizer(string, &entryIT);

#include "../generator_graphs/graphs.h"


namespace GM
{
	void dataProcesing(unsigned char* text, std::fstream* stream, LT::LexTable* lextable, IT::IdTable* idtable)
	{
		
		unsigned char* start = text;
		unsigned char* end = start;
		Data data;
		IT::Entry entryIT;
		while (true)
		{
			if (!*end) break;

				if ((!alphaCirillicDigit (*end) || !isalnum(*start)) && !data.switch_string)
				{
					char* string = new  char[end - start + 2];
					strncpy(string, (char*)start, end - start);
					string[end - start] = STR_ENDL;

					data.token = TOKEN;												// распознать лексему

					LT::Entry entryLT = LT::Create(data.token, data.count_lines, data.count);
					memset(entryIT.prefix, 0x00, PREFIX_SIZE);
					memset(entryIT.id, 0x00, ID_MAXSIZE);
					memset(entryIT.extFunct, 0x00, PREFIX_SIZE);

					if (data.token == LEX_RIGHTBRACE) { data.visibility = false, data.global = false; }
					if (data.token == LEX_DECLARE) data.global = true;

					if (data.token == LEX_LITERAL)
					{
						if (isdigit(string[0])) {
							int temp = atoi(string);
							if(temp > 2147483647 && temp < -2147483647)
								throw ERROR_THROW(121);
							if (IsLiteral(*idtable, temp) == LT_TI_NULLXDX  || !temp) {
								entryIT.idtype = IT::IDTYPE::L;
								entryIT.iddatatype = IT::IDDATATYPE::INT;
								entryIT.value.vint = temp;
								IT::Add(*idtable, entryIT);
								entryIT.iddatatype = IT::IDDATATYPE::NUL;
								entryIT.idtype = IT::IDTYPE::N;
							}
						}
						else
						{	
							int size = strlen(string);
							char temp[TI_STR_MAXSIZE];
							strncpy_s(temp, (string + 1), size - 2);
							if (size > TI_STR_MAXSIZE)
								throw ERROR_THROW(123);
							if (IsLiteral(*idtable, temp) == LT_TI_NULLXDX) {
								entryIT.idtype = IT::IDTYPE::L;
								entryIT.iddatatype = IT::IDDATATYPE::STR;
								strcpy_s(entryIT.value.vstr->str,temp);
								entryIT.value.vstr->len = (char)(size);
								IT::Add(*idtable, entryIT);
								entryIT.iddatatype = IT::IDDATATYPE::NUL;
								entryIT.idtype = IT::IDTYPE::N;
							}
						}

					}

					if (data.token == LEX_ID || data.token == LEX_MAIN) {

						if ((entryIT.idtype == IT::IDTYPE::F) && (entryIT.iddatatype))
						{
							strncpy_s(data.prefix, string, PREFIX_SIZE);
							data.visibility = true;

							if (data.global) {							// было объ€влнено внешн€€ функци€ или перременна
								strcpy_s(entryIT.prefix, VISIBLE_GLOBAL);
								strncpy_s(entryIT.extFunct, string, EXT_FUNCTION);
							}
							else
							strncpy_s(entryIT.id, string, ID_MAXSIZE);

							IT::Add(*idtable, entryIT);
						}
						else if (entryIT.idtype == IT::IDTYPE::V && entryIT.iddatatype)
						{	
							if(data.visibility)
							strncpy_s(entryIT.prefix, data.prefix, PREFIX_SIZE);
							strncpy_s(entryIT.id, string, ID_MAXSIZE);
							IT::Add(*idtable, entryIT);
						}
						else if (entryIT.iddatatype)
						{
							entryIT.idtype = IT::IDTYPE::P;
							if(data.visibility)
								strncpy_s(entryIT.prefix, data.prefix, PREFIX_SIZE);
							strncpy_s(entryIT.id,string,ID_MAXSIZE);
							IT::Add(*idtable, entryIT);
						}
						if (entryIT.iddatatype)	data.count++;

						entryIT.iddatatype = IT::IDDATATYPE::NUL;
						entryIT.idtype = IT::IDTYPE::N;
					}

					LT::Add(lextable, entryLT);
					start = end;
					delete[] string;
				}
				
				if (*end == '\'') {
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


char token_rekognizer(char* string, IT::Entry* entry) {
	bool result = false;

	switch (string[0]) {
		case '\'':
		{
			FST::FST graph_literal(string, 3,
				FST::NODE(1, FST::RELATION('\'', 1)),
				FST::NODE(67,
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
					FST::RELATION(' ', 1),
					FST::RELATION('а', 1),
					FST::RELATION('б', 1),
					FST::RELATION('в', 1),
					FST::RELATION('г', 1),
					FST::RELATION('д', 1),
					FST::RELATION('е', 1),
					FST::RELATION('Є', 1),
					FST::RELATION('ж', 1),
					FST::RELATION('з', 1),
					FST::RELATION('и', 1),
					FST::RELATION('к', 1),
					FST::RELATION('л', 1),
					FST::RELATION('м', 1),
					FST::RELATION('н', 1),
					FST::RELATION('о', 1),
					FST::RELATION('п', 1),
					FST::RELATION('р', 1),
					FST::RELATION('с', 1),
					FST::RELATION('т', 1),
					FST::RELATION('у', 1),
					FST::RELATION('ф', 1),
					FST::RELATION('х', 1),
					FST::RELATION('ц', 1),
					FST::RELATION('ч', 1),
					FST::RELATION('ш', 1),
					FST::RELATION('щ', 1),
					FST::RELATION('ъ', 1),
					FST::RELATION('ь', 1),
					FST::RELATION('э', 1),
					FST::RELATION('ю', 1),
					FST::RELATION('€', 1),
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
				entry->idtype = IT::IDTYPE::V;
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
				entry->idtype = IT::IDTYPE::F;
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
				entry->iddatatype = IT::IDDATATYPE::INT;
				return LEX_INTEGER;
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
				entry->iddatatype = IT::IDDATATYPE::INT;
				entry->idtype = IT::IDTYPE::F;
				return LEX_ID; 
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
			FST::FST graph_strlen(string, 7, 
				FST::NODE(1, FST::RELATION('s', 1)), 
				FST::NODE(1, FST::RELATION('t', 2)), 
				FST::NODE(1, FST::RELATION('r', 3)), 
				FST::NODE(1, FST::RELATION('l', 4)), 
				FST::NODE(1, FST::RELATION('e', 5)), 
				FST::NODE(1, FST::RELATION('n', 6)), 
				FST::NODE()); 
			if (result = execute(graph_strlen)) {
				entry->idtype = IT::IDTYPE::F;
					return LEX_ID; 
			}
				FST::FST graph_substr(string, 7, 
					FST::NODE(1, FST::RELATION('s', 1)), 
					FST::NODE(1, FST::RELATION('u', 2)), 
					FST::NODE(1, FST::RELATION('b', 3)), 
					FST::NODE(1, FST::RELATION('s', 4)), 
					FST::NODE(1, FST::RELATION('t', 5)), 
					FST::NODE(1, FST::RELATION('r', 6)), 
					FST::NODE()); 
					if (result = execute(graph_substr)) {
						entry->idtype = IT::IDTYPE::F;
							return LEX_ID; 
					}
				FST::FST graph_string(string, 7, 
					FST::NODE(1, FST::RELATION('s', 1)), 
					FST::NODE(1, FST::RELATION('t', 2)), 
					FST::NODE(1, FST::RELATION('r', 3)), 
					FST::NODE(1, FST::RELATION('i', 4)), 
					FST::NODE(1, FST::RELATION('n', 5)), 
					FST::NODE(1, FST::RELATION('g', 6)), 
					FST::NODE()); 
					if (result = execute(graph_string)) {
						entry->iddatatype = IT::IDDATATYPE::STR;
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
		else if (symbol >= 'а' && symbol <= '€')
			return true;
		else
			return false;
	}
}