#include "Serialize.h"
#include <fstream>
#include <iostream>
using namespace std;

void serializeIN(ofstream* f,unsigned int data)
{
	unsigned int n = data;
	unsigned int length = 0; do { length++; } while (n /= 16);

	*f << "0x010x";
	for (int i = 0; i < 8 - length;i++)
		*f << "0";
	*f << hex<<data;
}

void serializeIN(ofstream* f, char* data)
{
	*f << "0x020x";
	int length = strlen(data);
	if (length < 16)
		*f << "0";
	*f << hex << length+1;
	for (int i = 0; i <= length; i++)
	{
		*f << "0x";
		if ((short)data[i] < 16)
			*f << "0";
		*f << hex << (short)data[i];
	}
}