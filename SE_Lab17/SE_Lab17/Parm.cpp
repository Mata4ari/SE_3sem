#include "stdafx.h"


namespace Parm
{
	PARM getparm(int argc, _TCHAR* argv[])
	{
		PARM inputParms;
		if(argc>1)
		{
			if(wcslen(argv[1]) > PARM_MAX_SIZE)
				throw ERROR_THROW(104);
			if (wcsstr(argv[1], PARM_IN) == NULL)
			{
				throw ERROR_THROW(100);
			}
			else
			{
				wcscpy_s(inputParms.in, argv[1]);
			}
		}
		else
		{
			throw ERROR_THROW(100);
		}
		
		//---------------------------------------------
		if (argc>2)
		{
			if (wcslen(argv[2]) > PARM_MAX_SIZE)
				throw ERROR_THROW(104);
			if (wcsstr(argv[2], PARM_OUT) == NULL&& wcsstr(argv[2], PARM_LOG) == NULL)
			{
				throw ERROR_THROW(101);
			}
			else
			{
				if(wcsstr(argv[2], PARM_OUT) != NULL)
				{
					wcscpy_s(inputParms.out, argv[2]);
				}
				if (wcsstr(argv[2], PARM_LOG) != NULL)
				{
					wcscpy_s(inputParms.out, PARM_OUT);
					wcscpy_s(inputParms.log, argv[2]);
					wcscat_s(inputParms.out, &(argv[1])[4]);
					wcscat_s(inputParms.out, L".out");
					wcscat_s(inputParms.log, L".log");
					return inputParms;
				}
			}
		}
		else
		{
			wcscpy_s(inputParms.out, PARM_OUT);
			wcscat_s(inputParms.out, &(argv[1])[4]);
		}
		//-------------------------------------------------


		if (argc > 3)
		{
			if (wcslen(argv[3]) > PARM_MAX_SIZE)
				throw ERROR_THROW(104);
			if (wcsstr(argv[3], PARM_LOG) == NULL)
			{
				throw ERROR_THROW(102);
			}
			else
			{
				wcscpy_s(inputParms.log, argv[3]);
			}
		}
		else
		{
			wcscpy_s(inputParms.log, PARM_LOG);
			wcscat_s(inputParms.log, &(argv[1])[4]);
		}
		wcscat_s(inputParms.out, L".out");
		wcscat_s(inputParms.log, L".log");
		return inputParms;
	}
}