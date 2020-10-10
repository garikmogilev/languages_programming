#pragma once
#pragma warning(disable : 4996)
#include <list>
#include <limits>

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
#include "DP.h"				//	обработка данных
#include "FST.h"
#include "Out.h"
#include "LT.h"
#include "IT.h"

//#define TEST1				//  проверка ERROR
//#define TEST2				//  проверка PARM
//#define TEST3				//  проверка IN
//#define TEST4				//  проверка IN другой тип ошибок
#define TEST5				//	проверка LOG