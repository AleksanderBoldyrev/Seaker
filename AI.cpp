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

bool AI::PieceOfShip(cstate s, Field fuf)
{
	bool isp = false;
	if (s == fuf.body || s == fuf.left || s == fuf.right || s == fuf.onesh || s == fuf.up || s == fuf.down) isp = true;
	return isp;
}

bool AI::CheckSingleShip(Field& fuf)
{
	bool issing = true;
	if (fuf.posx > 0)
	{
		fuf.posx--;
		cstate stl = fuf.GetPosVal();
		if (PieceOfShip(stl, fuf)) issing = false;
		fuf.posx++;
	}
	if (fuf.posx < fuf.Width())
	{
		fuf.posx++; fuf.posx++;
		cstate str = fuf.GetPosVal();
		if (PieceOfShip(str, fuf)) issing = false;
		fuf.posx--; fuf.posx--;
	}
	if (fuf.posx > 0 && fuf.posy > 0)
	{
		fuf.posx--; fuf.posy--;
		cstate stu = fuf.GetPosVal();
		if (PieceOfShip(stu, fuf)) issing = false;
		fuf.posx++; fuf.posy++;
	}
	if (fuf.posx < fuf.Width() && fuf.posy < fuf.Height())
	{
		fuf.posy++; fuf.posy++;
		cstate std = fuf.GetPosVal();
		if (PieceOfShip(std, fuf)) issing = false;
		fuf.posy--; fuf.posy--;
	}
	return issing;
}

unsigned short AI::MakeMove(CUI clCUI, AI art, Field& fuf, Field& fcf, unsigned short cellcount)
{
	srand((unsigned)time(0));
	Sleep(500);
	bool isfirst = true;
	bool isturn  = true;
	bool hardchoice = true;
	unsigned short dir = 0;
	units x = 0, y = 0;
	clCUI.GotoXY(2 + fuf.Width(), 18 + fuf.Height());
	printf("Now is the turn of the computer.");
	clCUI.SetCursor(fuf, clCUI.x + 1, clCUI.y + 1);
	switch (this->level)
	{
	case (1) :						//*** Hard level. ***
		while (cellcount > 0 && isturn)
		{
			Sleep(500);
			cstate st;
			if (isshot)
			{
				fuf.posx;
				fuf.posy;
				dir = rand() % 4;
				switch (dir)
				{
				case(0) :			//*** Up. ***
					if (fuf.posy > 0) fuf.posy--;
					break;
				case(1) :			//*** Down. ***
					if (fuf.posy < fuf.Height()) fuf.posy++;
					break;
				case(2) :			//*** Left. ***
					if (fuf.posx > 0) fuf.posx--;
					break;
				case(3) :			//*** Right. ***
					if (fuf.posx < fuf.Width()) fuf.posx++;
					break;
				}
				st = fuf.GetPosVal();
			}
			else
			{
				fuf.posx = rand() % fuf.Width();
				fuf.posy = rand() % fuf.Height();
				st = fuf.GetPosVal();
				while (hardchoice)
				{
					hardchoice = rand() % 2;
					if (hardchoice)
					{
						fuf.posx = rand() % fuf.Width();
						fuf.posy = rand() % fuf.Height();
						st = fuf.GetPosVal();
						if (st != fuf.water && st != fuf.hit && st != fuf.miss) break;
					}
				}
			}
			cellcount = fuf.Fire(fuf.posx, fuf.posy, cellcount);
			if (st != fuf.water && st != fuf.hit && st != fuf.miss)
			{
				clCUI.GotoXY(fuf.posx + clCUI.x + 1, fuf.posy + clCUI.y + 1);
				clCUI.SetColor(clCUI.Yellow, clCUI.LightBlue);
				printf("%c", fuf.hit);
				clCUI.SetColor(clCUI.White, clCUI.Black);
				if (!CheckSingleShip(fuf)) 
				{
					isshot = true;
					//clCUI.WriteDot(fuf);
				}
			}
			else if (st == fuf.water)
			{
				clCUI.GotoXY(fuf.posx + clCUI.x + 1, fuf.posy + clCUI.y + 1);
				clCUI.SetColor(clCUI.LightCyan, clCUI.LightBlue);
				printf("%c", fuf.miss);
				clCUI.SetColor(clCUI.White, clCUI.Black);
				isturn = false;
			}
		}
		break;
	case (0) :						//*** Easy level. ***
		while (cellcount > 0 && isturn)
		{
			Sleep(500);
			fuf.posx = rand() % fuf.Width();
			fuf.posy = rand() % fuf.Height();
			cstate st = fuf.GetPosVal();
			cellcount = fuf.Fire(fuf.posx, fuf.posy, cellcount);
			if (st != fuf.water && st != fuf.hit && st != fuf.miss)
			{
				clCUI.GotoXY(fuf.posx + clCUI.x + 1, fuf.posy + clCUI.y + 1);
				clCUI.SetColor(clCUI.Yellow, clCUI.LightBlue);
				printf("%c", fuf.hit);
				clCUI.SetColor(clCUI.White, clCUI.Black);
			}
			else if (st == fuf.water)
			{
				clCUI.GotoXY(fuf.posx + clCUI.x + 1, fuf.posy + clCUI.y + 1);
				clCUI.SetColor(clCUI.LightCyan, clCUI.LightBlue);
				printf("%c", fuf.miss);
				clCUI.SetColor(clCUI.White, clCUI.Black);
				isturn = false;
			}
		}
		break;
	}
	while (cellcount > 0 && isturn)
	{
		Sleep(500);
		fuf.posx = rand() % fuf.Width();
		fuf.posy = rand() % fuf.Height();
		cstate st = fuf.GetPosVal();
		cellcount = fuf.Fire(fuf.posx, fuf.posy, cellcount);
		if (st != fuf.water && st != fuf.hit && st != fuf.miss)
		{
			clCUI.GotoXY(fuf.posx + clCUI.x + 1, fuf.posy + clCUI.y + 1);
			clCUI.SetColor(clCUI.Yellow, clCUI.LightBlue);
			printf("%c", fuf.hit);
			clCUI.SetColor(clCUI.White, clCUI.Black);
		}
		else if (st == fuf.water)
		{
			clCUI.GotoXY(fuf.posx + clCUI.x + 1, fuf.posy + clCUI.y + 1);
			clCUI.SetColor(clCUI.LightCyan, clCUI.LightBlue);
			printf("%c", fuf.miss);
			clCUI.SetColor(clCUI.White, clCUI.Black);
			isturn = false;
		}
		if (st == fuf.water) isturn = false;
	}
	return cellcount;
}
