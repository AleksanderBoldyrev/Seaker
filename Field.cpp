#include "Field.h"

Field::Field(bool who, units sx, units sy)
{
	owner = who;
	posx = 0;
	posy = 0;
	wc = sx;
	wcells = sx;
	hc = sy;
	hcells = sy;
	cells.resize(sx);
	for (int w = 0; w < sx; w++) cells[w].resize(sy);
	for (int w = 0; w < sx; w++) for (int h = 0; h < sy; h++) cells[w][h] = water;
}

Field::~Field()
{
	for (int w = 0; w < wc; w++)
		cells[w].erase(cells[w].begin(), cells[w].end());
	cells.erase(cells.begin(), cells.end());
	//cout << "Here thy Field is destroyed!...\n";
}

void Field::Wipe()
{
	for (units i = 0; i < wc; i++) for (units j = 0; j < hc; j++) cells[i][j] = water;
}

cstate Field::GetCell(units w, units h)
{
	if (w < 0 || w >= wc || h < 0 || h >= hc) return err;
	else return cells[w][h];
}

void Field::SetCell(units w, units h, cstate s)
{
	cells[w][h] = s;
}

bool Field::SetPos(units x, units y)
{
	if (y < 0 || y >= hc || x < 0 || x >= wc) return false;
	posx = x;
	posy = y;
	return true;
}

cstate Field::GetPosVal()
{
	return cells[posx][posy];
}

bool Field::CreateShip(units x, units y, units l, dir vdir)
{
	bool isplaced = false;
	short it = 0;
	if (ShipSpaceIsChecked(x, y, l, vdir))
		{
		if (l == 1)
		{
			SetCell(x, y, onesh);
			isplaced = true;
			return isplaced;
		}
		isplaced = true;
		switch (vdir)
		{
		case ('h') :
			SetCell(x, y, left);
			for (short le = 1; le <= l - 1; le++) { SetCell(x + le, y, body); it++; }
			SetCell(x + it, y, right);
			break;
		case ('v') :
			SetCell(x, y, up);
			for (short le = 1; le <= l - 1; le++) { SetCell(x, y + le, body); it++; }
			SetCell(x, y + it, down);
			break;
		default:
			printf("Unknown symbol!");
			break;
		}
	}
	return isplaced;
}

