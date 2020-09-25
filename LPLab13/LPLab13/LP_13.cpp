#include "stdafx.h"

int _tmain(int argc, _TCHAR* argv[])
{
	setlocale(LC_ALL, "rus");
		 
#ifdef TEST1
	std::cout << "---- тест Error::geterror ----" << std::endl << std::endl;
	try { throw ERROR_THROW(-1); }
	catch (Error::ERROR e)
	{
		std::cout << "Ошибка " << e.id << ": " << e.message << std::endl << std::endl;
	};

	std::cout << "---- тест Error::geterrorin ----" << std::endl << std::endl;
	try { throw ERROR_THROW_IN(1001, 7, 7); }
	catch (Error::ERROR e)
	{
		std::cout << "Ошибка " << e.id << ": " << e.message
			<< ", строка " << e.inext.line
			<< ", позиция " << e.inext.col << std::endl << std::endl;
	}
#endif //TEST1 

#ifdef TEST2
	std::cout << "---- тест Parm::getparm ----" << std::endl << std::endl;
	try
	{
		Parm::PARM parm = Parm::getparm(argc, argv);
		std::wcout << PARM_IN << parm.in << " " << PARM_OUT << parm.out << " " << PARM_LOG << parm.log << std::endl << std::endl;
	}
	catch (Error::ERROR e)
	{
		std::cout << "Оши6ка " << e.id << ": " << e.message << std::endl << std::endl;
	};

#endif // TEST2

#ifdef TEST3
	std::cout << "---- тест In::getin ----" << std::endl << std::endl;
	try
	{
		Parm::PARM parm = Parm::getparm(argc, argv);
		In::IN in = In::getin(parm.in);

		std::cout << in.text << std::endl;
		std::cout << "Всего символов: " << in.size << std::endl;
		std::cout << "Всего строк: " << in.lines << std::endl;
		std::cout << "Пропущено: " << in.ignor << std::endl;

	}

	catch (Error::ERROR e)
	{
		std::cout << "Ошибка " << e.id << ": " << e.message << std::endl << std::endl;
	}
#endif // TEST3


#ifdef TEST4
	std::cout << "---- тест In::getin ----" << std::endl << std::endl;
	try
	{
		Parm::PARM parm = Parm::getparm(argc, argv);
		In::IN in = In::getin(parm.in);
		std::cout << in.text << std::endl;
		std::cout << "Bcero символов: " << in.size << std::endl;
		std::cout << "Bcero строк: " << in.lines << std::endl;
		std::cout << "Пропущено: " << in.ignor << std::endl;
	}
	catch (Error::ERROR e)
	{
		std::cout << "Ошибка: " << e.id << ": " << e.message << std::endl;
		std::cout << "Строка: " << e.inext.line << " Позиция: " << e.inext.col << std::endl << std::endl;
	}
#endif // TEST4

#ifdef TEST5
		Log::LOG log = Log::INITLOG; 
	try {
		Parm::PARM parm = Parm::getparm(argc, argv); 
		log = Log::getlog(parm.log);
		Log::WriteLog(log);
		Log::WriteParm(log, parm);
		In::IN in = In::getin(parm.in);
		Log::WriteIn(log, in);
		Log::WriteLine(log, L"Файл: ", L"считан ", L"без ", L"ошибок ", L"");
		GM::dataProceesing(in.text, parm.out, log.stream);
		Log::Close(log);
		std::cout << in.text;
	}
	catch (Error::ERROR e)
	{
		Log::WriteError(log, e);
	};

#endif //TEST5
	
	system("pause");

	return 0;
}
