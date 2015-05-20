#include "CUI.h"

HANDLE hConsole;
HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);

CUI::CUI(units w, units h)
{
	_w = w;
	_h = h;
	c1		= new short(0);
	c2		= new short(10);
	c3		= new short(20);
	c4		= new short(30);

	k1		= new short(0);
	k2		= new short(10);
	k3		= new short(20);
	k4		= new short(30);

	l1		= new short(0);
	l2		= new short(10);
	l3		= new short(20);
	l4		= new short(30);

	d1		= new short(0);
	d2		= new short(10);
	d3		= new short(20);
	d4		= new short(30);
}

CUI::~CUI()
{
	delete c1; 
	delete c2; 
	delete c3; 
	delete c4; 
	delete k1; 
	delete k2; 
	delete k3; 
	delete k4; 
	delete l1; 
	delete l2; 
	delete l3; 
	delete l4;
	delete d1; 
	delete d2; 
	delete d3; 
	delete d4;
}

void CUI::GotoXY(int xx, int yy)			//Fecit per asini.
{
	COORD coord = { xx, yy };
	SetConsoleCursorPosition(hStdOut, coord);
}

void CUI::SetColor(short textcolor, short bgcolor)
{
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hStdOut, (WORD)((bgcolor << 4) | textcolor));
}

void CUI::Draw(Field* f)					//Verpa et feces caninae sunt!
{
	cstate st = f->GetPosVal();
	if (st == f->up || st == f->down || st == f->left || st == f->right || st == f->onesh || st == f->body || st == f->water)
	{
		SetColor(clship, clback);
		if (f->owner == COMP) printf("%c", f->water);
		else printf("%c", st);
	}
	if (st == f->miss || st == f->hit)
	{
		if (st == f->miss) SetColor(clmiss, clback);
		else SetColor(clhit, clback);
		printf("%c", st);
	}
	SetColor(cldef, clbdef);
}

void CUI::SetCursor(Field* f, unsigned short fx, unsigned short fy)
{
	GotoXY(fx, fy);		//insert design-oriented componentz
	//...............................................................................
}

void CUI::SetAim(Field* f)
{
	SetColor(claim, clback);
	printf("%c", '+');
	SetColor(cldef, clbdef);
}

void CUI::MoveAim(dir where, Field* f, bool who)
{
	switch (where)
	{
	case ('u') :
		//if (f->posy == 0) break;										//*** For the old board-cross restrict version. ***
		if (who == PLAYER) GotoXY(f->posx + x + 1, f->posy + y + 1);
		if (who == COMP)   GotoXY(f->posx + x + f->Width() + 2, f->posy + y + 1);
		Draw(f);
		SetColor(claim, clback);
		if (f->posy == 0) f->SetPos(f->posx, f->posy += f->Height() - 1);
		else f->SetPos(f->posx, --f->posy);
		if (who == PLAYER) GotoXY(f->posx + x + 1, f->posy + y + 1);
		if (who == COMP)   GotoXY(f->posx + x + f->Width() + 2, f->posy + y + 1);
		printf("%c", '+');
		break;
	case ('d') :
		//if (f->posy == f->Height() - 1) break;						//*** For the old board-cross restrict version. ***
		if (who == PLAYER) GotoXY(f->posx + x + 1, f->posy + y + 1);
		if (who == COMP)   GotoXY(f->posx + x + f->Width() + 2, f->posy + y + 1);
		Draw(f);
		SetColor(claim, clback);
		if (f->posy == f->Height() - 1) f->SetPos(f->posx, f->posy -= f->Height() - 1);
		else f->SetPos(f->posx, ++f->posy);
		if (who == PLAYER) GotoXY(f->posx + x + 1, f->posy + y + 1);
		if (who == COMP)   GotoXY(f->posx + x + f->Width() + 2, f->posy + y + 1);
		printf("%c", '+');
		break;
	case ('l') :
		//if (f->posx == 0) break;										//*** For the old board-cross restrict version. ***
		if (who == PLAYER) GotoXY(f->posx + x + 1, f->posy + y + 1);
		if (who == COMP)   GotoXY(f->posx + x + f->Width() + 2, f->posy + y + 1);
		Draw(f);
		SetColor(claim, clback);
		if (f->posx == 0) f->SetPos(f->posx += f->Width() - 1, f->posy);
		else f->SetPos(--f->posx, f->posy);
		if (who == PLAYER) GotoXY(f->posx + x + 1, f->posy + y + 1);
		if (who == COMP)   GotoXY(f->posx + x + f->Width() + 2, f->posy + y + 1);
		printf("%c", '+');
		break;
	case ('r') :
		//if (f->posx == f->Width() - 1) break;							//*** For the old board-cross restrict version. ***
		if (who == PLAYER) GotoXY(f->posx + x + 1, f->posy + y + 1);
		if (who == COMP)   GotoXY(f->posx + x + f->Width() + 2, f->posy + y + 1);
		Draw(f);
		SetColor(claim, clback);
		if (f->posx == f->Width() - 1) f->SetPos(f->posx -= f->Width() - 1, f->posy);
		else f->SetPos(++f->posx, f->posy);
		if (who == PLAYER) GotoXY(f->posx + x + 1, f->posy + y + 1);
		if (who == COMP)   GotoXY(f->posx + x + f->Width() + 2, f->posy + y + 1);
		printf("%c", '+');
		break;
	}
	SetColor(cldef, clbdef);
}

