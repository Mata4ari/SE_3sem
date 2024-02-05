#include "stdafx.h"
#include <sstream>
using namespace std;


int sn = 1;
char lx1;
char lx2;
bool IsParm = 0;
bool IsStrL = 0;
bool IsIntL = 0;
bool IsMain = 0;
int Lcount = 1;
char pref[ID_MAXSIZE];
int Count = 0;

namespace Lex
{
	void Reading(wchar_t infile[])
	{
		char* path = new char[wcslen(infile) - 4];
		for (int i = 0, j = 5; i < wcslen(infile) - 5; i++, j++)
		{
			path[i] = infile[j];
		}
		path[wcslen(infile) - 5] = '\0';

		auto ifile = new std::ifstream;
		ifile->open(path);
		if (!ifile->is_open())
			throw ERROR_THROW(600);


		LT::LexTable ltable = LT::Create(LT_SIZE);
		IT::IdTable itable = IT::Create(TI_SIZE);
		Error::Warning warning;


		char c='4';
		char cc = '4';
		char temp[TI_STR_MAXSIZE];
		int k = 0;
		while (ifile->get(c))
		{
			Count++;
			cc = c;
			if (k > TI_STR_MAXSIZE)
				throw ERROR_THROW(604);
			if (c == '\'')
			{
				k = 0;
				temp[k] = c;
				k++;
				ifile->get(c);
				while (c != '\'')
				{
					temp[k] = c;
					k++;
					ifile->get(c);
				}
				temp[k] = c;
				temp[k + 1] = '\0';
				k = 0;
				step(temp, ltable, itable,warning);
				cc = c;
				continue;
			}
			if (c == ' ' || c == ',' || c == ';' || c == '(' || c == ')' || c == '{' || c == '}' || c == '+' || c == '-' || c == '/' || c == '*' || c == '|'||c=='=')
			{
				temp[k] = '\0';
				if(k!=0)
				{
					step(temp, ltable, itable, warning);
					k = 0;
				}
				step(c, ltable, itable, warning);
			}
			else
			{
				temp[k] = c;
				k++;
			}
		}
		LT::PrintLexTable(ltable,warning);
		IT::PrintIdTable(itable);
		LT::Delete(ltable);
		IT::Delete(itable);
	}

