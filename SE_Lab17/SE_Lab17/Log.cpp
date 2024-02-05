#include "stdafx.h"
#include <string>

namespace Log
{
	LOG getlog(wchar_t logfile[])
	{
		LOG log;
		char* path = new char[wcslen(logfile) - 4];
		for (int i = 0, j = 5; i < wcslen(logfile) - 5; i++, j++)
		{
			path[i] = logfile[j];
		}
		path[wcslen(logfile) - 5] = '\0';

		auto ofile=new std::ofstream;
		ofile->open(path, std::ios::out | std::ios::app);
		if (!ofile->is_open())
			throw ERROR_THROW(112);

		log.stream = ofile;
		wcscpy_s(log.logfile, (wchar_t*)path);
		return log;
	}

	void WriteLine(LOG log, char* c, ...)
	{
		char str[300];
		char** p = &c;
		int k = 0;
		int j = 0;
		while (*(p + k)[0] != 0x00)
		{
			for (int i = 0; i < strlen(*(p + k)); i++)
			{
				str[j] = (*(p + k))[i];
				j++;
			}
			k++;
		}
		str[j] = '\0';
		*log.stream << str;
	}

	void WriteLine(LOG log, wchar_t* c, ...)
	{
		wchar_t str[300];
		char st[300];
		wchar_t** p = &c;
		int k = 0;
		int j = 0;
		while (*(p + k)[0] != 0x00)
		{
			for (int i = 0; i < wcslen(*(p + k)); i++)
			{
				str[j] = (*(p + k))[i];
				j++;
			}
			k++;
		}
		str[j] = '\0';
		wcstombs_s(0, st, wcslen(str) * MB_CUR_MAX + 1,str, wcslen(str));
		*log.stream<<st;
	}

	void WriteLog(LOG log)
	{
		std::time_t raw_time;
		tm time_info;
		char time_buf[80];
		std::time(&raw_time);
		localtime_s(&time_info, &raw_time);
		strftime(time_buf, sizeof(time_buf), "%c", &time_info);
		*log.stream << " ---- Протокол ------ " << time_buf<<" ---- \n";
	}

	void WriteParm(LOG log, Parm::PARM parm)
	{
		char ins[300], logs[300], outs[300];
		wcstombs_s(0, ins, wcslen(parm.in) * MB_CUR_MAX + 1, parm.in, wcslen(parm.in));
		wcstombs_s(0, logs, wcslen(parm.log) * MB_CUR_MAX + 1, parm.log, wcslen(parm.log));
		wcstombs_s(0, outs, wcslen(parm.out) * MB_CUR_MAX + 1, parm.out, wcslen(parm.out));
		*log.stream << " ---- Параметры ------ \n";
		*log.stream << ins << "\n";
		*log.stream << outs << "\n";
		*log.stream << logs << "\n";
	}

	void WriteIn(LOG log, In::INP in)
	{
		*log.stream << " ---- Исходные данные ------ \n";
		*log.stream << "Количество символов: " << in.size << "\n";
		*log.stream << "Количество строк: " << in.lines << "\n";
		*log.stream << "Проигнорировано: " << in.ignore << "\n";
	}

	void WriteError(LOG log,Out::OUTFILE out, Error::Error e)
	{
		if (log.stream->is_open())
		{
			*log.stream << "Error " << e.id << ": " << e.message << std::endl;
			*log.stream << "Строка " << e.inext.line << " Позиция " << e.inext.col << std::endl;
		}
		else
		{
			std::cout << "Error " << e.id << ": " << e.message << std::endl;
			std::cout << "Строка " << e.inext.line << " Позиция " << e.inext.col << std::endl;
		}
		if (out.stream->is_open())
		{
			*out.stream << "Error " << e.id << ": " << e.message << std::endl;
			*out.stream << "Строка " << e.inext.line << " Позиция " << e.inext.col << std::endl;
		}
	}

	void Close(LOG log)
	{
		log.stream->close();
	}

}