#include "FST.h"
#include <string.h>
#include <algorithm>
#include <iostream>

namespace FST
{
	RELATION::RELATION(char c, short ns)
	{
		this->symbol = c;
		this->nnode = ns;
		//std::cout << this->symbol << "\n";
	}

	NODE::NODE()
	{
		this->n_relation = 0;
		this->relations = NULL;
	}

	NODE::NODE(short n, RELATION rel, ...)
	{
		this->n_relation = n;
		RELATION *p = &rel;
		relations = new RELATION[n];
		for (short i = 0; i < n; i++)
		{
			//std::cout << p[i].symbol;
			relations[i] = p[i];
		}
	}

	FST::FST(char* s, short ns, NODE n, ...)
	{
		this->string = s;
		this->nstates = ns;
		this->nodes = new NODE[ns];
		NODE* p = &n;
		for (int i = 0; i < ns; i++)
			nodes[i] = p[i];
		this->rstates = new short[nstates];
		memset(this->rstates, 0xff, sizeof(short) * nstates);
		rstates[0] = 0;
		this->position = -1;
	}

	bool step(FST& fst, short*& rstates)
	{
		bool rc = false;
		/*for (int i = 0; i < 4; i++)
		{
			std::cout << rstates[i] << " " << fst.rstates[i] << std::endl;
		}
		std:: cout << "\n";*/
		std::swap(rstates, fst.rstates);
		for (short i = 0; i < fst.nstates; i++)
		{
			if (rstates[i] == fst.position)
			{
				for (short j = 0; j < fst.nodes[i].n_relation; j++)
				{
					if (fst.nodes[i].relations[j].symbol == fst.string[fst.position])
					{

						fst.rstates[fst.nodes[i].relations[j].nnode] = fst.position + 1;
						rc = true;
					}
				}
				
			}
		}
		return rc;
	}

	bool execute(FST& fst)
	{
		short* rstates = new short[fst.nstates];
		memset(rstates, 0xff, sizeof(short) * fst.nstates);
		short lstring = strlen(fst.string);
		bool rc = true;
		for (short i = 0; i < lstring && rc; i++)
		{
			fst.position++;
			rc = step(fst, rstates);
		}
		delete[] rstates;
		//std::cout << fst.rstates[fst.nstates - 1] << "\n";
		return (rc?(fst.rstates[fst.nstates-1]==lstring):rc);
	}

}