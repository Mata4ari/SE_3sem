#include <iostream>
#include <Windows.h>
#include <tchar.h>
#include "FST.h"
#include "Graphs.h"
using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{
	setlocale(LC_ALL, "rus");

	char str1[] = "a1";   
	FST::FST fst(IDENTIFICATOR(str1));
	
	if (FST::execute(fst))
		cout << "Цепочка " << fst.string << " распознана" << endl;
	else
		cout << "Цепочка " << fst.string << " не распознана" << endl;

	char a[] = "0xffffffff";
	unsigned int n;
	sscanf_s(a, "%x", &n);
	cout << n;

	return 0;
}