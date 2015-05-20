#ifndef _CUI_H
#define _CUI_H

#include <windows.h>
#include <stdio.h>

#include "Field.h"
#include "Types.h"

class CUI
{
public:
	void		 GotoXY			(int X, int Y);
	void		 SetColor		(short textcolor, short bgcolor);
	
	void		 SetCursor		(Field* f, unsigned short fx, unsigned short fy);
	void		 SetAim			(Field* f);
	void		 MoveAim		(dir where, Field* f, bool who);
	void	     Draw			(Field* f);
	void		 WriteDot		(Field* fuf);

	void		 PrintFrame		();
	void		 PrintWin		(Field* uf);
	void		 PrintIn		();
	void 		 PrintField		(Field* f);
	void		 PrintGame		(Field* cf, Field* uf);
	void		 AddShipState	(bool who, units shiplen, units s);
	void		 RemShipState	(bool who, units shiplen, units s);
	//void		 ChangeShipState(bool who, units shiplen);
	void		 ChangeTurnState(bool who);
	void		 ChangeState	();
	void		 ChangeState	(char* st);
	void		 ChangeSet		();
	void		 PrintCol		(char* str);
	void		 PrintSCol		(char* str);
	void		 ChangeLen		(units len);
	void		 ChangeDir		(char  dir);
	void		 PaintHM		(bool mh, bool who, Field* fuf);


	void 		 InitFields		();
	void 		 InitAI			();
	void 		 UpdateFields	();
	void 		 StartGame		();
	void 		 EndGame		();

				 CUI			(units w, units h);
				 ~CUI			();

	units	 	 x = 0,			y = 9;

	short*		 c1;			
	short*		 c2;			
	short*		 c3;				
	short*		 c4;			

	short*		 k1;		
	short*		 k2;		
	short*		 k3;		
	short*		 k4;			

	short*		 l1;				
	short*		 l2;				
	short*		 l3;				
	short*		 l4;				

	short*		 d1;				
	short*		 d2;				
	short*		 d3;				
	short*		 d4;

	const short  Black			= 0x00,
				 Blue			= 0x01,
				 Green			= 0x02,
				 Cyan			= 0x03,
				 Red			= 0x04,
				 Magenta		= 0x05,
				 Brown			= 0x06,
				 LightGray		= 0x07,
				 DarkGray		= 0x08,
				 LightBlue		= 0x09,
				 LightGreen		= 0x0A,
				 LightCyan		= 0x0B,
				 LightRed		= 0x0C,
				 LightMag		= 0x0D,
				 Yellow			= 0x0E,
				 White			= 0x0F;

	const short  clwater		= LightBlue;
	const short  clmiss			= LightCyan;
	const short  clship			= DarkGray;
	const short  claim			= LightRed;
	const short  clhit			= Yellow;
	const short  clback			= LightBlue;
	const short  clframe		= LightCyan;
	const short  clbframe		= Cyan;
	const short  cldef			= White;
	const short  clbdef			= Black;

private:

	units		 _w,			_h;

};

#endif
