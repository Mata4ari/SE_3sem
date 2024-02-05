#include "stdafx.h"
using namespace std;

namespace IT 
{
    IdTable Create(int size)
    {
        //if(size > TI_MAXSIZE)

        IdTable* A = new IdTable;
        A->maxsize = size;
        A->size = 0;
        A->table = new Entry[size];
        return *A;
    }
    void Add(IdTable& idtable, Entry entry)
    {
        if (idtable.size + 1 > TI_MAXSIZE)
            throw ERROR_THROW(612);
        idtable.table[idtable.size] = entry;
        idtable.size++;
    }
    Entry GetEntry(IdTable& idtable, int n)
    {
        return idtable.table[n-1];
    }

    int IsId(IdTable& idtable, char id[ID_MAXSIZE],char pref[ID_MAXSIZE])
    {
        for (int i = 0; i < idtable.size; i++)
        {
                if (idtable.table[i].idtype==F)
                {
                    if (strcmp(idtable.table[i].id, id) == 0)
                    {
                            return i;
                    }
                }
                if (strcmp(idtable.table[i].id, id) == 0)
                {
                    if (strcmp(idtable.table[i].pref, pref) == 0)
                        return i;
                }
        }
        
        return TI_NULLIDX;
    }

    void Delete(IdTable& idtable)
    {
        delete[] idtable.table;
    }

    void PrintIdTable(IdTable& itable)
    {
        ofstream f("TableId.txt");
        if (!f.is_open())
            throw ERROR_THROW(601);
        for (int i = 0; i < itable.size; i++)
        {
            if (itable.table[i].id[0] == 'L')
            {
                if (itable.table[i].iddatatype == INT)
                {
                    f << itable.table[i].id << "\t" << itable.table[i].idxfirstLE << "\t" <<itable.table[i].value.vint<< endl;
                }
                else
                {
                    f << itable.table[i].id << "\t" << itable.table[i].idxfirstLE << "\t" << itable.table[i].value.vstr->str << endl;
                }
                continue;
            }
            if (itable.table[i].idtype==F)
            {
                f  << itable.table[i].id << "\t" << itable.table[i].idxfirstLE<< endl;
                continue;
            }
            
            f<<itable.table[i].pref << itable.table[i].id << "\t" << itable.table[i].idxfirstLE << endl;
            
        }
        f.close();
    }
}
