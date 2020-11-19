#include "generator_graphs.h"

constexpr auto LEXEMA_FIXSIZE = 3;			// фиксированный размер лексемы;
constexpr auto NAMEFILE = "graphs_in.txt";	// название входного файла
constexpr auto NAMEOUTFILE = "graphs.h";	// название для печати графов
constexpr auto SYMBOL_END_DEFINED = "";//'\\';	// 
constexpr auto FORMAT_TAB_1 = '\t';
constexpr auto FORMAT_TAB_2 = "\t\t";
constexpr auto FORMAT_TAB_3 = "\t\t\t";
constexpr auto FORMAT_TAB_4 = "\t\t\t\t";
constexpr auto FORMAT_TAB_5 = "\t\t\t\t\t";
constexpr auto STEP_FOR_DIGIT = 1;
constexpr auto SIGN_STRING = '\'';
constexpr auto SIGN_STRING_OUT = "\\\'";
constexpr unsigned char SIGN_IDENTIFICATOR = '$';
constexpr unsigned char NEXT_WORD = '#';
//constexpr unsigned char LOTCASES = '@';

using namespace std;

std::fstream fout(NAMEOUTFILE, std::ios_base::out);


int main()
{
	setlocale(LC_ALL, "rus");
	GRAPH graph[128];
	char text[1024];

	read_file(NAMEFILE, text);
	
	char* word;									//слово из массива
	char sep[] = "|";							//массимв символов по которым ищем
	bool switcher = true;						//ключевое слово или возвращаемый тип
	int quantity_graph = 0;		
	int position_keyword = 0;
	
	word = strtok(text, sep);					//выделяем первую цепочку

	while (word)
	{
		if (switcher) {
	
			strcpy(graph[quantity_graph].keyword, word);
			switcher = false;		
		}
		else {
			strcpy(graph[quantity_graph].retchar, word);
			switcher = true;
			quantity_graph++;
		}
		word = strtok(NULL, sep);		
	}

	sort_graphs(graph, quantity_graph);
	
	
	constructor_graphs_wordkeys(graph, quantity_graph);
		

	

	for (int i = 0;i < quantity_graph; i++) 
	{
		cout << endl;
		cout << "GRAPH " << i << endl;
		cout << graph[i].keyword << endl;
		cout << graph[i].retchar << endl;
	}
	
}

void read_file(const char* file, char* text) {

	std::fstream fin(file, std::ios_base::in);
	if (fin.fail())
		cout << "Ошибка открытия файла";

	bool startAnalises = false;
	bool next_word = false;
	int position_arr = 0;
	int position_digi = 0;
	bool all_symbols_read = false;

	for (unsigned char symbol; symbol = fin.get();)
	{
		if (fin.eof())
			break;

		if (symbol == '\n') {
			startAnalises = true;
			next_word = false;
		}

		if(symbol == NEXT_WORD)
		{
				text[position_arr++] = '|';
				continue;
		}

		if (symbol == SIGN_STRING)
		{
			if (all_symbols_read) all_symbols_read = false;
			else all_symbols_read = true;
		}
		if(isspace(symbol) && !all_symbols_read)
			continue;

		if (startAnalises) {
			text[position_arr++] = symbol;
		}

		if (!isalnum(symbol) && next_word) {
			
			
			next_word = false;
		}

	}
	text[position_arr] = '\0';
	cout << text;
	fin.close();
}

void sort_graphs(GRAPH* graph, int size) {

	GRAPH temp;

	for (int j = 0; j < size- 1; j++) {

		for (int i = 0; i < size - 1 - j; i++) {
			
				if (graph[i].keyword[0] > graph[i + 1].keyword[0])
				{
					temp = graph[i];
					graph[i] = graph[i + 1];
					graph[i + 1] = temp;
				}

		}

	}
		cout << "complete sort" << endl;

}

