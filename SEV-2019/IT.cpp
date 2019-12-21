#include "stdafx.h"
#include <stdlib.h>


namespace IT
{

	Entry::Entry(char* id, int idxLT, IDDATATYPE datatype, IDTYPE idtype)
	{
		strncpy_s(this->id, ID_MAXSIZE, id, ID_MAXSIZE - 1);
		this->idxfirstLE = idxLT;
		this->iddatatype = datatype;
		this->idtype = idtype;
		this->value.vint = TI_INT_DEFAULT;
		for (int i = 0; i < TI_STR_MAXSIZE; i++)
		{
			this->value.vchr.chr[i] = '\0';
		}
		this->value.vstr.len = NULL;
		this->value.vchr.count = NULL;

	}
	IdTable Create(int size)
	{
		IdTable idtable;
		idtable.table = new Entry[size];
		idtable.size = NULL;
		return idtable;
	}
	void Add(IdTable& idtable, Entry entry)
	{
		strncpy_s(idtable.table[idtable.size].id, entry.id, ID_MAXSIZE - 1);
		idtable.table[idtable.size].line = entry.line;
		idtable.table[idtable.size].idxfirstLE = entry.idxfirstLE;
		idtable.table[idtable.size].iddatatype = entry.iddatatype;
		idtable.table[idtable.size].idtype = entry.idtype;
		idtable.table[idtable.size].value.vint = entry.value.vint;
		idtable.table[idtable.size].value.vchr = entry.value.vchr;
		idtable.table[idtable.size].value.vstr.len = entry.value.vstr.len;
		idtable.table[idtable.size].value.vstr.str[0] = entry.value.vstr.str[0];
		idtable.size++;
	}
	Entry GetEntry(IdTable& idtable, int n)
	{
		return idtable.table[n];
	}
	int IsId(IdTable& idtable, char id[ID_MAXSIZE])
	{
		for (int i = 0; i < idtable.size; i++)
		{
			if (strcmp(idtable.table[i].id, id) == NULL)
				return i;
		}
		return -1;
	}
	int GetSize(IdTable& idtable)
	{
		return idtable.size;
	}
	void SetValue(IdTable& idtable, int indTI, char* token)
	{
		if (idtable.table[indTI].iddatatype == CHR)
		{
			if (idtable.table[indTI].value.vchr.count > TI_CHAR_MAXSIZE)
				throw ERROR_THROW(6);
			idtable.table[indTI].value.vchr.count = strlen(token);
			strcpy_s(idtable.table[indTI].value.vchr.chr, TI_CHAR_MAXSIZE, token);
		}
		else if (idtable.table[indTI].iddatatype == STR)
		{
			if (idtable.table[indTI].value.vstr.len > TI_STR_MAXSIZE)
				throw ERROR_THROW(6);
			idtable.table[indTI].value.vstr.len = strlen(token);
			strcpy_s(idtable.table[indTI].value.vstr.str, TI_STR_MAXSIZE, token);
		}
		else
		{
			int tempInt = atoi(token);
			if (tempInt > INT_MAXSIZE)
			{
				throw ERROR_THROW(6);
			}
			else
			{
				if (tempInt < INT_MINUS_MAXSIZE)
					throw ERROR_THROW(6);
			}
			//idtable.table[indTI].value.vint = tempInt;

		}
	}
}