#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "CBDiamond.h"
#include <windows.h>
namespace game_framework {
	CBDiamond::CBDiamond()
	{
		Initialize();
	}
	int CBDiamond::GetX1()
	{
		return x1;
	}
	int CBDiamond::GetY1()
	{
		return y1;
	}
	int CBDiamond::GetX2()
	{
		x2 = x1 + Diamond.Width();
		return x2;
	}
	int CBDiamond::GetY2()
	{
		y2 = y1 + Diamond.Height();
		return y2;
	}
	void  CBDiamond::SetIsExist(bool n) {
		isExist = n;
	}
	int CBDiamond::GetExist() {
		return isExist;
	}
	void CBDiamond::Initialize()
	{
		LoadBitmap();
		isExist = 1;
	}
	void CBDiamond::SetXY(int nx, int ny)
	{
		x1 = nx; y1 = ny;
	}
	void CBDiamond::LoadBitmap()
	{
		Diamond.LoadBitmap(IDB_BD, RGB(255, 255, 255));
	}
	void CBDiamond::OnShow()
	{
		Diamond.SetTopLeft(x1, y1);
		if (isExist) {
			Diamond.ShowBitmap();
		}
		else {
		}
	}
}

