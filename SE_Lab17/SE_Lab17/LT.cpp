#include "stdafx.h"


namespace LT 
{
    LexTable LT::Create(int size)
    {
        //if(size>LT_MAXSIZE)

        LexTable* A=new LexTable;
        A->maxsize = size;
        A->size = 0;
        A->table = new Entry[size];
        return *A;
    }

    void Add(LexTable& lextable, Entry entry)
    {
        if (lextable.size + 1 > LT_MAXSIZE)
            throw ERROR_THROW(611);
        lextable.table[lextable.size] = entry;
        lextable.size++;
    }

    Entry GetEntry(LexTable& lextable, int n)
    {
        Entry A;
        A = lextable.table[n - 1];
        return A;
    }

    void Delete(LexTable& lextable)
    {
        delete[] lextable.table;
    }

    void PrintLexTable(LexTable& ltable,Error::Warning & warning)
    {
        int k = 1;
        std::ofstream f("TableLex.txt");
        if (!f.is_open())
           throw ERROR_THROW(601);
        f << k << " ";
        for (int i = 0; i < ltable.size; i++)
        {
            f << ltable.table[i].lexema[0];
            if (ltable.table[i].sn < ltable.table[i + 1].sn)
            {
                k++;
                f << std::endl;
                f << k << " ";
            }
        }
        f <<std:: endl;
        for (int i = 0; i < warning.size; i++)
        {
            f << "Ошибка " << warning.warnings[i].id << " " << warning.warnings[i].message << " Строка " << warning.warnings[i].inext.line << " Позиция " << warning.warnings[i].inext.col << "\n";
        }
        f.close();
    }
}
