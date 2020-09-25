
#pragma once		

#define IN_MAX_LEN_TEXT	1024*1024	// ������������ ������ ���������	���� =	1MB									
#define IN_CODE_ENDL '\n'			// ������ ��������
#define STR_ENDL '\0'               // ����� ������
#define TAB '\t'
#define SPACE ' '
#define LITERAL '\''
/****************************************************************************************************************************/
/*	�������	�������� ������� ����������.	������ = ���	(Windows-1251)	�������											*/
/*	�������� IN::F	- �����������	������,	IN::� - ����������� ������	,IN::F -������������ (�� �������)		            */
/*	����	0 <= ��������	< 255 -	�� �������� ������	��������															*/
/****************************************************************************************************************************/

#define IN_CODE_TABLE {\
/* 0  |  1  |  2  |  3  |  4  |  5  |  6  |  7  |  8  |  9  |  A  |  B  |  C  |  D  |  E  |  F  |    */\
 IN::F,IN::F,IN::F,IN::F,IN::F,IN::F,IN::F,IN::F,IN::F,IN::T,  '|',IN::F,IN::F,IN::F,IN::F,IN::F, /*0*/\
 IN::F,IN::F,IN::F,IN::F,IN::F,IN::F,IN::F,IN::F,IN::F,IN::F,IN::F,IN::F,IN::F,IN::F,IN::F,IN::F, /*1*/\
 IN::S,IN::L,IN::L,IN::L,IN::L,IN::L,IN::L,IN::T,IN::E,IN::E,IN::E,IN::E,IN::E,IN::E,IN::E,IN::T, /*2*/\
 IN::T,IN::T,IN::T,IN::T,IN::T,IN::T,IN::T,IN::T,IN::T,IN::T,IN::L,IN::E,IN::L,IN::E,IN::L,IN::L, /*3*/\
 IN::L,IN::T,IN::T,IN::T,IN::T,IN::T,IN::T,IN::T,IN::T,IN::T,IN::T,IN::T,IN::T,IN::T,IN::T,IN::T, /*4*/\
 IN::T,IN::T,IN::T,IN::T,IN::T,IN::T,IN::T,IN::T,IN::T,IN::T,IN::T,IN::L,IN::L,IN::L,IN::T,IN::T, /*5*/\
 IN::L,IN::T,IN::T,IN::T,IN::T,IN::T,IN::T,IN::T,IN::T,IN::T,IN::T,IN::T,IN::T,IN::T,IN::T,IN::T, /*6*/\
 IN::T,IN::T,IN::T,IN::T,IN::T,IN::T,IN::T,IN::T,IN::T,IN::T,IN::T,IN::E,IN::L,IN::E,IN::L,IN::F, /*7*/\
     																								   \
 IN::F,IN::F,IN::F,IN::F,IN::F,IN::F,IN::F,IN::F,IN::F,IN::F,IN::F,IN::F,IN::F,IN::F,IN::F,IN::F, /*8*/\
 IN::F,IN::F,IN::F,IN::F,IN::F,IN::F,IN::F,IN::F,IN::F,IN::F,IN::F,IN::F,IN::F,IN::F,IN::F,IN::F, /*9*/\
 IN::F,IN::F,IN::F,IN::F,IN::F,IN::F,IN::F,IN::F,IN::L,IN::L,IN::F,IN::F,IN::F,IN::F,IN::F,IN::F, /*A*/\
 IN::F,IN::F,IN::F,IN::F,IN::F,IN::F,IN::F,IN::F,IN::F,IN::L,IN::F,IN::F,IN::F,IN::F,IN::F,IN::F, /*B*/\
 IN::L,IN::L,IN::L,IN::L,IN::L,IN::L,IN::L,IN::L,IN::L,IN::L,IN::L,IN::L,IN::L,IN::L,IN::L,IN::L, /*C*/\
 IN::L,IN::L,IN::L,IN::L,IN::L,IN::L,IN::L,IN::L,IN::L,IN::L,IN::L,IN::L,IN::L,IN::L,IN::L,IN::L, /*D*/\
 IN::L,IN::L,IN::L,IN::L,IN::L,IN::L,IN::L,IN::L,IN::L,IN::L,IN::L,IN::L,IN::L,IN::L,IN::L,IN::L, /*E*/\
 IN::L,IN::L,IN::L,IN::L,IN::L,IN::L,IN::L,IN::L,IN::L,IN::L,IN::L,IN::L,IN::L,IN::L,IN::L,IN::L, /*F*/\
}


namespace In
{
    struct	IN										// �������� ������
    {
        enum { F, T, I, E, S, L };		                // T - ���������� ������. F - ������������,	I -	������������, ����� ��������, E - ��������� �����/���, S - ������, L - ��������
        int	size = 0;								//	������ ��������� ����													
        int	lines = 1;								//	���������� �����														
        int	ignor = 0;								//	���������� ����������������� ��������										
        unsigned char* text = nullptr;
        short code[256] = IN_CODE_TABLE;			//	������� ��������: T, F, I, E, S ����� ��������
    };
    IN getin(wchar_t infile[]);					    //	������ � ��������� ������� ����� ���� (Windows - 1251)	

};


