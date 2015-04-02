#ifndef _PLAYER_H
#define _PLAYER_H

#include "Types.h"

class Player
{
	char*	name;
public:
			Player();
			~Player();
	char*	GetName();
	void	SetName(char* name);
	};

#endif
