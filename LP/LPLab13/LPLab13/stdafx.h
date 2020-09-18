#pragma once
#pragma warning(suppress : 4996)
#include <tchar.h>
#include <time.h>
#include <wchar.h>
#include <locale>
#include <fstream>
#include <iostream>
#include "Error.h"			//	обработка ошибок
#include "Parm.h"			//	обработка параметров
#include "Log.h"			//	работа с протоколом
#include "In.h"				//	ввод исходного файла
#include "LT.h"				//	обработка лексем
#include "FST.h"
//#include "Out.h"
#include "DP.h"				//	обработка данных

//#define TEST1				//  проверка ERROR
//#define TEST2				//  проверка PARM
//#define TEST3				//  проверка IN
//#define TEST4				//  проверка IN другой тип ошибок
#define TEST5				//	проверка LOG