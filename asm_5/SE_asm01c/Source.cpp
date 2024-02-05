#include <iostream>
using namespace std;


extern "C" int __stdcall findmin(int a, int* b);
extern "C" int __stdcall findmax(int a, int* b);


void main()
{
	int arr[] = { 4,3,11,2,46,111,57,88,953,10 };
	int n = 10;
	int min = findmin(n,arr);
	int max = findmax(n,arr);
	cout << min << " + " << max << " = " << min + max;
}