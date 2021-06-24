#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "CRDiamond.h"
#include <windows.h>
namespace game_framework {
	CRDiamond::CRDiamond()
	{
		Initialize();
	}
	int CRDiamond::GetX1()
	{
		return x1;
	}
	int CRDiamond::GetY1()
	{
		return y1;
	}
	int CRDiamond::GetX2()
	{
		x2 = x1 + Diamond.Width();
		return x2;
	}
	int CRDiamond::GetY2()
	{
		y2 = y1 + Diamond.Height();
		return y2;
	}
	int CRDiamond::GetExist() {
		return isExist;
	}
	void  CRDiamond::SetIsExist(bool n) {
		isExist = n;
	}
	void CRDiamond::Initialize()
	{
		LoadBitmap();
		isExist = 1;
	}
	void CRDiamond::SetXY(int nx, int ny)
	{
		x1 = nx; y1 = ny;
		
	}
	void CRDiamond::LoadBitmap()
	{
		Diamond.LoadBitmap(IDB_RD, RGB(255, 255, 255));
	}
	void CRDiamond::OnShow()
	{
		Diamond.SetTopLeft(x1, y1);
		if (isExist) {
			Diamond.ShowBitmap();
		}
		else {
		}
	}
}

