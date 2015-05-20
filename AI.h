#ifndef _AI_H
#define _AI_H

#include <ctime>
#include "Field.h"
#include "CUI.h"
#include "Types.h"

class AI
{
	bool			level;
	bool			isshot  = false;
public:
					AI();
					~AI();
	bool			Getlevel();
	void			Setlevel(bool lv);
	void 			PlaceShipsAI(CUI* clCUI, Field* fcf);
	bool			PieceOfShip(cstate s, Field* fuf);
	void		 	MakeMove(CUI* clCUI, AI* art, Field* fuf, Field* fcf);
};

#endif
