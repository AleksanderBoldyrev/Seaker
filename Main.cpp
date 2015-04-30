#include <iostream>

using namespace std;

#include "Types.h"
#include "AI.h"
#include "Player.h"
#include "CUI.h"
#include "Field.h"
#include "Ship.h"

unsigned short shipspl[5];
unsigned short shipsai[5];

bool PlaceShips(CUI clCUI, AI art, Field& fuf, Field& fcf)
{
	shipspl[0] = 10;
	shipspl[1] = 4;
	shipspl[2] = 3;
	shipspl[3] = 2;
	shipspl[4] = 1;
	shipsai[0] = 10;
	shipsai[1] = 4;
	shipsai[2] = 3;
	shipsai[3] = 2;
	shipsai[4] = 1;
	system("cls");
	printf("Now you should arrange your ships on the board.");
	bool sucplace = false;
	unsigned short key;
	short currcc = 20;
	dir sd = 'h';
	units len = 1;
	unsigned short  count1 = 4,
					count2 = 3,
					count3 = 2,
					count4 = 1,
					currc  = 0;
	clCUI.PrintGame(fuf, fcf);
	clCUI.SetCursor(fuf, clCUI.x + 1, clCUI.y + 1);
	clCUI.SetAim(fuf);
	fuf.posx = 0;
	fuf.posy = 0;
	while (currcc > 0)
	{
		while (!_kbhit());
		key = _getch();
		switch (key)
		{
		case (0x77) :					//*** 'w' ***
			clCUI.MoveAim('u', fuf, PLAYER);
			break;
		case (0x61) :					//*** 'a' ***
			clCUI.MoveAim('l', fuf, PLAYER);
			break;
		case (0x73) :					//*** 's' ***
			clCUI.MoveAim('d', fuf, PLAYER);
			break;
		case (0x64) :					//*** 'd' ***
			clCUI.MoveAim('r', fuf, PLAYER);
			break;
		case (0x31) :					//*** '1' - length ***
			len = 1;
			break;
		case (0x32) :					//*** '2' - length ***
			len = 2;
			break;
		case (0x33) :					//*** '3' - length ***
			len = 3;
			break;
		case (0x34) :					//*** '4' - length ***
			len = 4;
			break;
		case (0x20) :					//*** ' ' ***			
			switch (len)
			{
			case(1) :
				if (count1 != 0)
				{
					currc = count1;
					count1--;
					currcc -= 1;
				}
				else continue;
				break;
			case(2) :
				if (count2 != 0)
				{
					currc = count2;
					count2--;
					currcc -= 2;
				}
				else continue;
				break;
			case(3) :
				if (count3 != 0)
				{
					currc = count3;
					count3--;
					currcc -= 3;
				}
				else continue;
				break;
			case(4) :
				if (count4 != 0)
				{
					currc = count4;
					count4--;
					currcc -= 4;
				}
				else continue;
				break;
			}
			if (!fuf.CreateShip(fuf.posx, fuf.posy, len, sd)) switch (len)
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
			else
			{
				switch (sd)
				{
				case ('h') :
					for (int i = 1; i != len + 1; i++)
					{
						Sleep(300);
						clCUI.MoveAim('r', fuf, PLAYER);
					}
					break;
				case ('v') :
					for (int i = 1; i != len + 1; i++)
					{
						Sleep(300);
						clCUI.MoveAim('d', fuf, PLAYER);
					}
					break;
				}
			}
			break;
		case (0x72) :					//*** 'r' ***
			if (sd == 'h') sd = 'v';
			else if (sd == 'v') sd = 'h';
			break;
		case (0x78) :					//*** 'x' ***
			exit(0);
			break;
		default: continue;
		}
	}
	return sucplace;
}