	void step(char* temp, LT::LexTable& ltable, IT::IdTable& itable,Error::Warning& warning)
	{
		if (temp[0] == 'f')
		{
			FST::FST fstFunction(FUNCTION(temp));
			if (FST::execute(fstFunction))
			{
				LT::Entry lstr;
				lstr.sn = sn;
				lx2 = LEX_FUNCTION;
				lstr.lexema[0] = LEX_FUNCTION;
				lstr.idxTI = LT_TI_NULLIDX;
				LT::Add(ltable, lstr);
				return;
			}
		}
		else if (temp[0] == 'i')
		{
			FST::FST fstInteger(INTEGER(temp));
			if (FST::execute(fstInteger))
			{
				LT::Entry lstr;
				lstr.sn = sn;
				lx1 = LEX_INTEGER;
				lstr.lexema[0] = LEX_INTEGER;
				lstr.idxTI = LT_TI_NULLIDX;
				LT::Add(ltable, lstr);
				return;
			}
		}
		else if (temp[0] == 'm')
		{
			FST::FST fstMain(MAIN(temp));
			if (FST::execute(fstMain))
			{
				IT::Entry istr;
				LT::Entry lstr;
				IsMain = 1;
				normalize(temp, istr, itable);
				if (IT::IsId(itable, istr.id, istr.pref) == TI_NULLIDX)
				{
					istr.idxfirstLE = sn;
					lstr.idxTI = itable.size;
				}
				else
				{
					int x = IT::IsId(itable, istr.id, istr.pref);
					istr.idxfirstLE = itable.table[x].idxfirstLE;
					istr.idtype = itable.table[x].idtype;
					lstr.idxTI = x;
				}
				IT::Add(itable, istr);
				lstr.lexema[0] = LEX_MAIN;
				lstr.sn = sn;
				LT::Add(ltable, lstr);
				IsMain = 0;
				return;
			}
		}
		else if (temp[0] == 's')
		{
			FST::FST fstString(STRING(temp));
			if (FST::execute(fstString))
			{
				LT::Entry lstr;
				lstr.sn = sn;
				lstr.lexema[0] = LEX_STRING;
				lx1 = LEX_STRING;
				lstr.idxTI = LT_TI_NULLIDX;
				LT::Add(ltable, lstr);
				return;
			}
		}
		else if (temp[0] == 'd')
		{
			FST::FST fstDeclare(DECLARE(temp));
			if (FST::execute(fstDeclare))
			{
				LT::Entry lstr;
				lstr.sn = sn;
				lstr.lexema[0] = LEX_DECLARE;
				lx1 = LEX_DECLARE;
				lstr.idxTI = LT_TI_NULLIDX;
				LT::Add(ltable, lstr);
				return;
			}
		}
		else if (temp[0] == 'r')
		{
			FST::FST fstReturn(RETURN(temp));
			if (FST::execute(fstReturn))
			{
				LT::Entry lstr;
				lstr.sn = sn;
				lstr.lexema[0] = LEX_RETURN;
				lx1 = LEX_RETURN;
				lstr.idxTI = LT_TI_NULLIDX;
				LT::Add(ltable, lstr);
				return;
			}
		}
		else if (temp[0] == 'p')
		{
			FST::FST fstPrint(PRINT(temp));
			if (FST::execute(fstPrint))
			{
				LT::Entry lstr;
				lstr.sn = sn;
				lstr.lexema[0] = LEX_PRINT;
				lx1 = LEX_PRINT;
				lstr.idxTI = LT_TI_NULLIDX;
				LT::Add(ltable, lstr);
				return;
			}
		}
		else if (temp[0] == '\'')
		{
			FST::FST fstStringLiteral(STRING_LITERAL(temp));
			if (FST::execute(fstStringLiteral))
			{
				IT::Entry istr;
				LT::Entry lstr;
				IsStrL = 1;
				normalize(temp, istr, itable);
				if (IT::IsId(itable, istr.id,istr.pref) == TI_NULLIDX)
				{
					istr.idxfirstLE = sn;
					lstr.idxTI = itable.size;
				}
				else
				{
					int x = IT::IsId(itable, istr.id, istr.pref);
					istr.idxfirstLE = itable.table[x].idxfirstLE;
					istr.idtype = itable.table[x].idtype;
					lstr.idxTI = x;
				}
				IT::Add(itable, istr);
				lstr.lexema[0] = LEX_LITERAL;
				lstr.sn = sn;
				LT::Add(ltable, lstr);
				return;
			}
		}
			FST::FST fstIntLiteral(INTEGER_LITERAL(temp));
			FST::FST fstId(IDENTIFICATOR(temp));
			
			if (FST::execute(fstIntLiteral))
			{
				if (strlen(temp) > TI_INT_MAXSIZE)
					throw ERROR_THROW(610);
				IT::Entry istr;
				LT::Entry lstr;
				IsIntL = 1;
				normalize(temp, istr, itable);
				if (IT::IsId(itable, istr.id, istr.pref) == TI_NULLIDX)
				{
					istr.idxfirstLE = sn;
					lstr.idxTI = itable.size;
				}
				else
				{
					int x = IT::IsId(itable, istr.id, istr.pref);
					istr.idxfirstLE = itable.table[x].idxfirstLE;
					istr.idtype = itable.table[x].idtype;
					lstr.idxTI = x;
				}
				IT::Add(itable, istr);
				lstr.lexema[0] = LEX_LITERAL;
				lstr.sn = sn;
				LT::Add(ltable, lstr);
				return;
			}
			if (FST::execute(fstId))
			{
				IT::Entry istr;
				LT::Entry lstr;
				normalize(temp, istr,itable);
				if (IT::IsId(itable, istr.id,istr.pref) == TI_NULLIDX)
				{
					istr.idxfirstLE = sn;
					lstr.idxTI = itable.size;
				}
				else
				{
					int x =IT::IsId(itable, istr.id,istr.pref);
					istr.idxfirstLE = itable.table[x].idxfirstLE;
					istr.idtype = itable.table[x].idtype;
					lstr.idxTI = x;
				}
				IT::Add(itable, istr);
				lstr.lexema[0] = LEX_ID;
				lstr.sn = sn;
				LT::Add(ltable, lstr);
				return;
			}
			Error::Error err = Error::getwarning(613, sn, Count - strlen(temp));
			Error::putwarning(warning, err);

	}

	void step(char ch, LT::LexTable& ltable, IT::IdTable& itable, Error::Warning& warning)
	{
		if (ch == ' ')
			return;
		if (ch == '|')
		{
			sn++;
			return;
		}
		if (ch == '{')
		{
			IsParm = 0;	
		}
		if (ch == '+' || ch == '-' || ch == '/' || ch == '*')
		{
			LT::Entry entry;
			entry.idxTI = TI_NULLIDX;
			entry.lexema[0] = LEX_PLUS;
			entry.sn = sn;
			LT::Add(ltable, entry);
		}
		else
		{
			LT::Entry entry;
			entry.idxTI = TI_NULLIDX;
			entry.lexema[0] = ch;
			entry.sn = sn;
			LT::Add(ltable, entry);
		}
	}

