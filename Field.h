#ifndef _FIELD_H
#define _FIELD_H

#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <vector>

using namespace std;

#include "Types.h"

class Field
{
	units   				wcells, hcells;
	vector<vector<cstate>>	cells;
	units					wc = 10,				 hc = 10;
	
	void					SetCell					 (units w, units h, cstate s);
	cstate 					GetCell					 (units w, units h);
	unsigned short			Aftermath				 (units px, units py);
public:
	const cstate			water					 = 0x20;
	const cstate			miss					 = 0x0F;
	const cstate			up						 = 0x1E;
	const cstate			down					 = 0x1F;
	const cstate			left					 = 0x11;
	const cstate			right					 = 0x10;
	const cstate			body					 = 0xFE;
	const cstate			onesh					 = 0x04;
	const cstate			hit						 = 0x06;
	const cstate			err						 = 0xFF;

	unsigned short			shipsnum[5];
	bool 					owner;											//True == Player; False == AI.
	units					posx = 0,				 posy = 0;

							Field					 (bool who, units sx, units sy);
							~Field					 ();
	units					Width					 ()  { return wcells; }
	units					Height					 ()  { return hcells; }
	void					Wipe					 ();
	bool 					SetPos					 (units x, units y);
	cstate					GetPosVal				 ();
	unsigned short			Fire					 (units px, units py);
	bool					CreateShip				 (units x, units y, units l, dir vdir);
	bool					ShipSpaceIsChecked		 (units x, units y, units l, dir vdir);
	bool					CenterCellSpaceIsChecked (units cellx, units celly, units le, dir di, units ord);
};

#endif
