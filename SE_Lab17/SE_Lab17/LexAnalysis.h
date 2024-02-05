#pragma once
#define LT_SIZE 500
#define TI_SIZE 200
namespace Lex
{
	void Reading(wchar_t infile[]);
	void step(char* temp, LT::LexTable& ltable, IT::IdTable& itable, Error::Warning& warning);
	void step(char ch, LT::LexTable& ltable, IT::IdTable& itable, Error::Warning& warning);
	void normalize(char* str, IT::Entry& entry,IT::IdTable&);
}