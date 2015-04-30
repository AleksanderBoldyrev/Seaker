#include "CUI.h"

HANDLE hConsole;
HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);

CUI::CUI(units w, units h)
{
	_w = w;
	_h = h;
}

CUI::~CUI()
{

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

void CUI::Draw(Field& f)					//Verpa et feces caninae sunt!
{
	cstate st = f.GetPosVal();
	if (st == f.up || st == f.down || st == f.left || st == f.right || st == f.onesh || st == f.body || st == f.water)
	{
		SetColor(clship, clback);
		if (f.owner == COMP) printf("%c", f.water);
		else printf("%c", st);
	}
	if (st == f.miss || st == f.hit)
	{
		if (st == f.miss) SetColor(clmiss, clback);
		else SetColor(clhit, clback);
		printf("%c", st);
	}
	SetColor(cldef, clbdef);
}

void CUI::SetCursor(Field& f, unsigned short fx, unsigned short fy)
{
	GotoXY(fx, fy);		//insert design-oriented componentz
	//...............................................................................
}

void CUI::SetAim(Field& f)
{
	SetColor(claim, clback);
	printf("%c", '+');
	SetColor(cldef, clbdef);
}

void CUI::MoveAim(dir where, Field& f, bool who)
{
	switch (where)
	{
	case ('u') :
		if (f.posy == 0) break;
		if (who == PLAYER) GotoXY(f.posx + x + 1, f.posy + y + 1);
		if (who == COMP)   GotoXY(f.posx + x + f.Width() + 2, f.posy + y + 1);
		Draw(f);
		SetColor(claim, clback);
		f.SetPos(f.posx, --f.posy);
		if (who == PLAYER) GotoXY(f.posx + x + 1, f.posy + y + 1);
		if (who == COMP)   GotoXY(f.posx + x + f.Width() + 2, f.posy + y + 1);
		printf("%c", '+');
		break;
	case ('d') :
		if (f.posy == f.Height() - 1) break;
		if (who == PLAYER) GotoXY(f.posx + x + 1, f.posy + y + 1);
		if (who == COMP)   GotoXY(f.posx + x + f.Width() + 2, f.posy + y + 1);
		Draw(f);
		SetColor(claim, clback);
		f.SetPos(f.posx, ++f.posy);
		if (who == PLAYER) GotoXY(f.posx + x + 1, f.posy + y + 1);
		if (who == COMP)   GotoXY(f.posx + x + f.Width() + 2, f.posy + y + 1);
		printf("%c", '+');
		break;
	case ('l') :
		if (f.posx == 0) break;
		if (who == PLAYER) GotoXY(f.posx + x + 1, f.posy + y + 1);
		if (who == COMP)   GotoXY(f.posx + x + f.Width() + 2, f.posy + y + 1);
		Draw(f);
		SetColor(claim, clback);
		f.SetPos(--f.posx, f.posy);
		if (who == PLAYER) GotoXY(f.posx + x + 1, f.posy + y + 1);
		if (who == COMP)   GotoXY(f.posx + x + f.Width() + 2, f.posy + y + 1);
		printf("%c", '+');
		break;
	case ('r') :
		if (f.posx == f.Width() - 1) break;
		if (who == PLAYER) GotoXY(f.posx + x + 1, f.posy + y + 1);
		if (who == COMP)   GotoXY(f.posx + x + f.Width() + 2, f.posy + y + 1);
		Draw(f);
		SetColor(claim, clback);
		f.SetPos(++f.posx, f.posy);
		if (who == PLAYER) GotoXY(f.posx + x + 1, f.posy + y + 1);
		if (who == COMP)   GotoXY(f.posx + x + f.Width() + 2, f.posy + y + 1);
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
		ix++;
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

void CUI::PrintField(Field& f)
{
	int xx;
	if (f.owner == PLAYER) xx = 1 + x;
	else xx = 2 + _w + x;
	units fx = 0, fy = 0;
	for (int h = y + 1; h != _h + y + 1; h++) for (int w = xx; w != _w + xx; w++)
	{
		GotoXY(w, h);
		fx = w - xx;
		fy = h - y - 1;
		f.SetPos(fx, fy);
		SetColor(clship, clback);
		printf("%c", (char)f.GetPosVal());
	}
	GotoXY(x, y + _h + 3);
	SetColor(cldef, clbdef);
}

void CUI::PrintGame(Field& cf, Field& uf)
{
	system("cls");
	this->PrintWin();
	this->PrintFrame();
	this->PrintField(uf);
	this->PrintField(cf);
}

void CUI::PrintWin()
{
	int i;
	SetColor(clframe, clbframe);
	GotoXY(0, 0);
	for (i = 0; i != 37; i++) printf("%c", 0x20);
	printf("SEAKER");
	for (i = 0; i != 37; i++) printf("%c", 0x20);
	GotoXY(0, 1);
	for (i = 0; i != 80; i++) printf("%c", 0xC4);
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

