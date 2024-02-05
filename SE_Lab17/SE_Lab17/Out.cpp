#include "stdafx.h"

namespace Out
{

	OUTFILE getOut(wchar_t outfile[])
	{
		OUTFILE out;
		char* path = new char[wcslen(outfile) - 4];
		for (int i = 0, j = 5; i < wcslen(outfile) - 5; i++, j++)
		{
			path[i] = outfile[j];
		}
		path[wcslen(outfile) - 5] = '\0';

		auto ofile = new std::ofstream;
		ofile->open(path);
		if (!ofile->is_open())
			throw ERROR_THROW(113);

		out.stream = ofile;
		return out;
	}


	void writeOutFile(OUTFILE out, unsigned char *text)
	{
		unsigned char *buff = new unsigned char[IN_MAX_LEN_TEXT];
		int k = 0;
		for (int i=0; text[i]!='\0'; i++)
		{
			if ((text[i] == ' ' && (text[i + 1] == ';' || text[i + 1] == ','|| text[i + 1] == '{'|| text[i + 1] == '}'|| text[i + 1] == '('
				|| text[i + 1] == ')'|| text[i + 1] == '='|| text[i + 1] == '+'|| text[i + 1] == '-'|| text[i + 1] == '/'|| text[i + 1] == '*' || text[i + 1] == '|')))
			{
				continue;
			}
		    if((text[i] == ' ' && (text[i - 1] == ';' || text[i - 1] == ',' || text[i + 1] == '{' || text[i - 1] == '}' || text[i - 1] == '('
					|| text[i - 1] == ')' || text[i - 1] == '=' || text[i - 1] == '+' || text[i - 1] == '-' || text[i - 1] == '/' || text[i - 1] == '*' || text[i - 1] == '|')))
			{
				continue;
			}
			
				buff[k] = text[i];
				k++;
		}
		buff[k] = '$';
		buff[k+1] = '\0';
		*out.stream << buff;
		out.stream->close();
		delete[] buff;
	}
}