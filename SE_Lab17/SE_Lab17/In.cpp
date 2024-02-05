#include "stdafx.h"

namespace In
{
	INP getin(wchar_t infile[])
	{
		setlocale(LC_ALL, "rus");
		INP inp;

		char* path = new char[wcslen(infile) - 3];
		for (int i = 0, j = 4; i < wcslen(infile) - 4; i++, j++)
		{
			path[i] = infile[j];
		}
		path[wcslen(infile) - 4] = '\0';
		
		std::ifstream ifile;
		ifile.open(path);
		if (!ifile.is_open())
			throw ERROR_THROW(110);

		char c;
		unsigned char ch,temp='z';
		
		int position = 0;
		inp.text = new unsigned char[IN_MAX_LEN_TEXT];
		while (ifile.get(c))
		{
			ch = c;
			if (ch == IN_CODE_ENDL)
			{
				inp.lines++;
				position = 0;
			}
			if (inp.code[ch] == INP::F)
			{
				std::cout << ch;
				inp.size++;
				throw ERROR_THROW_IN(111, inp.lines, position+1);
			}
			else if (inp.code[ch] == INP::I)
			{
				position++;
				inp.ignore++;
			}
			else if (inp.code[ch] == INP::T)
			{
				if(!(ch==' '&&temp==' '))
				{
					position++;
					inp.text[inp.size] = ch;
					inp.size++;
				}
			}
			else
			{
				position++;
				inp.text[inp.size] = inp.code[ch];
				inp.size++;
			}
			temp = c;
		}

		inp.text[inp.size] = '\0';
		ifile.close();
		return inp;
	}
}