	void normalize(char* str,IT::Entry &entry,IT::IdTable& itable)
	{
		if (IsStrL)
		{
			char buff[4];
			entry.id[0] = 'L';
			_itoa_s(Lcount, buff, 10);
			Lcount++;
			buff[3] = '\0';
			entry.id[1] = '\0';
			strcat_s(entry.id, buff);
			entry.id[strlen(entry.id)] = '\0';
			entry.idtype = IT::L;
			entry.iddatatype = IT::STR;
			int i = 1;
			int k = 0;
			for (; i < strlen(str) - 1; k++,i++)
			{
				entry.value.vstr->str[k] = str[i];
			}
			entry.value.vstr->str[k] = '\0';
			entry.value.vstr->len = strlen(str - 2);
			IsStrL = 0;
			return;
		}
		if (IsIntL)
		{
			char buff[4];

			entry.id[0] = 'L';
			_itoa_s(Lcount, buff, 10);
			Lcount++;
			buff[3] = '\0';
			entry.id[1] = '\0';
			strcat_s(entry.id, buff);
			entry.id[strlen(entry.id)] = '\0';
			entry.idtype = IT::L;
			entry.iddatatype = IT::INT;
			entry.value.vint = atoi(str);
			IsIntL = 0;
			return;
		}
		if (lx2==LEX_FUNCTION||IsMain)
		{
			int i = 0;
			for (; i < ID_MAXSIZE-1&& i < strlen(str); i++)
			{
				entry.id[i] = str[i];
			}
			entry.id[i] = '\0';
			entry.idtype = IT::F;
			if(IsMain)
				entry.iddatatype = IT::INT;
			if(lx1==LEX_INTEGER&&!IsMain)
			{
				entry.iddatatype = IT::INT;
			}
			if (lx1 == LEX_STRING && !IsMain)
			{
				entry.iddatatype = IT::STR;
			}
			int k = 0;
			for (; k < strlen(entry.id); k++)
			{
				pref[k] = entry.id[k];
			}
			pref[k] = '\0';
			IsParm = 1;
			IsMain = 0;
			lx2 = 'z';
			return;
		}
		if (lx1 == LEX_INTEGER&&IsParm)
		{
			int i = 0;
			for (int i = itable.size - 1; i >= 0; i--)
			{
				if (itable.table[i].idtype == IT::F)
				{
					int k = 0;
					for (; k < strlen(itable.table[i].id); k++)
					{
						pref[k] = itable.table[i].id[k];
					}
					pref[k] = '\0';
					break;
				}
			}
			for (int k=0; i < ID_MAXSIZE-1 && k < strlen(str); k++,i++)
			{
				entry.id[i] = str[k];
			}
			strcpy_s(entry.pref, pref);
			entry.id[i] = '\0';
			entry.idtype = IT::P;
			entry.iddatatype = IT::INT;
			entry.value.vint = 0;
			lx1 = 'z';
			return;
		}
		if (lx1 == LEX_INTEGER)
		{
			int i = 0;
			for (int k = 0; i < ID_MAXSIZE - 1 && k < strlen(str); k++, i++)
			{
				entry.id[i] = str[k];
			}
			strcpy_s(entry.pref, pref);
			entry.id[i] = '\0';
			entry.idtype = IT::V;
			entry.iddatatype = IT::INT;
			entry.value.vint = 0;
			lx1 = 'z';
			return;
		}
		if (lx1 == LEX_STRING && IsParm)
		{
			for (int i = itable.size - 1; i >= 0; i--)
			{
				if (itable.table[i].idtype == IT::F)
				{
					int k = 0;
					for (; k < strlen(itable.table[i].id); k++)
					{
						pref[k] = itable.table[i].id[k];
					}
					pref[k] = '\0';
					break;
				}
			}
			int i = 0;
			for (int k = 0; i < ID_MAXSIZE - 1 && k < strlen(str); k++, i++)
			{
				entry.id[i] = str[k];
			}
			strcpy_s(entry.pref, pref);
			entry.id[i] = '\0';
			entry.idtype = IT::P;
			entry.iddatatype = IT::STR;
			entry.value.vstr->len = 0;
			entry.value.vstr->str[0] = '\0';
			lx1 = 'z';
			return;
		}
		if (lx1 == LEX_STRING)
		{
			int i = 0;
			for (int k = 0; i < ID_MAXSIZE - 1 && k < strlen(str); k++, i++)
			{
				entry.id[i] = str[k];
			}
			entry.id[i] = '\0';
			entry.idtype = IT::V;
			entry.iddatatype = IT::STR;
			entry.value.vstr->len = 0;
			entry.value.vstr->str[0] = '\0';
			lx1 = 'z';
			return;
		}
		int i = 0;
		strcpy_s(entry.pref,pref);
		for (int k = 0; i < ID_MAXSIZE - 1 && k < strlen(str); k++, i++)
		{
			entry.id[i] = str[k];
		}
		entry.id[i] = '\0';
		return;
	}
}