#pragma once
#pragma warning(disable : 4996)
#include <iostream>
#include <fstream>
#include <iostream>

struct GRAPH {
	char keyword[256];				//�������� �����
	char retchar[256];				//������������ ������
	bool count_stop = false;
};


void read_file(const char*, char*);
void sort_graphs(GRAPH*,int);
void constructor_graphs_wordkeys(GRAPH*, int);