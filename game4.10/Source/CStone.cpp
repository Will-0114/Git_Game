#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "CStone.h"
#include <windows.h>
#define vx 260
#define vy 500
#define time 1.0/60
#define ax 550
#define ay 1200


namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// CEraser: Eraser class
	/////////////////////////////////////////////////////////////////////////////

	CStone::CStone()
	{
		Initialize();
	}
	bool CStone::HitRightWall(int tx1, int ty1, int tx2, int ty2)
	{
		x2 = x1 + animation.Width();
		y2 = y1 + animation.Height();
		return ((x1 < tx2) && (tx1 < x2) && (y1 > ty1) && (y2 < ty2));
	}
	bool CStone::HitLeftWall(int tx1, int ty1, int tx2, int ty2)
	{
		x2 = x1 + animation.Width();
		y2 = y1 + animation.Height();
		return ((x1 > tx1) && (tx2 > x2) && (y2 > ty1) && (ty2 > y1));
	}
	bool CStone::StandFloor(int tx1, int ty1, int tx2, int ty2) {

		x2 = x1 + animation.Width();
		y2 = y1 + animation.Height();
		return((tx1 < x1) && (tx2 > x2) && (ty1 < y2) && (ty2 > y1));
	}
	void CStone::SetWall(bool wall)
	{
		isWall = wall;
	}
	bool CStone::HitCeiling(int tx1, int ty1, int tx2, int ty2) {
		x2 = x1 + animation.Width();
		y2 = y1 + animation.Height();
		return((tx1 < x1) && (tx2 > x2) && (y1 < ty2) && (ty1 < y1));
	}
	int CStone::GetX1()
	{
		return x1;
	}
	int CStone::GetY1()
	{
		return y1;
	}
	int CStone::GetX2()
	{
		x2 = x1 + animation.Width();
		return x2;
	}
	int CStone::GetY2()
	{
		y2 = y1 + animation.Height();
		return y2;
	}
	void CStone::Initialize()
	{

		const int X_POS = 100;
		const int Y_POS = 300;
		x1 = X_POS;
		y1 = Y_POS;
		k = 0;
		isWall = isStand = false;
	}
	void CStone::OnFloor() {
		if (isStand == false) {
			y1 += 10;
		}
		animation.OnShow();
	}
	void CStone::SetIsStand(bool stand)
	{
		isStand = stand;
	}
	void CStone::LoadBitmap()
	{
		animation.AddBitmap(IDB_STONE,RGB(255,255,255));
	}
	void CStone::OnMove()
	{
	}
	void CStone::SetXY(int nx, int ny)
	{
		x1 = nx; y1 = ny;
	}
	void CStone::OnShow()
	{
		animation.SetTopLeft(x1, y1 + 24 - animation.Height());
		animation.OnShow();
	}
}