void CUI::PrintFrame()
{
	//*** Corners of the frame. ***

	SetColor(clframe, clbframe);
	GotoXY(x, y);								printf("\xC9");
	GotoXY(x + _w + 1, y);						printf("\xCB");
	GotoXY(x + 2 * _w + 2, y);					printf("\xBB");
	GotoXY(x, y + _h + 1);						printf("\xC8");
	GotoXY(x + _w + 1, y + _h + 1);				printf("\xCA");
	GotoXY(x + 2 * _w + 2, y + _h + 1);			printf("\xBC");

	//*** Horizontal boarding. ***

	units i;
	units ix = x + 1;
	units iy = y;
	for (i = 0; i < _w; i++)
	{
		GotoXY(ix, iy);							printf("\xCD");
		GotoXY(ix + _w + 1, iy);				printf("\xCD");
		GotoXY(ix, iy + _h + 1);				printf("\xCD");
		GotoXY(ix + _w + 1, iy + _h + 1);		printf("\xCD");
		ix++;									//*** Nya! ***
	}

	//*** Vertical boarding. ***

	ix = x;
	iy = y + 1;
	for (i = 0; i < _h; i++)
	{
		GotoXY(ix, iy);							printf("\xBA");
		GotoXY(ix + _w + 1, iy);				printf("\xBA");
		GotoXY(ix + 2 * _w + 2, iy);			printf("\xBA");
		iy++;
	}
	SetColor(cldef, clbdef);
}

void CUI::PrintField(Field* f)
{
	int xx;
	if (f->owner == PLAYER) xx = 1 + x;
	else xx = 2 + _w + x;
	units fx = 0, fy = 0;
	for (int h = y + 1; h != _h + y + 1; h++) for (int w = xx; w != _w + xx; w++)
	{
		GotoXY(w, h);
		fx = w - xx;
		fy = h - y - 1;
		f->SetPos(fx, fy);
		SetColor(clship, clback);
		printf("%c", (char)f->GetPosVal());
	}
	GotoXY(x, y + _h + 3);
	SetColor(cldef, clbdef);
}

void CUI::PrintGame(Field* cf, Field* uf)
{
	system("cls");
	this->PrintWin(uf);
	this->PrintFrame();
	this->PrintField(uf);
	this->PrintField(cf);
}

