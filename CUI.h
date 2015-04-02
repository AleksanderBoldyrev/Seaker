#ifndef _CUI_H
#define _CUI_H

#include <windows.h>
#include <stdio.h>

#include "Field.h"
#include "Types.h"

class CUI
{
public:
	void		GotoXY(int X, int Y);
	void		SetColor(short textcolor, short bgcolor);
	
	void		SetCursor(Field& f, unsigned short fx, unsigned short fy);
	void		SetAim(Field& f);
	void		MoveAim(dir where, Field& f, bool who);
	void		Draw(Field& f);
	void		Fire(units px, units py, bool who);
	void		Miss(units px, units py, bool who);


	void		PrintFrame();
	void 		PrintField(Field& f);
	void		PrintGame(Field& cf, Field& uf);

			CUI(units w, units h);
			~CUI();
			
	units		x = 10, y = 10;

	const short	Black = 0x00,
			Blue = 0x01,
			Green = 0x02,
			Cyan = 0x03,
			Red = 0x04,
			Magenta = 0x05,
			Brown = 0x06,
			LightGray = 0x07,
			DarkGray = 0x08,
			LightBlue = 0x09,
			LightGreen = 0x0A,
			LightCyan = 0x0B,
			LightRed = 0x0C,
			LightMag = 0x0D,
			Yellow = 0x0E,
			White = 0x0F;
private:

	units		_w, _h;

};

#endif
