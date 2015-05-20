#include "AI.h"

AI::AI()
{
	level = 0;
}

AI::~AI()
{
	
}

bool AI::Getlevel()
{
	return level;
}

void AI::Setlevel(bool lv)
{
	level = lv;
}

void AI::PlaceShipsAI(CUI* clCUI, Field* fcf)
{
	
	srand((unsigned)time(0));
	bool isfirst = true;
	units x = 0, y = 0, sdnum;
	short currcc = 20;
	dir sd = 'h';
	units len = 1;
	unsigned short  count1 = 4,
					count2 = 3,
					count3 = 2,
					count4 = 1;
	while (currcc > 0)
	{
		sdnum = rand() % 2;
		switch (sdnum)
		{
		case (0) :
			sd = 'h';
			break;
		case (1) :
			sd = 'v';
			break;
		}
		len = rand() % 5;
		if (len == 0) continue;
		switch (len)
		{
		case(1) :
			if (count1 != 0)
			{
				x = rand() % fcf->Width();
				y = rand() % fcf->Height();
				count1--;
				currcc -= 1;
				if (!fcf->CreateShip(x, y, len, sd)) switch (len)
				{
				case(1) :
					count1++;
					currcc += 1;
					break;
				case(2) :
					count2++;
					currcc += 2;
					break;
				case(3) :
					count3++;
					currcc += 3;
					break;
				case(4) :
					count4++;
					currcc += 4;
					break;
				}
				else clCUI->AddShipState(COMP, 1, 10);
			}
			else continue;
			break;
		case(2) :
			if (count2 != 0)
			{
				switch (sd)
				{
				case ('h') :
					x = rand() % (fcf->Width() - 1);
					y = rand() % fcf->Height();
					break;
				case ('v') :
					x = rand() % fcf->Width();
					y = rand() % (fcf->Height() - 1);
					break;
				}
				count2--;
				currcc -= 2;
				if (!fcf->CreateShip(x, y, len, sd)) switch (len)
				{
				case(1) :
					count1++;
					currcc += 1;
					break;
				case(2) :
					count2++;
					currcc += 2;
					break;
				case(3) :
					count3++;
					currcc += 3;
					break;
				case(4) :
					count4++;
					currcc += 4;
					break;
				}
				else clCUI->AddShipState(COMP, 2, 10);
			}
			else continue;
			break;
		case(3) :
			if (count3 != 0)
			{
				switch (sd)
				{
				case ('h') :
					x = rand() % (fcf->Width() - 2);
					y = rand() % fcf->Height();
					break;
				case ('v') :
					x = rand() % fcf->Width();
					y = rand() % (fcf->Height() - 2);
					break;
				}
				count3--;
				currcc -= 3;
				if (!fcf->CreateShip(x, y, len, sd)) switch (len)
				{
				case(1) :
					count1++;
					currcc += 1;
					break;
				case(2) :
					count2++;
					currcc += 2;
					break;
				case(3) :
					count3++;
					currcc += 3;
					break;
				case(4) :
					count4++;
					currcc += 4;
					break;
				}
				else clCUI->AddShipState(COMP, 3, 10);
			}
			else continue;
			break;
		case(4) :
			if (count4 != 0)
			{
				switch (sd)
				{
				case ('h') :
					x = rand() % (fcf->Width() - 3);
					y = rand() % fcf->Height();
					break;
				case ('v') :
					x = rand() % fcf->Width();
					y = rand() % (fcf->Height() - 3);
					break;
				}
				count4--;
				currcc -= 4;
				if (!fcf->CreateShip(x, y, len, sd)) switch (len)
				{
				case(1) :
					count1++;
					currcc += 1;
					break;
				case(2) :
					count2++;
					currcc += 2;
					break;
				case(3) :
					count3++;
					currcc += 3;
					break;
				case(4) :
					count4++;
					currcc += 4;
					break;
				}
				else clCUI->AddShipState(COMP, 4, 10);
			}
			else continue;
			break;
		}
	}
}

bool AI::PieceOfShip(cstate s, Field* fuf)
{
	bool isp = false;
	if (s == fuf->body || s == fuf->left || s == fuf->right || s == fuf->onesh || s == fuf->up || s == fuf->down) isp = true;
	return isp;
}