void CUI::PrintWin(Field* uf)
{
	int i;
	SetColor(clframe, clbframe);
	GotoXY(0, 0);
	for (i = 0; i != 37; i++) printf("%c", 0x20);
	printf("SEAKER");
	for (i = 0; i != 37; i++) printf("%c", 0x20);
	
	//*** Horisontal lines. ***

	GotoXY(0, 1);
	for (i = 0; i != 80; i++) 
	{
		if (i % 10 == 0 && i < 60 && i > 0) printf("\xCB");
		else printf("\xCD");
	}
	GotoXY(0, 3);
	for (i = 0; i != 80; i++) 
	{
		if (i % 10 == 0 && i < 60 && i > 0) printf("\xCE");
		else printf("\xCD");
	}
	GotoXY(0, 7);
	for (i = 0; i != 80; i++) 
	{
		if (i == 10) printf("\xCE");
		else if (i % 10 == 0 && i != 10 && i < 60 && i > 0) printf("\xCA");
		else printf("\xCD");
	}

	//*** Vertical lines. ***

	GotoXY(0, 2);
	for (i = 0; i != 80; i++) 
	{
		if (i % 10 == 0 && i < 60 && i > 0) printf("\xBA");
		else printf("\x20");
	}
	GotoXY(0, 4);
	for (i = 0; i != 80; i++) 
	{
		if (i % 10 == 0 && i < 60 && i > 0) printf("\xBA");
		else printf("\x20");
	}
	GotoXY(0, 5);
	for (i = 0; i != 80; i++) 
	{
		if (i % 10 == 0 && i < 60 && i > 0) printf("\xBA");
		else printf("\x20");
	}
	GotoXY(0, 6);
	for (i = 0; i != 80; i++) 
	{
		if (i % 10 == 0 && i < 60 && i > 0) printf("\xBA");
		else printf("\x20");
	}

	//*** Vertical Field. ***
	
	GotoXY(0, 8);
	int num = uf->Height() + 4;
	for (i = 0; i != num; i++) 
	{
		for (int j = 0; j != 11; j++) 
		{
			if (j % 10 == 0 && j > 0) printf("\xBA");
			else printf("\x20");
		}
		printf("\n");
	}

	//*** Downer line. ***

	GotoXY(0, num + 8);
	for (i = 0; i != 80; i++) 
	{
		if (i == 10) printf("\xCA");
		else printf("\xCD");
	}

	//*** Inner composition. ***
	
	GotoXY(2, 2);
	printf("STATS");
	GotoXY(2, 4);
	printf("PLAYER");
	GotoXY(4, 6);
	printf("AI");
	GotoXY(2, 8);
	printf("TURN:");
	GotoXY(2, 10);
	printf("State:");
	GotoXY(2, 12);
	printf("Length:");
	GotoXY(2, 14);
	printf("Dir.:");

	//...
	GotoXY(15, 2);
	printf("1");				//***  4-Ship count. ***
	GotoXY(25, 2);
	printf("2");				//***  3-Ship count. ***
	GotoXY(35, 2);
	printf("3");				//***  2-Ship count. ***
	GotoXY(45, 2);
	printf("4");				//***  1-Ship count. ***
	//...

	GotoXY(0, num + 9);
	for (i = 0; i != 80; i++) for (int j = 0; j != 30; j++) printf("\x20");
	GotoXY(20, num + 9);
	printf("#The Rules to play  the Seaker game#");
	GotoXY(0, num + 10);
	printf("1> The movement keys: 'w'(~up), 's'(~down), 'a'(~left), 'd'(~right).");
	GotoXY(0, num + 11);
	printf("2> To place a ship use a spacebar key.");
	GotoXY(0, num + 12);
	printf("3> To choose a ship's length use the numeric keys (1--4).");
	GotoXY(0, num + 13);
	printf("4> To shoot at the field use the key 'f'.");
	GotoXY(0, num + 14);
	printf("5> To exit the game use the 'x' key.");
	GotoXY(0, num + 15);
	printf("6> Created and designed by Alexander Boldyrev, 2015.");
	GotoXY(0, num + 16);
	printf("P.S. 7> Don't look into my source code! (Nothing interesting, but harmful).");
}

void CUI::PrintIn()
{

}

void CUI::InitFields()
{

}

void CUI::InitAI()
{

}

void CUI::UpdateFields()
{

}

void CUI::StartGame()
{

}

void CUI::EndGame()
{

}

void CUI::ChangeTurnState(bool who)
{
	switch (who)
	{
	case (1) :
		GotoXY(2, 9);
		PrintCol("Player  ");
		break;
	case (0) :
		GotoXY(2, 9);
		PrintCol("Computer");
		break;
	}
}

void CUI::ChangeState()
{
	GotoXY(2, 11);
	PrintCol("Game ");
}

void CUI::ChangeSet()
{
	GotoXY(2, 11);
	PrintCol("Set.  ");
}

void CUI::ChangeState(char* st)
{
	GotoXY(2, 11);
	PrintCol(st);
}

/*void CUI::ChangeShipState(bool who, units shiplen)
{
	switch (who)
	{
	case (1) :
		switch (shiplen)
		{
		case (4) :						//***  4-Ship count. ***	
			GotoXY(15, 4);
			PrintCol("\xDB");
			break;
		case (3) :						//***  3-Ship count. ***
			GotoXY(25, 4);
			PrintCol("\xDB");
			break;
		case (2) :						//***  2-Ship count. ***
			GotoXY(35, 4);
			PrintCol("\xDB");
			break;
		case (1) :						//***  1-Ship count. ***
			GotoXY(45, 4);
			PrintCol("\xDB");
			break;
		}
		break;
	case (0) :
		switch (shiplen)
		{
		case (4) :						//***  4-Ship count. ***	
			GotoXY(15, 6);
			PrintCol("\xDB");
			break;
		case (3) :						//***  3-Ship count. ***
			GotoXY(25, 6);
			PrintCol("\xDB");
			break;
		case (2) :						//***  2-Ship count. ***
			GotoXY(35, 6);
			PrintCol("\xDB");
			break;
		case (1) :						//***  1-Ship count. ***
			GotoXY(45, 6);
			PrintCol("\xDB");
			break;
		}
		break;
	}
}*/

