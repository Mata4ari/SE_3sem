#include <iostream>
#include <fstream>
#include "Serialize.h"
#include "Deserialize.h"
using namespace std;

void main()
{

	ofstream* f = new ofstream;
	f->open("serialize.bin");
	char a[] = "hello";
	char a1[] = "world";
	char a2[] = "";
	unsigned int b1 = 0xffffffff;
	unsigned int b2 = 0;
	serializeIN(f, b1);
	serializeIN(f, a);
	serializeIN(f, b2);
	serializeIN(f, a1);
	serializeIN(f, a2);
	f->close();
	ifstream* fi = new ifstream;
	fi->open("serialize.bin", ios::out);
	ofstream* fo = new ofstream;
	fo->open("data.asm");
	deserialize(fi,fo);
	fo->close();
	fi->close();
}