#include "Deserialize.h"
#include <iostream>

void deserialize(ifstream*f,ofstream*fo)
{
	unsigned int n;
	char temp[4];
	int k = 0;
	

	*fo << ".586" << endl;
	*fo << ".model flat, stdcall" << endl;
	*fo << "includelib kernel32.lib" << endl << endl;
	*fo << ".data" << endl;
	*fo << "ExitProcess PROTO :DWORD" << endl << endl;

	while (f->read(temp, 4))
	{
		sscanf_s(temp, "%x", &n);
		if (n == INT_DATA)
		{
			char buf[10];
			f->read(buf, 10);
			sscanf_s(buf, "%x", &n);
			*fo << "l" << k << " dword" << " " << n << endl;
			k++;
		}
		else if (n==STR_DATA)
		{
			int len;
			f->read(temp, 4);
			sscanf_s(temp, "%x", &len);
			*fo << "l" << k << " byte" << " " << len;
			if (len != 0)
				*fo << ',';
			while (len != 0)
			{
				f->read(temp, 4);
				sscanf_s(temp, "%x", &n);
				*fo << " " << n;
				if (len != 1)
					*fo << ',';
				len--;
			}
			*fo << endl;
			k++;
		}
		else
		{
			cout << "error";
		}
	}
	*fo << endl << ".code" << endl << endl;
	*fo << endl << "main proc" << endl << endl;
	*fo << "push - 1" << endl;
	*fo << "call ExitProcess" << endl;
	*fo << "main endp" << endl<<endl;
	*fo << "end main" << endl;
}