unsigned short MakeMove(CUI clCUI, AI art, Field& fuf, Field& fcf, unsigned short cellcount)
{

	bool isturn = true;
	unsigned short key;
	clCUI.GotoXY(2 + fuf.Width(), 18 + fuf.Height());
	printf("Now is the turn of the player.");
	clCUI.SetCursor(fcf, fuf.Width() + clCUI.x + 2, clCUI.y + 1);
	clCUI.SetAim(fcf);
	fcf.posx = 0;
	fcf.posy = 0;
	while (cellcount > 0 && isturn)
	{
		while (!_kbhit());
		key = _getch();
		cstate st = fcf.GetPosVal();
		switch (key)
		{
		case (0x77) :					//*** 'w' ***
			clCUI.MoveAim('u', fcf, COMP);
			break;
		case (0x61) :					//*** 'a' ***
			clCUI.MoveAim('l', fcf, COMP);
			break;
		case (0x73) :					//*** 's' ***
			clCUI.MoveAim('d', fcf, COMP);
			break;
		case (0x64) :					//*** 'd' ***
			clCUI.MoveAim('r', fcf, COMP);
			break;
		case (0x66) :					//*** 'f' ***
			cellcount = fcf.Fire(fcf.posx, fcf.posy, cellcount);
			if (st != fcf.water && st != fcf.hit && st != fcf.miss)
			{
				clCUI.GotoXY(fcf.posx + clCUI.x + fcf.Width() + 2, fcf.posy + clCUI.y + 1);
				clCUI.SetColor(clCUI.Yellow, clCUI.LightBlue);
				printf("%c", fcf.hit);
				clCUI.SetColor(clCUI.White, clCUI.Black);
			}
			else if (st == fcf.water)
			{
				clCUI.GotoXY(fcf.posx + clCUI.x + fcf.Width() + 2, fcf.posy + clCUI.y + 1);
				clCUI.SetColor(clCUI.LightCyan, clCUI.LightBlue);
				printf("%c", fcf.miss);
				clCUI.SetColor(clCUI.White, clCUI.Black);
				isturn = false;
			}
			break;
		case (0x78) :					//*** 'x' ***
			exit(0);
			break;
		default: continue;
		}
	}
	return cellcount;
}

bool PlayTheGame(CUI clCUI, AI art, Field& fiu, Field& fic, bool turn)
{
	srand((unsigned)time(0));
	system("cls");
	bool pturn_is_first = true;
	bool aturn_is_first = true;
	unsigned short pcellcount = 20, ccellcount = 20;
	bool win = 0;
	while (true)
	{
		switch (turn)
		{
		case (1) :
			Sleep(300);
			if (pturn_is_first) PlaceShips(clCUI, art, fiu, fic);
			pcellcount = MakeMove(clCUI, art, fiu, fic, pcellcount);
			pturn_is_first = false;
			turn = 0;
			break;
		case (0) :
			Sleep(300);
			if (aturn_is_first) art.PlaceShipsAI(fic);
			ccellcount = art.MakeMove(clCUI, art, fiu, fic, ccellcount);
			aturn_is_first = false;
			turn = 1;
			break;
		}
		if (pcellcount <= 0)
		{
			win = 1;
			break;
		}
		if (ccellcount <= 0)
		{
			win = 0;
			break;
		}
	}
	return win;
}

int main()
{
	units w, h, lv;

	const unsigned short MAX_STRLEN = 80;

	char* nam = new char[80];
	Player pl1;
	AI artint;
	printf("Enter your name: ");
	gets(nam);
	pl1.SetName(nam);
	printf("Field of which length do you wish to create? (10..80) ");
	scanf("%d", &w);
	while (w < 10 || w > 80)
	{
		printf("\nPlease enter a valid number: (10..80) ");
		scanf("%d", &w);
	}
	printf("Field of which height do you wish to create? (10..80) ");
	scanf("%d", &h);
	while (h < 10 || h > 80)
	{
		printf("\nPlease enter a valid number: (10..80) ");
		scanf("%d", &h);
	}
	printf("What type of AI do you want to play with? (1|0) ");
	scanf("%d", &lv);
	while (lv < 0 || lv > 1)
	{
		printf("\nPlease enter a valid number: (1|0) ");
		scanf("%d", &lv);
	}
	artint.Setlevel(lv);
	CUI   clGUI(w, h);
	Field fc(COMP, w, h);
	Field fu(PLAYER, w, h);

	//*** Here thy game begins ***

	printf("=================== Here thy game begins! ===================\n\n\n");

	printf("Welcome to the \"Seaker\" game, %s!\n\n", pl1.GetName());
	char reply;
	int p_wins = 0, c_wins = 0, ties = 0;
	bool turn = true;
	printf("Do you wanna play some game? (y/n)\n");
	reply = _getch();
	while (reply != 'y' && reply != 'n')
	{
		printf("\nPlease enter a valid reply (y/n):");
		reply = _getch();
	}

	//***Here Game Loop begins.

	while (reply == 'y')
	{
		system("cls");
		fu.Wipe();
		fc.Wipe();
		
		bool winner = PlayTheGame(clGUI, artint, fu, fc, turn);
		clGUI.PrintGame(fu, fc);
		printf("Press any key. ");
		_getch();
		system("cls");

		switch (winner)
		{
		case 1:
			p_wins++;
			break;
		case 0:
			c_wins++;
			break;
		}
		printf("\n\tWinner statistic\nPlayer 1: %d, Player 2: %d\n", p_wins, c_wins);
		printf("Would you like to play again? (y/n): ");
		reply = _getch();
		while (reply != 'y' && reply != 'n')
		{
			printf("\nPlease enter a valid reply (y/n):");
			reply = _getch();
		}
	}

	//***Game Loop ends.

	system("pause");
	return 0;
}