void CUI::AddShipState(bool who, units shiplen, units s)
{
	units shift;
	if (who == PLAYER) shift = 0;
	else shift = 2;
	switch (who)
	{
	case(PLAYER) :
		switch (shiplen)
		{
		case (4) :						//***  4-Ship count. ***
			GotoXY(s + *c4 + 5, 4 + shift);
			PrintSCol("\xDB");
			break;
		case (3) :						//***  3-Ship count. ***
			*c3 += 2;
			GotoXY(s + *c3 + 2, 4 + shift);
			PrintSCol("\xDB");
			break;
		case (2) :						//***  2-Ship count. ***
			*c2 += 2;
			GotoXY(s + *c2 + 1, 4 + shift);
			PrintSCol("\xDB");
			break;
		case (1) :						//***  1-Ship count. ***
			*c1 += 2;
			GotoXY(s + *c1, 4 + shift);
			PrintSCol("\xDB");
			break;
		}
		break;
	
	case (COMP) :
		switch (shiplen)
		{
		case (4) :						//***  4-Ship count. ***
			GotoXY(s + *d4 + 5, 4 + shift);
			PrintSCol("\xDB");
			break;
		case (3) :						//***  3-Ship count. ***
			*d3 += 2;
			GotoXY(s + *d3 + 2, 4 + shift);
			PrintSCol("\xDB");
			break;
		case (2) :						//***  2-Ship count. ***
			*d2 += 2;
			GotoXY(s + *d2 + 1, 4 + shift);
			PrintSCol("\xDB");
			break;
		case (1) :						//***  1-Ship count. ***
			*d1 += 2;
			GotoXY(s + *d1, 4 + shift);
			PrintSCol("\xDB");
			break;
		}
		break;
	}
}

void CUI::RemShipState(bool who, units shiplen, units s)
{
	units shift = 2;
	switch (who)
	{
	case (PLAYER) :
		switch (shiplen)
		{
		case (4) :						//***  4-Ship count. ***
			GotoXY(s + *l4 + 5, 4);
			PrintCol("\xDB");
			break;
		case (3) :						//***  3-Ship count. ***
			*l3 += 2;
			GotoXY(s + *l3 + 2, 4);
			PrintCol("\xDB");
			break;
		case (2) :						//***  2-Ship count. ***
			*l2 += 2;
			GotoXY(s + *l2 + 1, 4);
			PrintCol("\xDB");
			break;
		case (1) :						//***  1-Ship count. ***
			*l1 += 2;
			GotoXY(s + *l1, 4);
			PrintCol("\xDB");
			break;
		}
		break;
	case (COMP) :
		switch (shiplen)
		{
		case (4) :						//***  4-Ship count. ***
			GotoXY(s + *k4 + 5, 4 + shift);
			PrintCol("\xDB");
			break;
		case (3) :						//***  3-Ship count. ***
			*k3 += 2;
			GotoXY(s + *k3 + 2, 4 + shift);
			PrintCol("\xDB");
			break;
		case (2) :						//***  2-Ship count. ***
			*k2 += 2;
			GotoXY(s + *k2 + 1, 4 + shift);
			PrintCol("\xDB");
			break;
		case (1) :						//***  1-Ship count. ***
			*k1 += 2;
			GotoXY(s + *k1, 4 + shift);
			PrintCol("\xDB");
			break;
		}
		break;
	}
}	

void CUI::PrintCol(char* str)
{
	SetColor(claim, clbframe);
	printf("%s", str);
	SetColor(cldef, clbdef);
}

void CUI::PrintSCol(char* str)
{
	SetColor(clframe, clbframe);
	printf("%s", str);
	SetColor(cldef, clbdef);
}

void CUI::ChangeLen(units len)
{
	GotoXY(2, 13);
	SetColor(claim, clbframe);
	printf("%d", len);
	SetColor(cldef, clbdef);
}

void CUI::ChangeDir(char dir)
{
	GotoXY(2, 15);
	SetColor(claim, clbframe);
	printf("%c", dir);
	SetColor(cldef, clbdef);
}

void CUI::PaintHM(bool mh, bool who, Field* fuf)
{
	switch (mh)				//*** 1 ~ hit, 0 ~ miss. ***
	{
	case (1) :
		if (who == PLAYER) GotoXY(fuf->posx + x + 1, fuf->posy + y + 1);
		else GotoXY(fuf->posx + x + fuf->Width() + 2, fuf->posy + y + 1);
		SetColor(Yellow, LightBlue);
		printf("%c", fuf->hit);
		SetColor(White, Black);
		break;
	case (0) :
		if (who == PLAYER) GotoXY(fuf->posx + x + 1, fuf->posy + y + 1);
		else GotoXY(fuf->posx + x + fuf->Width() + 2, fuf->posy + y + 1);
		SetColor(LightCyan, LightBlue);
		printf("%c", fuf->miss);
		SetColor(White, Black);
		break;
	}
}
