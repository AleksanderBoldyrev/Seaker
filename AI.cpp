#include "AI.h"

AI::AI(bool lv)
{
	level = lv;
}

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

void AI::PlaceShipsAI(Field& fcf)
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
				x = rand() % fcf.Width();
				y = rand() % fcf.Height();
				count1--;
				currcc -= 1;
				if (!fcf.CreateShip(x, y, len, sd)) switch (len)
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
			}
			else continue;
			break;
		case(2) :
			if (count2 != 0)
			{
				switch (sd)
				{
				case ('h') :
					x = rand() % (fcf.Width() - 1);
					y = rand() % fcf.Height();
					break;
				case ('v') :
					x = rand() % fcf.Width();
					y = rand() % (fcf.Height() - 1);
					break;
				}
				count2--;
				currcc -= 2;
				if (!fcf.CreateShip(x, y, len, sd)) switch (len)
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
			}
			else continue;
			break;
		case(3) :
			if (count3 != 0)
			{
				switch (sd)
				{
				case ('h') :
					x = rand() % (fcf.Width() - 2);
					y = rand() % fcf.Height();
					break;
				case ('v') :
					x = rand() % fcf.Width();
					y = rand() % (fcf.Height() - 2);
					break;
				}
				count3--;
				currcc -= 3;
				if (!fcf.CreateShip(x, y, len, sd)) switch (len)
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

			}
			else continue;
			break;
		case(4) :
			if (count4 != 0)
			{
				switch (sd)
				{
				case ('h') :
					x = rand() % (fcf.Width() - 3);
					y = rand() % fcf.Height();
					break;
				case ('v') :
					x = rand() % fcf.Width();
					y = rand() % (fcf.Height() - 3);
					break;
				}
				count4--;
				currcc -= 4;
				if (!fcf.CreateShip(x, y, len, sd)) switch (len)
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
			}
			else continue;
			break;
		}
	}
}

unsigned short AI::MakeMove(CUI clCUI, AI art, Field& fuf, Field& fcf, unsigned short cellcount)
{
	srand((unsigned)time(0));
	Sleep(500);
	bool isfirst = true;
	bool isturn  = true;
	units x = 0, y = 0;			// , sdnum;
	clCUI.GotoXY(0, 0);
	for (int i = 0; i <= 80; i++) printf(" ");
	clCUI.GotoXY(0, 0);
	printf("Now is the turn of the computer.");
	clCUI.SetCursor(fuf, clCUI.x + 1, clCUI.y + 1);
	clCUI.SetAim(fuf);
	while (cellcount > 0 && isturn)
	{
		Sleep(500);
		fuf.posx = rand() % fuf.Width();
		fuf.posy = rand() % fuf.Height();
		cstate st = fuf.GetPosVal();
		if (st != fuf.water && st != fuf.hit && st != fuf.miss)
		{
			fuf.Fire(fuf.posx, fuf.posy);
			clCUI.GotoXY(fuf.posx + 11, fuf.posy + 11);
			clCUI.SetColor(clCUI.Yellow, clCUI.LightBlue);
			printf("%c", fuf.hit);
			clCUI.SetColor(clCUI.White, clCUI.Black);
			cellcount--;
		}
		else if (st == fuf.water)
		{
			fuf.Miss(fuf.posx, fuf.posy);
			clCUI.GotoXY(fuf.posx + 11, fuf.posy + 11);
			clCUI.SetColor(clCUI.Yellow, clCUI.LightBlue);
			printf("%c", fuf.miss);
			clCUI.SetColor(clCUI.White, clCUI.Black);
			isturn = false;
		}
	}
	return cellcount;
}
