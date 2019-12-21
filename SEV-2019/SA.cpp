#include "stdafx.h"
#include "SA.h"


bool  SemanticAnalyze(LT::LexTable& Lextable, In::IN& InStruct, IT::IdTable& idtable, Log::LOG& log)
{
	bool Standart_LIB = false;
	int isGlavn = 0;
	bool isFunction = false;
	bool choise = true;
	int isBrace = 0;
	bool isBack = false;
	bool Viragenia_Num = true;
	IT::IDDATATYPE type_func;
	int IsParFun;
	bool IsEqual;
	bool IsParam;

	for (int i = 0, j; i < Lextable.size; i++)
	{
		switch (Lextable.table[i].lexema)
		{
		case LEX_DIRSLASH: {
			if (IT::IsId(idtable, InStruct.tokens[i + 1].token) != -1 && idtable.table[IT::IsId(idtable, InStruct.tokens[i + 1].token)].value.vint == 0) {
				throw ERROR_THROW_IN(109, Lextable.table[i + 1].sn, NULL);
				choise = false;
				break;
			}
		}
		case LEX_NUM:
		{
			j = i;
			if (Lextable.table[i + 1].lexema == LEX_FUNCTION)
			{
				while (Lextable.table[j].lexema != LEX_SEPARATOR)
				{
					if (Lextable.table[j].lexema == LEX_LEFTBRACE)
						break;
					j++;
				}
				if (Lextable.table[j].lexema == LEX_SEPARATOR)
					throw ERROR_THROW(8);
				break;
			}
			if (strcmp(InStruct.tokens[i].token, LEX_TYPE_CHAR) == 0 && strlen(InStruct.tokens[i + 3].token) > TI_CHAR_MINSIZE)
			{
				throw ERROR_THROW_IN(127, Lextable.table[i].sn, NULL);
			}
			break;
		}
		case LEX_IF:
		{
			switch (Lextable.table[i + 3].lexema)
			{
			case LEX_MORE:
			{
				IsEqual = true;
				break;
			}
			case LEX_LESS:
			{
				IsEqual = true;
				break;
			}
			case LEX_MORE_OR_EQUAL:
			{
				IsEqual = true;
				break;
			}
			case LEX_LESS_OR_EQUAL:
			{
				IsEqual = true;
				break;
			}
			case LEX_NOT_EQUALS:
			{
				IsEqual = true;
				break;
			}
			case LEX_EQUAL:
			{
				IsEqual = true;
				break;
			}
			default:
			{
				IsEqual = false;
				break;
			}
			}
			if (!IsEqual)
			{
				throw ERROR_THROW_IN(128, Lextable.table[i].sn, NULL);
			}
			if (idtable.table[Lextable.table[i + 2].idxTI].iddatatype != idtable.table[Lextable.table[i + 4].idxTI].iddatatype)
			{
				throw ERROR_THROW_IN(114, Lextable.table[i].sn, NULL);
			}

			break;
		}
		case LEX_FUNCTION:
		{		IsParFun =i+2;
			if (Lextable.table[i - 1].lexema == LEX_NUM && Lextable.table[i + 1].lexema == LEX_ID && Lextable.table[i + 2].lexema == LEX_LEFTHESIS)
			{
				if(strcmp(InStruct.tokens[i-1].token,"num")==0)
					type_func = IT::NUM;
				if (strcmp(InStruct.tokens[i - 1].token, "str")==0)
					type_func = IT::STR;
				if (strcmp(InStruct.tokens[i - 1].token, "char")==0)
					type_func = IT::CHR;

				isFunction = true;
				isBack = true;
			}
			break;
		}
		case LEX_STANDART:
		{
			Standart_LIB = true;
			break;
		}
		case LEX_GLAVN:
		{
			if (isFunction == true || isBack == true)
			{
				throw ERROR_THROW_IN(126, Lextable.table[i].sn, NULL);
				choise = false;
				break;
			}
			isBack = true;
			isGlavn++;
			break;
		}
		case LEX_EQUAL:
		{
			if (Lextable.table[i - 1].lexema == LEX_ID && Lextable.table[i + 1].lexema == LEX_ID)
			{
				if (idtable.table[Lextable.table[i - 1].idxTI].iddatatype != idtable.table[Lextable.table[i + 1].idxTI].iddatatype)
				{
					throw ERROR_THROW_IN(3, Lextable.table[i].sn, NULL);
					choise = false;
					break;
				}
			}
			if (Lextable.table[i + 1].lexema == LEX_ID && Lextable.table[i + 2].lexema != LEX_LEFTHESIS && Lextable.table[i + 2].lexema != LEX_SEPARATOR)
			{
				int  p = 0;
				while (Lextable.table[i].lexema != LEX_SEPARATOR)
				{
					if (Lextable.table[i].lexema == LEX_ID)
					{
						p = Lextable.table[i].idxTI;
						if (idtable.table[p].iddatatype != IT::NUM)
						{
							Viragenia_Num = false;
							break;
						}
					}
					i++;
				}
			}
			break;
		}
		case LEX_ID:
		{
			if (idtable.table[IT::IsId(idtable, InStruct.tokens[i].token)].idtype == IT::F && Lextable.table[i - 1].lexema == LEX_EQUAL)
			{
				int schet = 2;
				int b = i+1;
				while (Lextable.table[b].lexema != LEX_RIGHTTHESIS)
				{
					if (Lextable.table[b].lexema == LEX_COMMA)
						schet += 3;
					if (Lextable.table[b].lexema == LEX_ID && Lextable.table[b].lexema != Lextable.table[IsParFun + schet].lexema)
					{
						if (Lextable.table[b].lexema != LEX_RIGHTTHESIS)
							throw ERROR_THROW_IN(122, Lextable.table[i].sn, NULL);
					}
					b++;
				}
			}
			if (idtable.table[IT::IsId(idtable, InStruct.tokens[i].token)].idtype == IT::F && Lextable.table[i - 1].lexema == LEX_EQUAL)
			{
			int schet = 2;
			int b = i+1;
			while (Lextable.table[b].lexema != LEX_RIGHTTHESIS)
			{
				if (Lextable.table[b].lexema == LEX_COMMA)
				schet+=3;
				if (Lextable.table[b].lexema == LEX_ID && idtable.table[IT::IsId(idtable, InStruct.tokens[b].token)].iddatatype != idtable.table[IT::IsId(idtable, InStruct.tokens[IsParFun +schet].token)].iddatatype)
				{
						throw ERROR_THROW_IN(114, Lextable.table[i].sn, NULL);
				}
				b++;
			}
			}
			if (IT::IsId(idtable, InStruct.tokens[i].token) != -1 && idtable.table[IT::IsId(idtable, InStruct.tokens[i].token)].idtype == IT::F && Lextable.table[i + 1].lexema == LEX_EQUAL)
			{
				throw ERROR_THROW_IN(119, Lextable.table[i].sn, NULL);
				choise = false;
			}
			if (IT::IsId(idtable, InStruct.tokens[i].token) != -1 && (Lextable.table[i - 2].lexema == LEX_IF))
			{

				if (IT::GetEntry(idtable, IT::IsId(idtable, InStruct.tokens[i].token)).value.vint == 0)
					throw ERROR_THROW_IN(3, Lextable.table[i].sn, NULL);
			}
			if (IT::IsId(idtable, InStruct.tokens[i].token) != -1 && idtable.table[IT::IsId(idtable, InStruct.tokens[i].token)].idtype == IT::F)
			{
				int kol2 = 0;
				int a = idtable.table[IT::IsId(idtable, InStruct.tokens[i].token)].idxfirstLE;
				while (Lextable.table[a].lexema != LEX_RIGHTTHESIS)
				{
					if (Lextable.table[a].lexema == LEX_COMMA)
						kol2++;
					a++;
				}
				int kol = 0;
				while (Lextable.table[i].lexema != LEX_RIGHTTHESIS)
				{
					if (Lextable.table[i].lexema == LEX_COMMA)
						kol++;
					i++;
				}
				if (kol != kol2)
				{
					throw ERROR_THROW_IN(122, Lextable.table[i].sn, NULL);
					choise = false;
				}
				break;
			}
			if (IT::IsId(idtable, InStruct.tokens[i].token) != -1 && (Lextable.table[i - 2].lexema == LEX_STRCPY || Lextable.table[i - 2].lexema == LEX_STRCAT))
			{
				int check;
				check = IT::IsId(idtable, InStruct.tokens[i].token);
				if (idtable.table[check].iddatatype == IT::NUM && (Lextable.table[i - 2].lexema == LEX_STRCPY || Lextable.table[i - 2].lexema == LEX_STRCAT))
				{
					throw ERROR_THROW_IN(120, Lextable.table[i].sn, NULL);
					choise = false;
					break;
				}
				break;
			}
			if (IT::IsId(idtable, InStruct.tokens[i].token) != -1 && (Lextable.table[i - 2].lexema == LEX_STRCPY || Lextable.table[i - 2].lexema == LEX_STRCAT))
			{
				int check;
				check = IT::IsId(idtable, InStruct.tokens[i].token);
				if (idtable.table[check].iddatatype == IT::CHR && (Lextable.table[i - 2].lexema == LEX_STRCPY || Lextable.table[i - 2].lexema == LEX_STRCAT))
				{
					throw ERROR_THROW_IN(120, Lextable.table[i].sn, NULL);
					choise = false;
					break;
				}
				break;
			}
			if (IT::IsId(idtable, InStruct.tokens[i].token) != -1 && idtable.table[IT::IsId(idtable, InStruct.tokens[i].token)].iddatatype == IT::NUM && InStruct.tokens[i + 2].token[0] == char(34))
			{
				throw ERROR_THROW_IN(4, Lextable.table[i].sn, NULL);
				choise = false;
			}
			if (IT::IsId(idtable, InStruct.tokens[i].token) == -1 && ((Lextable.table[i - 1].lexema != LEX_NUM && Lextable.table[i - 2].lexema != LEX_DEF) || (Lextable.table[i - 1].lexema != LEX_CHAR && Lextable.table[i - 2].lexema != LEX_DEF) || (Lextable.table[i - 1].lexema != LEX_FUNCTION && Lextable.table[i - 2].lexema != LEX_NUM)))
			{
				throw ERROR_THROW_IN(105, Lextable.table[i].sn, NULL);
				choise = false;
			}
			if ((IT::IsId(idtable, InStruct.tokens[i].token) != -1 &&
				Lextable.table[i + 1].lexema == LEX_EQUAL &&
				Lextable.table[i + 2].lexema == LEX_ID &&
				Lextable.table[i + 3].lexema == LEX_SEPARATOR))
			{
				throw ERROR_THROW_IN(106, Lextable.table[i].sn, NULL);
				choise = false;
			}
			if ((IT::IsId(idtable, InStruct.tokens[i].token) != -1 && Lextable.table[i + 1].lexema == LEX_EQUAL && InStruct.tokens[i + 2].isStr == true && (Lextable.table[i + 3].lexema == LEX_PLUS || Lextable.table[i + 3].lexema == LEX_MINUS || Lextable.table[i + 3].lexema == LEX_DIRSLASH || Lextable.table[i + 3].lexema == LEX_STAR) && InStruct.tokens[i + 4].isStr == true))
			{
				throw ERROR_THROW_IN(108, Lextable.table[i].sn, NULL);
				choise = false;
			}
			if (IT::IsId(idtable, InStruct.tokens[i].token) != -1 && Lextable.table[i + 1].lexema == LEX_EQUAL && (Lextable.table[i + 2].lexema == LEX_ID && idtable.table[IT::IsId(idtable, InStruct.tokens[i + 2].token)].iddatatype == IT::NUM) && (Lextable.table[i + 4].lexema == LEX_ID && idtable.table[IT::IsId(idtable, InStruct.tokens[i + 4].token)].iddatatype == IT::NUM))
				break;
			if (IT::IsId(idtable, InStruct.tokens[i].token) != -1 && Lextable.table[i + 1].lexema == LEX_EQUAL && (Lextable.table[i + 2].lexema == LEX_LITERAL && InStruct.tokens[i + 2].isStr == false) && (Lextable.table[i + 4].lexema == LEX_LITERAL && InStruct.tokens[i + 4].isStr == false))
				break;

			if (IT::IsId(idtable, InStruct.tokens[i].token) != -1 && Lextable.table[i + 1].lexema == LEX_EQUAL && (Lextable.table[i + 2].lexema == LEX_ID || Lextable.table[i + 2].lexema == LEX_LITERAL) && (Lextable.table[i + 3].lexema == LEX_DIRSLASH || Lextable.table[i + 3].lexema == LEX_MINUS || Lextable.table[i + 3].lexema == LEX_PLUS || Lextable.table[i + 3].lexema == LEX_STAR)
				&& (Lextable.table[i + 4].lexema == LEX_LITERAL || Lextable.table[i + 4].lexema == LEX_ID) && Lextable.table[i + 5].lexema == LEX_SEPARATOR)
			{
				if (idtable.table[Lextable.table[i + 2].idxTI].iddatatype != idtable.table[Lextable.table[i].idxTI].iddatatype
					|| idtable.table[Lextable.table[i + 4].idxTI].iddatatype != idtable.table[Lextable.table[i].idxTI].iddatatype)
				{
					throw ERROR_THROW_IN(3, Lextable.table[i].sn, NULL);
					choise = false;
				}
			}
			break;
		}
		case LEX_STRCAT:
		{
			int schet = 0;
			int b = i;
			while (Lextable.table[b].lexema != LEX_RIGHTTHESIS)
			{
				if (Lextable.table[b].lexema == LEX_COMMA)
					schet++;
				b++;
			}
			if (schet == 1)
				throw ERROR_THROW_IN(122, Lextable.table[i].sn, NULL);
			if (Standart_LIB == false)
			{
				throw ERROR_THROW_IN(116, Lextable.table[i].sn, NULL);
				choise = false;
			}
			if (Lextable.table[i + 2].lexema == LEX_LITERAL && InStruct.tokens[i + 2].isStr == false)
			{
				throw ERROR_THROW_IN(120, Lextable.table[i].sn, NULL);
				choise = false;
			}
			if (Lextable.table[i + 4].lexema == LEX_LITERAL && InStruct.tokens[i + 4].isStr == true)
			{
				throw ERROR_THROW_IN(3, Lextable.table[i].sn, NULL);
				choise = false;
			}
			if (Lextable.table[i + 6].lexema == LEX_LITERAL && InStruct.tokens[i + 6].isStr == true)
			{
				throw ERROR_THROW_IN(3, Lextable.table[i].sn, NULL);
				choise = false;
			}
			break;
		}
		case LEX_BACK:
		{
			if (isFunction == true)
			{
				int k = 0;
				for (k = 0; k <= idtable.size; k++)
				{
					if (strcmp(idtable.table[k].id, InStruct.tokens[i + 1].token) == 0)
						if (idtable.table[k].iddatatype != type_func)
						{
							throw ERROR_THROW_IN(114, Lextable.table[i].sn, NULL);
						}
				}

				isBack = false;
				isFunction = false;
				break;
			}
			else
			{
				if (isGlavn == 0)
					throw ERROR_THROW_IN(126, Lextable.table[i].sn, NULL);
				isBack = false;
				break;
			}
			break;
		}
		case LEX_LEFTBRACE:
		{
			isBrace++;

			break;
		}
		case LEX_BRACELET:
		{
			isBrace--;
			break;
		}
		case LEX_STRCPY:
		{
			int schet = 0;
			int b = i;
			while (Lextable.table[b].lexema != LEX_RIGHTTHESIS)
			{
				if (Lextable.table[b].lexema == LEX_COMMA)
					schet++;
				b++;
			}
			if (schet != 0)
				throw ERROR_THROW_IN(122, Lextable.table[i].sn, NULL);
			if (Standart_LIB == false)
			{
				throw ERROR_THROW_IN(116, Lextable.table[i].sn, NULL);
				choise = false;
			}
			if (Lextable.table[i + 2].lexema == LEX_LITERAL && InStruct.tokens[i + 2].isStr == false)
			{
				throw ERROR_THROW_IN(120, Lextable.table[i].sn, NULL);
				choise = false;
			}
			break;
		}
		}
	}

	if (isBrace != 0)
	{
		throw ERROR_THROW(599);
		choise = false;
	}

	if (isBack == true)
	{
		throw ERROR_THROW(126);
		choise = false;
	}
	if (isGlavn == 0)
	{
		throw ERROR_THROW(123);
		choise = false;
	}
	else if (isGlavn > 1)
	{
		throw ERROR_THROW(118);
		choise = false;
	}
	return choise;
}