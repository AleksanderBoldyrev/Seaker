#include "Player.h"

Player::Player()
{
	name = 0;
}

Player::~Player()
{

}

void Player::SetName(char* n)
{
	name = n;
}

char* Player::GetName()
{
	return name;
}