void AI::MakeMove(CUI* clCUI, AI* art, Field* fuf, Field* fcf)
{
	unsigned short clen;
	srand((unsigned)time(0));
	Sleep(500);
	bool isfirst = true;
	bool isturn  = true;
	bool nextship = true;
	bool hardchoice = true;
	static bool wasmiss = false;
	unsigned short dir = 0;
	units x = 0, y = 0;
	clCUI->SetCursor(fuf, clCUI->x + 1, clCUI->y + 1);
	switch (this->level)
	{
	case (1) :						//*** Hard level. ***
		while (fuf->shipsnum[0] > 0 && isturn)
		{
			Sleep(500);
			cstate st;
			if ((isshot || wasmiss) && !nextship)
			{
				fuf->posx;
				fuf->posy;
				dir = rand() % 4;
				switch (dir)
				{
				case(0) :			//*** Up. ***
					if (fuf->posy > 0) fuf->posy--;
					break;
				case(1) :			//*** Down. ***
					if (fuf->posy < fuf->Height() - 1) fuf->posy++;
					break;
				case(2) :			//*** Left. ***
					if (fuf->posx > 0) fuf->posx--;
					break;
				case(3) :			//*** Right. ***
					if (fuf->posx < fuf->Width() - 1) fuf->posx++;
					break;
				}
				st = fuf->GetPosVal();

				clen = fuf->Fire(fuf->posx, fuf->posy);
				if (st != fuf->water && st != fuf->hit && st != fuf->miss)
				{
					clCUI->PaintHM (true, PLAYER, fuf);
					isshot = true;	
					if (clen != 0) 
					{
						clCUI->RemShipState(PLAYER, clen, 10);
						isshot = true;
						nextship = true;
					}
					wasmiss = false;
				}
				else if (st == fuf->water)
				{
					clCUI->PaintHM(false, PLAYER, fuf);
					isturn = false;
					if (isshot)
					{
						isshot = false;						//TODO: ship find.
						wasmiss = true;
						if (fuf->posx > 0) fuf->posx--;
						st = fuf->GetPosVal();
						if (st == fuf->hit) continue;
						if (fuf->posx < fuf->Width() - 1) fuf->posx++; if (fuf->posx < fuf->Width() - 1) fuf->posx++;
						st = fuf->GetPosVal();
						if (st == fuf->hit) continue;
						if (fuf->posx > 0) fuf->posx--; if (fuf->posy < fuf->Height() - 1) fuf->posy++;
						st = fuf->GetPosVal();
						if (st == fuf->hit) continue;
						if (fuf->posy > 0) fuf->posy--; if (fuf->posy > 0) fuf->posy--;
						st = fuf->GetPosVal();
						if (st == fuf->hit) continue;
					}
				}
				else if (st == fuf->miss)
				{
					if (fuf->posx > 0) fuf->posx--;
					st = fuf->GetPosVal();
					if (st == fuf->hit) continue;
					if (fuf->posx < fuf->Width() - 1) fuf->posx++; if (fuf->posx < fuf->Width() - 1) fuf->posx++;
					st = fuf->GetPosVal();
					if (st == fuf->hit) continue;
					if (fuf->posx > 0) fuf->posx--; if (fuf->posy < fuf->Height() - 1) fuf->posy++;
					st = fuf->GetPosVal();
					if (st == fuf->hit) continue;
					if (fuf->posy > 0) fuf->posy--; if (fuf->posy > 0) fuf->posy--;
					st = fuf->GetPosVal();
					if (st == fuf->hit) continue;
				}
			}
			else
			{
				fuf->posx = rand() % fuf->Width();
				fuf->posy = rand() % fuf->Height();
				st = fuf->GetPosVal();
				while (hardchoice)
				{
					hardchoice = rand() % 2;
					if (hardchoice)
					{
						fuf->posx = rand() % fuf->Width();
						fuf->posy = rand() % fuf->Height();
						st = fuf->GetPosVal();
						if (st != fuf->water && st != fuf->hit && st != fuf->miss) break;
					}
				}
			}
			clen = fuf->Fire(fuf->posx, fuf->posy);
			if (st != fuf->water && st != fuf->hit && st != fuf->miss)
			{
				clCUI->PaintHM(true,  PLAYER, fuf);
				if (clen != 0) clCUI->RemShipState(PLAYER, clen, 10);
				isshot = true;							//TODO: Aftermath().
				wasmiss = false;
			}
			else if (st == fuf->water)
			{
				clCUI->PaintHM(false, PLAYER, fuf);
				if (isshot) isshot = false;				//TODO: ship find.
				isturn = false;
			}
		}
		break;
	case (0) :						//*** Easy level. ***
		while (fuf->shipsnum[0] > 0 && isturn)
		{
			Sleep(500);
			fuf->posx = rand() % fuf->Width();
			fuf->posy = rand() % fuf->Height();
			cstate st = fuf->GetPosVal();
			clen = fuf->Fire(fuf->posx, fuf->posy);
			if (st != fuf->water && st != fuf->hit && st != fuf->miss)
			{
				clCUI->PaintHM(true,  PLAYER, fuf);
				if (clen != 0) clCUI->RemShipState(PLAYER, clen, 10);
			}
			else if (st == fuf->water)
			{
				clCUI->PaintHM(false, PLAYER, fuf);
				isturn = false;
			}
		}
		break;
	}
}
