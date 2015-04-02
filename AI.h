#ifndef _AI_H
#define _AI_H

#include <ctime>
#include "Field.h"
#include "CUI.h"
#include "Types.h"

class AI
{
	bool			level;
public:
					AI();
					AI(bool lv);
					~AI();
	bool			Getlevel();
	void 			PlaceShipsAI(Field& fcf);
	unsigned short 	MakeMove(CUI clCUI, AI art, Field& fuf, Field& fcf, unsigned short cellcount);
};

#endif