void constructor_graphs_wordkeys(GRAPH* graph,int size) {

	if (fout.fail())
		cout << "Ошибка открытия файла";

	 bool new_case = true;
	 bool print_default = false;
	 int default_index_in_graph = 0;

		fout << "#define ANALISES_TOKEN" << SYMBOL_END_DEFINED << endl;
		fout << FORMAT_TAB_1 <<  "switch(string[0]){" << SYMBOL_END_DEFINED << endl;


		for (size_t index = 0; index < size; index++)
		{
			if (graph[index].keyword[0] == SIGN_IDENTIFICATOR)
			{
				print_default = true;
				default_index_in_graph = index;
				continue;
			}
			else if (isalpha(graph[index].keyword[0])) {

				if (new_case){
					fout << FORMAT_TAB_2 << "case \'" << graph[index].keyword[0] << "\' :" << SYMBOL_END_DEFINED << endl;
					fout << FORMAT_TAB_2 << "{" << SYMBOL_END_DEFINED << endl;
				}

				fout << FORMAT_TAB_4 << "FST::FST graph_" << graph[index].keyword << "(" << "string," << (strlen(graph[index].keyword) + 1) << "," << SYMBOL_END_DEFINED << endl;

				for (int j = 0; j < (strlen(graph[index].keyword) + 1); j++) {

					if (j == (strlen(graph[index].keyword))) {
						fout << FORMAT_TAB_4 << "FST::NODE());" << SYMBOL_END_DEFINED << endl;
						break;
					}

					fout << FORMAT_TAB_4 << "FST::NODE(1, FST::RELATION('" << graph[index].keyword[j] << "'," << (j + 1) << "))," << SYMBOL_END_DEFINED << endl;
				}

				fout << FORMAT_TAB_2 << "if (result = execute(graph_" << graph[index].keyword << ")) {" << SYMBOL_END_DEFINED << endl;
				fout << FORMAT_TAB_3 << "return " << graph[index].retchar << ";" << SYMBOL_END_DEFINED << endl;
				fout << FORMAT_TAB_3 << "break;" << SYMBOL_END_DEFINED << endl;
				fout << FORMAT_TAB_2 << "}" << SYMBOL_END_DEFINED << endl;

				if ((graph[index].keyword[0] == graph[index + 1].keyword[0]))
					new_case = false;
				else {
					fout << FORMAT_TAB_2 /*<< "break;"*/ << SYMBOL_END_DEFINED << endl << "}" << SYMBOL_END_DEFINED << endl;
					new_case = true;
				}
			}
			else if (isdigit(graph[index].keyword[0])) {
				if (new_case) {
					for(int i = 0; i < strlen(graph[index].keyword);i++)
					fout << FORMAT_TAB_2 << "case \'" << graph[index].keyword[i] << "\' :" << SYMBOL_END_DEFINED << endl;

					fout << FORMAT_TAB_2 << "{" << SYMBOL_END_DEFINED << endl;
				}

				fout << FORMAT_TAB_4 << "FST::FST graph_digit" << "(" << "string,"  << 1 << "," << SYMBOL_END_DEFINED << endl;
				fout << FORMAT_TAB_4 << "FST::NODE(" << strlen(graph[index].keyword) << "," << SYMBOL_END_DEFINED << endl;
				for (int j = 0; j < strlen(graph[index].keyword); j++) 
				{
					fout << FORMAT_TAB_5 << "FST::RELATION('" << graph[index].keyword[j] << "'," << 0;
					if((strlen(graph[index].keyword) -1)  == j)
						fout << ")" << SYMBOL_END_DEFINED << endl;
					else
						fout << ")," << SYMBOL_END_DEFINED << endl;

				}
				fout << FORMAT_TAB_4 << "));" << SYMBOL_END_DEFINED << endl;
				fout << FORMAT_TAB_2 << "if (result = execute(graph_digit)) {" << SYMBOL_END_DEFINED << endl;
				fout << FORMAT_TAB_3 << "return " << graph[index].retchar << ";" << SYMBOL_END_DEFINED << endl;
				fout << FORMAT_TAB_3 << "break;" << SYMBOL_END_DEFINED << endl;
				fout << FORMAT_TAB_2 << "}" << SYMBOL_END_DEFINED << endl;

				if ((graph[index].keyword[0] == graph[index + 1].keyword[0]))
					new_case = false;
				else {
					fout << FORMAT_TAB_2 /*<< "break;"*/ << SYMBOL_END_DEFINED << endl << "}" << SYMBOL_END_DEFINED << endl;
					new_case = true;
				}
			}
			else if (graph[index].keyword[0] == SIGN_STRING)
			{
				if (new_case) {
					fout << FORMAT_TAB_2 << "case \'" << SIGN_STRING_OUT << "\':" << SYMBOL_END_DEFINED << endl;
					fout << FORMAT_TAB_2 << "{" << SYMBOL_END_DEFINED << endl;
				}

				fout << FORMAT_TAB_4 << "FST::FST graph_literal" << "(" << "string," << 3 << "," << SYMBOL_END_DEFINED << endl;
				fout << FORMAT_TAB_4 << "FST::NODE(1," << "FST::RELATION('" << SIGN_STRING_OUT << "\', 1))," << SYMBOL_END_DEFINED << endl;;
				fout << FORMAT_TAB_4 << "FST::NODE(" << (strlen(graph[index].keyword) - 1) << "," << SYMBOL_END_DEFINED << endl;
				
				for (int j = 1;; j++) {

					if (graph[index].keyword[j] == SIGN_STRING)
						break;

					if (!j) continue;
					fout << FORMAT_TAB_5 << "FST::RELATION('" << graph[index].keyword[j] << "\',1";

						if ((strlen(graph[index].keyword) - 1) == j)
							fout << "))," << SYMBOL_END_DEFINED << endl;
						else
							fout << ")," << SYMBOL_END_DEFINED << endl;

				}
				fout << FORMAT_TAB_5 << "FST::RELATION('" << SIGN_STRING_OUT << "\',2))," << SYMBOL_END_DEFINED << endl;;
				fout << FORMAT_TAB_4 << "FST::NODE());" << SYMBOL_END_DEFINED << endl;

				fout << FORMAT_TAB_2 << "if (result = execute(graph_literal" << ")) {" << SYMBOL_END_DEFINED << endl;
				fout << FORMAT_TAB_3 << "return " << graph[index].retchar << ";" << SYMBOL_END_DEFINED << endl;
				fout << FORMAT_TAB_3 << "break;" << SYMBOL_END_DEFINED << endl;
				fout << FORMAT_TAB_2 << "}" << SYMBOL_END_DEFINED << endl;

				if ((graph[index].keyword[0] == graph[index + 1].keyword[0]))
					new_case = false;
				else {
					fout << FORMAT_TAB_2 /*<< "break;"*/ << SYMBOL_END_DEFINED << endl << "}" << SYMBOL_END_DEFINED << endl;
					new_case = true;
				}
			}
			else
			{
				fout << FORMAT_TAB_2 << "case \'" << graph[index].keyword[0] << "\':" << SYMBOL_END_DEFINED << endl;
				fout << FORMAT_TAB_2 << "{" << SYMBOL_END_DEFINED << endl;
				fout << FORMAT_TAB_4 << "FST::FST graph" << /*<< graph[index].retchar <<*/ "(" << "string,"  << 1 << "," << SYMBOL_END_DEFINED << endl;
				fout << FORMAT_TAB_4 << "FST::NODE(1," << SYMBOL_END_DEFINED << endl; ;
				fout << FORMAT_TAB_5  << "FST::RELATION('" << graph[index].keyword[0] << "',0)" << SYMBOL_END_DEFINED << endl;
				fout << FORMAT_TAB_4 << "));" << SYMBOL_END_DEFINED << endl;
				fout << FORMAT_TAB_2 << "if (result = execute(graph" /*<< graph[index].retchar*/ << ")) {" << SYMBOL_END_DEFINED << endl;
				fout << FORMAT_TAB_3 << "return ";
				if (strlen(graph[index].retchar) == 1)
					fout << '\'' << graph[index].retchar << "';" << SYMBOL_END_DEFINED << endl;
				else
				fout << graph[index].retchar << ";" << SYMBOL_END_DEFINED << endl;
				fout << FORMAT_TAB_3 << "break;" << SYMBOL_END_DEFINED << endl;
				fout << FORMAT_TAB_2 << "}" << SYMBOL_END_DEFINED << endl;

				if ((graph[index].keyword[0] == graph[index + 1].keyword[0]))
					new_case = false;
				else {
					fout << FORMAT_TAB_2 /* << "break;"*/ << SYMBOL_END_DEFINED << endl << "}" << SYMBOL_END_DEFINED << endl;
					new_case = true;
				}
			}
		
			
		}

		if (print_default){
			fout << FORMAT_TAB_2 << "default" << ":" << SYMBOL_END_DEFINED << endl;

			fout << FORMAT_TAB_2 << "{" << SYMBOL_END_DEFINED << endl;

			fout << FORMAT_TAB_3 << "FST::FST graph_identificator" << "(" << "string,"  << 1 << "," << SYMBOL_END_DEFINED << endl;
			fout << FORMAT_TAB_4 << "FST::NODE(" << (strlen(graph[default_index_in_graph].keyword) - 1) << "," << SYMBOL_END_DEFINED << endl;;
			for (int j = 1; j < strlen(graph[default_index_in_graph].keyword); j++) {
				fout << FORMAT_TAB_5 << "FST::RELATION('" << graph[default_index_in_graph].keyword[j] << "'," << 0;
					if ((strlen(graph[default_index_in_graph].keyword) - 1) == j)
					 fout << "))," << SYMBOL_END_DEFINED << endl;
					else
					 fout << ")," << SYMBOL_END_DEFINED << endl;
			}
			fout << FORMAT_TAB_4 << "FST::NODE());" << SYMBOL_END_DEFINED << endl;
			fout << FORMAT_TAB_2 << "if (result = execute(graph_identificator)) {" << SYMBOL_END_DEFINED << endl;
			fout << FORMAT_TAB_3 << "return " << graph[default_index_in_graph].retchar << ";" << SYMBOL_END_DEFINED << endl;
			fout << FORMAT_TAB_3 << "break;" << SYMBOL_END_DEFINED << endl;
			fout << FORMAT_TAB_2 << "}" << SYMBOL_END_DEFINED << endl;

			if ((graph[default_index_in_graph].keyword[0] == graph[default_index_in_graph + 1].keyword[0]))
				new_case = false;

			else {
				fout << FORMAT_TAB_2/* << "break;"*/ << SYMBOL_END_DEFINED << endl << "}" << SYMBOL_END_DEFINED << endl;
				new_case = true;
			}
		}
	fout << FORMAT_TAB_1 << "}" << SYMBOL_END_DEFINED << endl;

	fout.close();
}
