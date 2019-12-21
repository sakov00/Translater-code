#pragma once
#include"Error.h"
#include <string>

#define	LEXEMA_FIXSIZE	1			// ������������� ������ ������� ������
#define	LT_MAXSIZE		65536		// ������������ ������ ������� ������
#define	LT_TI_NULLDX	0xffffffff	// ������� � ������� ������
#define	LEX_NUM		    't'			// �����
#define	LEX_STR		    't'			// ������
#define LEX_CHAR		't'			// �������
#define LEX_OBJECT      't'			// ������						
#define	LEX_ID			'i'			// ��������������
#define	LEX_LITERAL		'l'			// �������
#define	LEX_FUNCTION	'f'			// �������
#define LEX_IF          'u'			// if
#define	LEX_DEF		    'd'			// Init
#define LEX_STANDART    'B'         // ���������� ���������� ����������
#define LEX_STRCAT      's'         // ���������� ���������� strcat
#define LEX_STRCPY      'p'         // ���������� ���������� strcpy
#define	LEX_BACK		'b'			// Return
#define	LEX_OUT		    'o'			// Out
#define	LEX_GLAVN		'g'			// Glavn
#define	LEX_SEPARATOR	';'			// ;
#define	LEX_COMMA		','			// ,
#define	LEX_LEFTBRACE	'{'			// {
#define	LEX_BRACELET	'}'			// }
#define	LEX_LEFTHESIS	'('			// (
#define	LEX_RIGHTTHESIS	')'			// )

#define	LEX_PLUS		'+'			// +
#define	LEX_MINUS		'-'			// -
#define	LEX_STAR		'*'			// *
#define	LEX_DIRSLASH	'/'			// /

#define	LEX_EQUAL		'='			// =
#define	LEX_NOT_EQUALS	'!'			// !=
#define	LEX_LESS_OR_EQUAL	'k'		// <=
#define	LEX_MORE_OR_EQUAL	'v'		// >=
#define	LEX_LESS		'<'			// <
#define	LEX_MORE		'>'			// >

#define	LEX_TYPE_NUM	    "num"	
#define	LEX_TYPE_STR	    "str"	
#define LEX_TYPE_CHAR		"char"
#define	LEX_TYPE_FUNCTION	"function"	
#define	LEX_TYPE_VARIABLE	"variable"	
#define LEX_TYPE_PARAMETR	"parametr"	
#define LEX_TYPE_LITERAL	"literal"
#define LEX_TYPE_STANDART	"vstroen"
#define LEX_TYPE_EQUALS		"="
#define LEX_TYPE_NOT_EQUALS	"!"

#define	LEX_TYPE_LESS_OR_EQUAL	"k"		// <=
#define	LEX_TYPE_MORE_OR_EQUAL	"v"		// >=
#define	LEX_TYPE_LESS		"<"		// <
#define	LEX_TYPE_MORE		">"			// >


namespace LT
{
	struct Entry
	{
		char lexema;			// �������
		int sn;					// ����� ������ � �������� ������
		int idxTI;				// ������ � ������� ��������������� ��� LT_TI_NULLIDX
		int tokenId = 0;        // ����� ������
		char operation = ' ';         // ��������
		std::string value;
		Entry() {};             // ����������� �� ���������
		Entry(char lexema, int snn, int idxti = LT_TI_NULLDX);	// �����������
		Entry(char lexema, int snn, char v, int idxti = LT_TI_NULLDX); // �����������

	};
	struct LexTable						// ��������� ������� ������
	{
		int maxsize;					// ������� ������� ������
		int size;						// ������� ������ ������� ������
		Entry* table;					// ������ ����� ������� ������
	};
	LexTable Create(int size);			// ������� < LT_MAXSIZE
	void Add(LexTable& lextable, Entry entry);	// ��������� ������� ������, ������ ������� ������
	Entry GetEntry(LexTable& lextable, int n);	// ��������� ������� ������, ����� ���������� ������
	void Delete(LexTable& lextable);	// ������� ������� ������ (���������� ������)
}