bool Field::CenterCellSpaceIsChecked(units cellx, units celly, units le, dir di, units ord)
{
	bool b = true;
	switch (di)
	{
	case ('h') :
		if (ord == 1)
		{
			if ((this->GetCell(cellx, celly - 1) != water && this->GetCell(cellx, celly - 1) != err) || (this->GetCell(cellx, celly + 1) != water && this->GetCell(cellx, celly + 1) != err) || (this->GetCell(cellx - 1, celly) != water && this->GetCell(cellx - 1, celly) != err) || (this->GetCell(cellx - 1, celly - 1) != water && this->GetCell(cellx - 1, celly - 1) != err) || (this->GetCell(cellx - 1, celly + 1) != water && this->GetCell(cellx - 1, celly + 1) != err) || (this->GetCell(cellx, celly) != water && this->GetCell(cellx, celly) != err))
			{
				b = false;
				goto e;
			}
			break;
		}
		if (ord == le)
		{
			if ((this->GetCell(cellx, celly - 1) != water && this->GetCell(cellx, celly - 1) != err) || (this->GetCell(cellx, celly + 1) != water && this->GetCell(cellx, celly + 1) != err) || (this->GetCell(cellx + 1, celly) != water && this->GetCell(cellx + 1, celly) != err) || (this->GetCell(cellx + 1, celly - 1) != water && this->GetCell(cellx + 1, celly - 1) != err) || (this->GetCell(cellx + 1, celly + 1) != water && this->GetCell(cellx + 1, celly + 1) != err) || (this->GetCell(cellx, celly) != water && this->GetCell(cellx, celly) != err))
			{
				b = false;
				goto e;
			}
			break;
		}
		else if ((this->GetCell(cellx, celly - 1) != water && this->GetCell(cellx, celly - 1) != err) || (this->GetCell(cellx, celly + 1) != water && this->GetCell(cellx, celly + 1) != err) || (this->GetCell(cellx, celly) != water && this->GetCell(cellx, celly) != err) || (this->GetCell(cellx, celly) != water && this->GetCell(cellx, celly) != err))
		{
			b = false;
			goto e;
		}
		break;
	case ('v') :
		if (ord == 1)
		{
			if ((this->GetCell(cellx, celly - 1) != water && this->GetCell(cellx, celly - 1) != err) || (this->GetCell(cellx + 1, celly) != water && this->GetCell(cellx + 1, celly) != err) || (this->GetCell(cellx - 1, celly) != water && this->GetCell(cellx - 1, celly) != err) || (this->GetCell(cellx - 1, celly - 1) != water && this->GetCell(cellx - 1, celly - 1) != err) || (this->GetCell(cellx + 1, celly - 1) != water && this->GetCell(cellx + 1, celly - 1) != err) || (this->GetCell(cellx, celly) != water && this->GetCell(cellx, celly) != err))
			{
				b = false;
				goto e;
			}
			break;
		}
		if (ord == le)
		{
			if ((this->GetCell(cellx, celly + 1) != water && this->GetCell(cellx, celly + 1) != err) || (this->GetCell(cellx + 1, celly) != water && this->GetCell(cellx + 1, celly) != err) || (this->GetCell(cellx - 1, celly) != water && this->GetCell(cellx - 1, celly) != err) || (this->GetCell(cellx - 1, celly + 1) != water && this->GetCell(cellx - 1, celly + 1) != err) || (this->GetCell(cellx + 1, celly + 1) != water && this->GetCell(cellx + 1, celly + 1) != err) || (this->GetCell(cellx, celly) != water && this->GetCell(cellx, celly) != err))
			{
				b = false;
				goto e;
			}
			break;
		}
		else if ((this->GetCell(cellx - 1, celly) != water && this->GetCell(cellx - 1, celly) != err) || (this->GetCell(cellx + 1, celly) != water && this->GetCell(cellx + 1, celly) != err) || (this->GetCell(cellx, celly) != water && this->GetCell(cellx, celly) != err))
		{
			b = false;
			goto e;
		}
		break;
	}
	e: return b;
}

bool Field::ShipSpaceIsChecked(units x, units y, units l, dir vdir)
{
	bool b = true;
	unsigned short order = 1;
	units vx = x, vy = y;
	if (l == 1)
	{
		if ((this->GetCell(x, y + 1) != water && this->GetCell(x, y + 1) != err) || (this->GetCell(x + 1, y) != water && this->GetCell(x + 1, y) != err) || (this->GetCell(x - 1, y) != water && this->GetCell(x - 1, y) != err) || (this->GetCell(x, y - 1) != water && this->GetCell(x, y - 1) != err) || (this->GetCell(x + 1, y + 1) != water && this->GetCell(x + 1, y + 1) != err) || (this->GetCell(x + 1, y - 1) != water && this->GetCell(x + 1, y - 1) != err) || (this->GetCell(x - 1, y + 1) != water && this->GetCell(x - 1, y + 1) != err) || (this->GetCell(x - 1, y - 1) != water && this->GetCell(x - 1, y - 1) != err) || (this->GetCell(x, y) != water && this->GetCell(x, y) != err))
		{
			b = false;
			goto ex;
		}
	}
	switch (vdir)
	{
	case ('h') :
		for (vx; vx <= l - 1 + x; vx++)
		{
			if (!this->CenterCellSpaceIsChecked(vx, vy, l, vdir, order))
			{
				b = false;
				goto ex;
			}
			order++;
		}
	    break;
	case ('v') :
		for (vy; vy <= l - 1 + y; vy++)
		{
			if (!CenterCellSpaceIsChecked(vx, vy, l, vdir, order))
			{
				b = false;
				goto ex;
			}
			order++;
		}
		break;
	}
ex:	return b;
}

void Field::Fire(units px, units py)
{
	this->SetCell(px, py, this->hit);
}

void Field::Miss(units px, units py)
{
	this->SetCell(px, py, this->miss);
}
