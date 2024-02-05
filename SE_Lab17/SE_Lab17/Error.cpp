#include "stdafx.h"

namespace Error 
{
	Error errors[ERROR_MAX_ENTRY] =
	{
		ERROR_ENTRY(0,"Недопустимый код ошибки"),
		ERROR_ENTRY(1,"Системный сбой"),
		ERROR_ENTRY_NODEF(2),ERROR_ENTRY_NODEF(3),ERROR_ENTRY_NODEF(4),ERROR_ENTRY_NODEF(5),ERROR_ENTRY_NODEF(6),ERROR_ENTRY_NODEF(7),
		ERROR_ENTRY_NODEF(8),ERROR_ENTRY_NODEF(9),
		ERROR_ENTRY_NODEF10(10),ERROR_ENTRY_NODEF10(20),ERROR_ENTRY_NODEF10(30),ERROR_ENTRY_NODEF10(40),ERROR_ENTRY_NODEF10(50),
		ERROR_ENTRY_NODEF10(60),ERROR_ENTRY_NODEF10(70),ERROR_ENTRY_NODEF10(80),ERROR_ENTRY_NODEF10(90),
		ERROR_ENTRY(100,"Параметр -in должен быть задан"),
		ERROR_ENTRY(101,"Неверно указан второй параметр"),
		ERROR_ENTRY(102,"Неверно указан третий параметр"),
		ERROR_ENTRY_NODEF(103),
		ERROR_ENTRY(104,"Превышена длина входного параметра"),
		ERROR_ENTRY_NODEF(105),ERROR_ENTRY_NODEF(106),ERROR_ENTRY_NODEF(107),ERROR_ENTRY_NODEF(108),ERROR_ENTRY_NODEF(109),
		ERROR_ENTRY(110,"Ошибка при открытии файла с исходным кодом (-in)"),
		ERROR_ENTRY(111,"Недопустимый символ в исходном файле (-in)"),
		ERROR_ENTRY(112,"Ошибка при создании файла протокола (-log)"),
		ERROR_ENTRY(113,"Ошибка при создании файла out"),
		ERROR_ENTRY_NODEF(114),ERROR_ENTRY_NODEF(115),ERROR_ENTRY_NODEF(116),ERROR_ENTRY_NODEF(117),ERROR_ENTRY_NODEF(118),
		ERROR_ENTRY_NODEF(119),ERROR_ENTRY_NODEF10(120),ERROR_ENTRY_NODEF10(130),ERROR_ENTRY_NODEF10(140),ERROR_ENTRY_NODEF10(150),
		ERROR_ENTRY_NODEF10(160),ERROR_ENTRY_NODEF10(170),ERROR_ENTRY_NODEF10(180),ERROR_ENTRY_NODEF10(190),ERROR_ENTRY_NODEF100(200),
		ERROR_ENTRY_NODEF100(300),ERROR_ENTRY_NODEF100(400),ERROR_ENTRY_NODEF100(500),
		ERROR_ENTRY(600,"Ошибка открытия входного файла лексического анализатора"),
		ERROR_ENTRY(601,"Ошибка открытия выходного файла"),
		ERROR_ENTRY(602,""),
		ERROR_ENTRY_NODEF(603),
		ERROR_ENTRY(604,"Превышен размер строкового литерала"),
		ERROR_ENTRY_NODEF(605),ERROR_ENTRY_NODEF(606),ERROR_ENTRY_NODEF(607),ERROR_ENTRY_NODEF(608),ERROR_ENTRY_NODEF(609),
		ERROR_ENTRY(610,"Превышен размер числового литерала"),
		ERROR_ENTRY(611,"Таблица лексем переполненна"),
		ERROR_ENTRY(612,"Таблица идентификаторов переполненна"),
		ERROR_ENTRY(613,"Выражение не распознано"),
		ERROR_ENTRY_NODEF(614),ERROR_ENTRY_NODEF(615),ERROR_ENTRY_NODEF(616),ERROR_ENTRY_NODEF(617),ERROR_ENTRY_NODEF(618),
		ERROR_ENTRY_NODEF(619),ERROR_ENTRY_NODEF10(620),ERROR_ENTRY_NODEF10(630),ERROR_ENTRY_NODEF10(640),ERROR_ENTRY_NODEF10(650),
		ERROR_ENTRY_NODEF10(660),ERROR_ENTRY_NODEF10(670),ERROR_ENTRY_NODEF10(680),ERROR_ENTRY_NODEF10(690),
		ERROR_ENTRY_NODEF100(700),ERROR_ENTRY_NODEF100(800),ERROR_ENTRY_NODEF100(900)
	};

	Error geterror(int id)
	{
		if (id<0 || id>=ERROR_MAX_ENTRY)
		{
			return errors[0];
		}
		else
		{
			return errors[id];
		}
	}


	Error geterrorin(int id, int line = -1, int col = -1)
	{
		Error e;
		if (id < 0 || id >= ERROR_MAX_ENTRY)
		{
			return errors[0];
		}
		else
		{
			int i = 0;
			e.id = id;
			while (errors[id].message[i] != '\0')
			{
				e.message[i] = errors[id].message[i];
				i++;
			}
			e.message[i] = '\0';
			e.inext.line = line;
			e.inext.col = col;
			return e;
		}
	}

	Error getwarning(int id, int line = -1, int col = -1)
	{
		Error e;
		if (id < 0 || id >= ERROR_MAX_ENTRY)
		{
			return errors[0];
		}
		else
		{
			int i = 0;
			e.id = id;
			while (errors[id].message[i] != '\0')
			{
				e.message[i] = errors[id].message[i];
				i++;
			}
			e.message[i] = '\0';
			e.inext.line = line;
			e.inext.col = col;
			return e;
		}
	}
	void putwarning(Warning& warning, Error e)
	{
		warning.warnings[warning.size] = e;
		warning.size++;
	}
	void printerror(Error e)
	{
		std::cout << e.id << " " << e.message;
	}
}