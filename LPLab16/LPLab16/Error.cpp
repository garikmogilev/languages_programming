#include "stdafx.h" 

namespace Error
{
	/************************************************************************/
	/*				|	0	- 99	|	��������� ������					*/
	/*				|---------------|---------------------------------------*/
	/* ����� ������ |	100	- 109	|	������ ����������					*/
	/*				|---------------|---------------------------------------*/
	/*				|	110	- 119	|	������ �������� � ������ ������		*/
	/*				|---------------|---------------------------------------*/
	/*				|	120	- 129	|	������ ��� ������� ������			*/
	/************************************************************************/

	ERROR errors[ERROR_MAX_ENTRY] = //������� ������
	{
		ERROR_ENTRY(0, "������������ ��� ������"),
		ERROR_ENTRY(1, "��������� ����"),
		ERROR_ENTRY_NODEF(2), ERROR_ENTRY_NODEF(3), ERROR_ENTRY_NODEF(4), ERROR_ENTRY_NODEF(5),
		ERROR_ENTRY_NODEF(6), ERROR_ENTRY_NODEF(7), ERROR_ENTRY_NODEF(8), ERROR_ENTRY_NODEF(9),
		ERROR_ENTRY_NODEF10(10), ERROR_ENTRY_NODEF10(20), ERROR_ENTRY_NODEF10(30), ERROR_ENTRY_NODEF10(40), ERROR_ENTRY_NODEF10(50),
		ERROR_ENTRY_NODEF10(60), ERROR_ENTRY_NODEF10(70), ERROR_ENTRY_NODEF10(80), ERROR_ENTRY_NODEF10(90),
		ERROR_ENTRY(100, "�������� -in ������ ���� �����"),
		ERROR_ENTRY(101, "������, ���������� ������� �����"), ERROR_ENTRY_NODEF(102),ERROR_ENTRY_NODEF(103),
		ERROR_ENTRY(104, "��������� ����� �������� ���������"),
		ERROR_ENTRY_NODEF(105), ERROR_ENTRY_NODEF(106), ERROR_ENTRY_NODEF(107),
		ERROR_ENTRY_NODEF(108), ERROR_ENTRY_NODEF(109),
		ERROR_ENTRY(110, "������ ��� �������� ����� � �������� ����� (-in)"),
		ERROR_ENTRY(111, "������������ ������ � �������� ����� (-in)"),
		ERROR_ENTRY(112, "������ ��� �������� ����� ���������(-log)"),
		ERROR_ENTRY(113,"������ ��� �������� ����� ��� ������"),
		ERROR_ENTRY(114,"������, � ����������� ������� ��� ���������"),
		ERROR_ENTRY_NODEF(115),
		ERROR_ENTRY_NODEF(116), ERROR_ENTRY_NODEF(117), ERROR_ENTRY_NODEF(118), ERROR_ENTRY_NODEF(119),
		ERROR_ENTRY(120,"�������� ������ ������� ������"),
		ERROR_ENTRY(121,"�������� �������� ���� integer"),
		ERROR_ENTRY(122,"�������� ������ ������� ���������������"),
		ERROR_ENTRY(123,"��������� ����� ������"),
		ERROR_ENTRY(124,"��������� �������� ����� ��� �������"),
		ERROR_ENTRY(125,"����������������� �������"),
		ERROR_ENTRY(126,"����������������� ����������"),
		ERROR_ENTRY(127,"�� ������ ��� ��� �������"),
		ERROR_ENTRY(128,"�� ���������� �������"),
		ERROR_ENTRY_NODEF(129),
		ERROR_ENTRY_NODEF10(130), ERROR_ENTRY_NODEF10(140), ERROR_ENTRY_NODEF10(150),
		ERROR_ENTRY_NODEF10(160), ERROR_ENTRY_NODEF10(170), ERROR_ENTRY_NODEF10(180), ERROR_ENTRY_NODEF10(190),
		ERROR_ENTRY_NODEF100(200), ERROR_ENTRY_NODEF100(300), ERROR_ENTRY_NODEF100(400), ERROR_ENTRY_NODEF100(500),
		ERROR_ENTRY(600,"�������� ��������� ���������"),
		ERROR_ENTRY(601,"��������� ��������"),
		ERROR_ENTRY(602,"������ � ���������"),
		ERROR_ENTRY(603,"������ � ���������� �������"),
		ERROR_ENTRY(604,"������ � ���������� ���������� �������"),
		ERROR_ENTRY_NODEF100(700), ERROR_ENTRY_NODEF100(800), ERROR_ENTRY_NODEF100(900)
	};

	ERROR geterror(int id) {

		if (id < 0 || id > ERROR_MAX_ENTRY) id = 0;		//���� ��� ��������� �� ������ 0

		ERROR* ptr = new ERROR;
		ptr->id = id;
		strcpy_s(ptr->message, errors[id].message);
		return *ptr;
	};

	Error::ERROR geterrorline(int id, int line)
	{
		if (id < 0 || id > ERROR_MAX_ENTRY) id = 0;		//���� ��� ��������� �� ������ 0

		ERROR* ptr = new ERROR;

		ptr->id = id;
		ptr->inext.line = line;
		strcpy_s(ptr->message, errors[id].message);

		return *ptr;
	}

	Error::ERROR geterrorin(int id, int line, int col)
	{
		if (id < 0 || id > ERROR_MAX_ENTRY) id = 0;		//���� ��� ��������� �� ������ 0

		ERROR* ptr = new ERROR;

		ptr->id = id;
		ptr->inext.line = line;
		ptr->inext.col = col;
		strcpy_s(ptr->message, errors[id].message);
		
		return *ptr;
	}

}
