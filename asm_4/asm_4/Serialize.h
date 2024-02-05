#pragma once
#include <fstream>

#define INT_DATA 0x01
#define STR_DATA 0x02

void serializeIN(std::ofstream* f, unsigned int data);
void serializeIN(std::ofstream* f, char* data);
