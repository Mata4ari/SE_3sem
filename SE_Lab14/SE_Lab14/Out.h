#pragma once

namespace Out
{
	struct OUTFILE
	{
		std::ofstream* stream;
	};
	static const OUTFILE INITOUTFILE{ nullptr };
	OUTFILE getOut(wchar_t outfile[]);
	void writeOutFile( OUTFILE out,unsigned char* text);
}