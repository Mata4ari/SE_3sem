#include "stdafx.h"
#include <Windows.h>
#include <tchar.h>
using namespace std;


int _tmain(int argc,_TCHAR* argv[])
{
	setlocale(LC_ALL, "rus");

	Log::LOG lg = Log::INITLOG;
	Out::OUTFILE out= Out::INITOUTFILE;
	try
	{
		Parm::PARM inputParm = Parm::getparm(argc, argv);
		
		lg = Log::getlog(inputParm.log);
		Log::WriteLine(lg, (char*)"Тест:", "без ошибок \n", "");
		Log::WriteLine(lg, (wchar_t*)L"Тест:", L"без ошибок \n", L"");
		Log::WriteLog(lg);
		Log::WriteParm(lg, inputParm);
		out = Out::getOut(inputParm.out);
		In::INP in = In::getin(inputParm.in);
		Out::writeOutFile(out, in.text);
		Log::WriteIn(lg, in);
		Log::Close(lg);

		delete[] in.text;
	}
	catch (Error::Error e)
	{
		Log::WriteError(lg,out, e);
	}

	return 0;
}