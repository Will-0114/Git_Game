#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "CPlayer.h"
#include <windows.h>
#define vx 260
#define vy 500
#define time 1.0/60
#define ax 550
#define ay 1200
namespace game_framework {
	CPlayer::CPlayer()
	{
		Initialize();
	}
	bool CPlayer::HitBDiamond(CBDiamond  BDiamond)
	{
		x2 = x1 + animation.Width();
		y2 = y1 + animation.Height();
		
		return ( x2 > BDiamond.GetX1() &&  BDiamond.GetX2() > x1 && y2 > BDiamond.GetY1() && BDiamond.GetY2() > y1);
	}
	bool CPlayer::HitRDiamond(CRDiamond  RDiamond)
	{
		x2 = x1 + animation.Width();
		y2 = y1 + animation.Height();

		return (x2 > RDiamond.GetX1() && RDiamond.GetX2() > x1 && y2 > RDiamond.GetY1() && RDiamond.GetY2() > y1);
	}
	bool CPlayer::HitRightWall(int tx1, int ty1, int tx2, int ty2)
	{
		x2 = x1 + animation.Width();
		y2 = y1 + animation.Height();
		return ((x1 < tx2) && (tx1 < x2) && (y1 > ty1) && (y2 < ty2));
	} 
	bool CPlayer::HitLeftWall(int tx1, int ty1, int tx2, int ty2)
	{
		x2 = x1 + animation.Width();
		y2 = y1 + animation.Height();

		return ((x1 > tx1) && (tx2 > x2) && (y2 > ty1) && (ty2 > y1));
	}
	bool CPlayer::StandFloor(int tx1, int ty1, int tx2, int ty2) {
		
		x2 = x1 + animation.Width();
		y2 = y1 + animation.Height();
		return((tx1 < x1) && (tx2 > x2) && (ty1 < y2) && (ty2 > y1));
	}
	int CPlayer::GetState() {
		int state=0;
		if (isMovingLeft) {
			state = 3;
		}
		else if (isMovingRight) {
			state = 2;
		}
		return state;
	}
	void CPlayer::SetWall(bool wall)
	{
		isWall = wall;
	}
	bool CPlayer::HitCeiling(int tx1, int ty1, int tx2, int ty2) {

		x2 = x1 + animation.Width();
		y2 = y1 + animation.Height();
		
		return((tx1 < x1) && (tx2 > x2) && (y1 < ty2) && (ty1 < y1));
	}
	int CPlayer::GetX1()
	{
		return x1;
	}
	int CPlayer::GetY1()
	{
		return y1;
	}
	int CPlayer::GetX2()
	{
		x2 = x1 + animation.Width();
		return x2;
	}
	int CPlayer::GetY2()
	{
		y2 = y1 + animation.Height();
		return y2;
	}
	void CPlayer::Setplayer(int a) {
		if (a == 1) {
			isplayer = 1;
		}
		else {
			isplayer = 0;
		}
	}
	void CPlayer::Initialize()
	{
		const int X_POS = 100;
		const int Y_POS = 300;
		x1 = X_POS;
		y1 = Y_POS;
		a = 375;
		k = 0;
		isMovingLeft = isMovingRight = isMovingUp = isMovingDown = false;
		isWall = isStand = isJump = false;
	}
	void CPlayer::OnFloor() {
		if (isStand == false) {
			y1 += 10;
		}
		animation.OnShow();
	}
	void CPlayer::SetIsStand(bool stand)
	{
		isStand = stand;
	}
	void CPlayer::SetIsJump(bool jump) {
		isJump = jump;
	}
	void CPlayer::SetFloor(int _floor) {
		floor = _floor;
	}
	bool CPlayer::GetJumpState() {
		return isJump;
	}
	void CPlayer::LoadBitmap()
	{
		if (isplayer) {
			animation.AddBitmap(IDB_RED, RGB(255, 255, 255));
			animation.AddBitmap(IDB_REDDOWN, RGB(255, 255, 255));
			animation.AddBitmap(IDB_REDJUMP, RGB(255, 255, 255));
			animation.AddBitmap(IDB_REDRUN1, RGB(255, 255, 255));
			animation.AddBitmap(IDB_REDRUN2, RGB(255, 255, 255));
			animation.AddBitmap(IDB_REDRUN3, RGB(255, 255, 255));
			animation.AddBitmap(IDB_REDRUN4, RGB(255, 255, 255));
			animation.AddBitmap(IDB_REDRUN5, RGB(255, 255, 255));
			animation.AddBitmap(IDB_REDRUN6, RGB(255, 255, 255));
			animation.AddBitmap(IDB_REDRUN7, RGB(255, 255, 255));
			animation.AddBitmap(IDB_REDLRUN1, RGB(255, 255, 255));
			animation.AddBitmap(IDB_REDLRUN2, RGB(255, 255, 255));
			animation.AddBitmap(IDB_REDLRUN3, RGB(255, 255, 255));
			animation.AddBitmap(IDB_REDLRUN4, RGB(255, 255, 255));
			animation.AddBitmap(IDB_REDLRUN5, RGB(255, 255, 255));
			animation.AddBitmap(IDB_REDLRUN6, RGB(255, 255, 255));
			animation.AddBitmap(IDB_REDLRUN7, RGB(255, 255, 255));
		}
		else {
			animation.AddBitmap(IDB_BLUE, RGB(255, 255, 255));
			animation.AddBitmap(IDB_BLUEDOWN, RGB(255, 255, 255));
			animation.AddBitmap(IDB_BLUEJUMP, RGB(255, 255, 255));
			animation.AddBitmap(IDB_BLUERUN1, RGB(255, 255, 255));
			animation.AddBitmap(IDB_BLUERUN2, RGB(255, 255, 255));
			animation.AddBitmap(IDB_BLUERUN3, RGB(255, 255, 255));
			animation.AddBitmap(IDB_BLUERUN4, RGB(255, 255, 255));
			animation.AddBitmap(IDB_BLUERUN5, RGB(255, 255, 255));
			animation.AddBitmap(IDB_BLUERUN6, RGB(255, 255, 255));
			animation.AddBitmap(IDB_BLUERUN7, RGB(255, 255, 255));
			animation.AddBitmap(IDB_BLUELRUN1, RGB(255, 255, 255));
			animation.AddBitmap(IDB_BLUELRUN2, RGB(255, 255, 255));
			animation.AddBitmap(IDB_BLUELRUN3, RGB(255, 255, 255));
			animation.AddBitmap(IDB_BLUELRUN4, RGB(255, 255, 255));
			animation.AddBitmap(IDB_BLUELRUN5, RGB(255, 255, 255));
			animation.AddBitmap(IDB_BLUELRUN6, RGB(255, 255, 255));
			animation.AddBitmap(IDB_BLUELRUN7, RGB(255, 255, 255));
		}
	}
	void CPlayer::Seta(int na) {
		a = na;
	}
	void CPlayer::OnMove()
	{
		const int a = 2;
		int V = 0;
		V += a * 1;
		int STEP_SIZE = 2;
		animation.OnMove();
		if (isStand) {
			if (!(animation.GetCurrentBitmapNumber() == 0)) animation.Movetonum(0);
			STEP_SIZE = vx / 25 - int(time * ax / 100);
		}
		else{
			if (!(animation.GetCurrentBitmapNumber() == 0)) animation.Movetonum(1);
			STEP_SIZE = vx / 25 + int(time * ax / 100);
		}
		if (isMovingLeft) {
			if (!(animation.GetCurrentBitmapNumber() > 9 && animation.GetCurrentBitmapNumber() < 17))
			{
				animation.Movetonum(10+k);
				k++;
				if (k > 6) {
					k = 0;
				};
			}
			if(!isWall) x1 -= STEP_SIZE;
		}
		if (isMovingRight){
			if (!(animation.GetCurrentBitmapNumber() > 2 && animation.GetCurrentBitmapNumber() < 10)) {
				animation.Movetonum(3+k);
				k++;
				if (k > 6) {
					k = 0;
				};
			}
			if (!isWall) x1 += STEP_SIZE;
		}
		if (isMovingUp && isStand) {
			if (!(animation.GetCurrentBitmapNumber() == 2)) animation.Movetonum(2);
			isJump = true;
		}
	}
	void CPlayer::Jump() {
		if (isJump) {
			y1 -= a / 20;
			if (a > 20) a -= 11;
			else {
				a = 375;
				isJump = isStand = false;
			}
			animation.OnShow();
		}
	}
	void CPlayer::SetMovingDown(bool flag)
	{
		isMovingDown = flag;
	}

	void CPlayer::SetMovingLeft(bool flag)
	{
		isMovingLeft = flag;
	}
	void CPlayer::SetMovingRight(bool flag)
	{
		isMovingRight = flag;
	}
	void CPlayer::SetMovingUp(bool flag)
	{
		isMovingUp = flag;

	}
	void CPlayer::SetXY(int nx, int ny)
	{
		x1 = nx; y1 = ny;
	}
	void CPlayer::OnShow()
	{
		if (isplayer) {
			animation.SetTopLeft(x1, y1 + 19 - animation.Height());
		}
		else {
			animation.SetTopLeft(x1, y1 + 18 - animation.Height());
		}
		animation.OnShow();
	}
}