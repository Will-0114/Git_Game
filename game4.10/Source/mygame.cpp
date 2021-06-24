/*
 * mygame.cpp: 本檔案儲遊戲本身的class的implementation
 * Copyright (C) 2002-2008 Woei-Kae Chen <wkc@csie.ntut.edu.tw>
 *
 * This file is part of game, a free game development framework for windows.
 *
 * game is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * game is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 * History:
 *   2002-03-04 V3.1
 *          Add codes to demostrate the use of CMovingBitmap::ShowBitmap(CMovingBitmap &).
 *	 2004-03-02 V4.0
 *      1. Add CGameStateInit, CGameStateRun, and CGameStateOver to
 *         demonstrate the use of states.
 *      2. Demo the use of CInteger in CGameStateRun.
 *   2005-09-13
 *      Rewrite the codes for CBall and CEraser.
 *   2005-09-20 V4.2Beta1.
 *   2005-09-29 V4.2Beta2.
 *      1. Add codes to display IDC_GAMECURSOR in GameStateRun.
 *   2006-02-08 V4.2
 *      1. Revise sample screens to display in English only.
 *      2. Add code in CGameStateInit to demo the use of PostQuitMessage().
 *      3. Rename OnInitialUpdate() -> OnInit().
 *      4. Fix the bug that OnBeginState() of GameStateInit is not called.
 *      5. Replace AUDIO_CANYON as AUDIO_NTUT.
 *      6. Add help bitmap to CGameStateRun.
 *   2006-09-09 V4.3
 *      1. Rename Move() and Show() as OnMove and OnShow() to emphasize that they are
 *         event driven.
 *   2006-12-30
 *      1. Bug fix: fix a memory leak problem by replacing PostQuitMessage(0) as
 *         PostMessage(AfxGetMainWnd()->m_hWnd, WM_CLOSE,0,0).
 *   2008-02-15 V4.4
 *      1. Add namespace game_framework.
 *      2. Replace the demonstration of animation as a new bouncing ball.
 *      3. Use ShowInitProgress(percent) to display loading progress. 
 *   2010-03-23 V4.6
 *      1. Demo MP3 support: use lake.mp3 to replace lake.wav.
*/

#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "mygame.h"
#include <windows.h>
int wall1[21][4] = { {0,0,15,480},{0,0,640,15},{0,465,640,480},{625,0,640,480},{575,415,640,480},{0,400,210,415},{245,365,555,380},{230,345,310,365},{15,335,295,345},{80,250,365,265},{280,265,640,280},{570,280,640,330},{455,200,555,215},{0,180,555,200},{325,165,480,180},{325,150,465,165},{0,115,95,200},{195,100,275,150},{195,100,640,115},{180,80,260,100},{165,65,230,80} };
int wall2[20][4] = { {0,0,15,480},{0,0,640,15},{0,465,640,480},{625,0,640,480},{180,200,240,215},{410,200,470,215}, {95,415,245,430},{360,415,510,430},{575,415,640,480},{590,400,640,415},{0,330,575,345},{0,280,60,345},{95,250,640,265},{280,230,375,250},{540,200,640,250},{575,150,640,200},{475,115,540,130},{460,100,525,115},{360,85,510,100},{0,85,275,100} };
int wall3[32][4] = { {0,0,15,480},{0,0,640,15},{0,465,640,480},{625,0,640,480},{110,445,195,465},{110,380,175,465},{65,380,115,410},{60,165,75,385},{60,165,260,180},{210,180,225,310},{210,295,310,315},{245,130,260,180}, {245,130,310,145},{295,95,310,145},{295,95,375,110},{130,80,225,95},{45,65,110,80},{230,415,275,430},{345,395,410,410},{330,245,375,265},{430,30,445,345},{395,200,445,215},{430,50,460,65},{430,330,575,345},{495,80,640,95},{495,80,510,245},{495,230,580,245},{560,280,640,295},{430,445,640,465}, {460,430,640,450},{560,415,640,430},{595,380,640,415} };
int wall4[29][4] = { {0,450,640,480},{0,0,15,480},{0,0,640,15},{625,0,640,480},{130,415,195,430},{210,400,280,415},{325,415,390,430},{425,385,460,395},{525,415,590,430},{575,365,635,380},{10,325,120,345},{100,280,120,345},{100,280,310,295},{295,280,310,330},{295,315,405,330},{390,300,405,330},{390,300,525,315},{490,315,555,330},{65,200,80,280},{65,200,200,215},{145,215,200,245},{145,230,295,245},{275,215,295,245},{275,215,640,230},{575,200,640,215},{590,165,640,215},{540,100,590,115},{155,100,295,115},{0,135,135,145} };
int wall5[27][4] = { {0,0,15,480},{0,0,640,15},{0,450,195,480},{195,465,445,480},{445,450,640,480},{625,0,640,480},{180,80,195,465},{445,80,460,465},{180,365,260,380},{115,280,195,295},{185,265,260,280},{115,215,190,230},{180,165,260,180},{100,65,245,80},{115,80,180,150},{310,430,325,480},{310,330,325,415},{310,235,325,315},{310,130,325,215},{280,115,360,130},{395,65,540,80},{445,80,460,480},{380,165,455,180},{445,215,525,230},{380,265,455,280},{445,280,525,300},{380,365,460,380} };
int RD1[3][2] = { {180,40}, {140,220}, {320,430}};
int BD1[4][2] = { {30,80},{370,60},{400,230},{460,430} };
int RD2[7][2] = { {125,440}, {190,440}, {395,390},{445,390},{445,285},{200,285},{290,200}};
int BD2[7][2] = { {125,390},{190,390},{395,440},{445,440},{395,285},{150,285},{340,200}};
int RD3[6][2] = { {25,310}, {25,220}, {25,25},{255,255},{240,385},{345,365}};
int BD3[6][2] = { {290,345},{385,365},{460,200},{460,115},{590,250},{500,400}};
int RD4[8][2] = { {240,365}, {435,250}, {340,265},{90,245},{25,215},{150,155},{350,175},{170,60}};
int BD4[7][2] = { {150,380},{340,385},{470,260},{315,255},{25,280},{220,190},{250,60} };
int RD5[7][2] = { {595,345}, {595,265}, {595,65},{475,175},{445,40},{320,80},{205,230} };
int BD5[7][2] = { {55,345},{55,265},{55,65},{130,175},{150,40},{285,80},{395,325} };
int elevator1[2][3] = { {15,250,300},{560,185,250} };
int elevator2[3][3] = { {180,200,215},{410,200,215},{360,85,280} };
int elevator5[3][3] = { {260,415,320},{310,315,250} ,{260,215,320} };
int Velevator2[1][3] = { {315,270,205} };
int Velevator3[2][3] = { {110,30,70},{175,350,385} };
int Delevator3[2][3] = { {15,445,85},{445,100,315} };
int Delevator5[2][3] = { {540,90,460},{30,410,90} };
int button1[2][2] = { {165,240},{515,175} };
int button2[4][2] = { {100,320},{520,320},{150,75},{460,75} };
int button3[1][2] = { {525,220} };
int lever1[1][2] = { {140,315} };
int lever3[1][2] = { {50,40} };
int lever5[3][2] = { {210,348},{400,248},{210,148}};
int RNUM = 0, BNUM = 0;
int buttonnum[5] = { 2,4,1,0,0 };
int velenum[5] = { 0,1,2,0,0 };
int elenum[5] = {2,3,0,0,3};
int levernum[5] = {1,0,1,0,3};
int delenum[5] = { 0,0,2,0,2 };
int game[5] = { 0,0,0,0,0 };
int gamenumber = 0;
int gameRDiamond[5] = { 3, 7, 6, 8, 7 };
int gameBDiamond[5] = { 4, 7, 6, 7, 7 };
int gameover = 0;
namespace game_framework {
/////////////////////////////////////////////////////////////////////////////
// 這個class為遊戲的遊戲開頭畫面物件
/////////////////////////////////////////////////////////////////////////////
CGameStateInit::CGameStateInit(CGame *g)
: CGameState(g)
{
}
CGameStateInit::~CGameStateInit()
{
}
void CGameStateInit::OnInit()
{
	// 當圖很多時，OnInit載入所有的圖要花很多時間。為避免玩遊戲的人
	// 等的不耐煩，遊戲會出現「Loading ...」，顯示Loading的進度。
	ShowInitProgress(0);	// 一開始的loading進度為0%
	// 開始載入資料
	state = 0;
	Back.LoadBitmap(IDB_SHOWABOUT);
	Back.SetTopLeft(114, 122);
	Background.LoadBitmap(IDB_START);
	Tool.LoadBitmap(IDB_TOOL,RGB(0,0,0));
	Word.LoadBitmap(IDB_WORD, RGB(0, 0, 0));
	Play.LoadBitmap(IDB_PLAY, RGB(255, 255, 255));
	Question.LoadBitmap(IDB_QUESTION, RGB(255, 255, 255));
	// 此OnInit動作會接到CGameStaterRun::OnInit()，所以進度還沒到100%
}
void CGameStateInit::OnBeginState()
{
}
void CGameStateInit::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	const char KEY_ESC = 27;
	const char KEY_SPACE = ' ';
	if (nChar == KEY_SPACE);					// 切換至GAME_STATE_RUN
	else if (nChar == KEY_ESC)								// Demo 關閉遊戲的方法
		PostMessage(AfxGetMainWnd()->m_hWnd, WM_CLOSE,0,0);	// 關閉遊戲
}
void CGameStateInit::OnLButtonDown(UINT nFlags, CPoint point)
{
	if (point.x >= 240 && point.y >= 400 && point.x <= 390 && point.y <= 450) {
		GotoGameState(GAME_STATE_OPINION);
	}		// 切換至GAME_STATE_OPINION
	if (point.x >= 120 && point.y >= 400 && point.x <= 156 && point.y <= 454) {
		state = 1; 
	}
	if (state == 1) {
		if (point.x >= 260 && point.y >= 282 && point.x <= 384 && point.y <= 312) {
			state = 0;
		}
	}
}
void CGameStateInit::OnShow()
{
	Background.SetTopLeft(0, 0);
	Background.ShowBitmap();
	Tool.SetTopLeft(60,400);
	Word.SetTopLeft(60,100);
	Play.SetTopLeft(240,400);
	Question.SetTopLeft(120, 400);
	Word.ShowBitmap();
	Play.ShowBitmap();
	Question.ShowBitmap();
	CDC* pDC = CDDraw::GetBackCDC();			// 取得 Back Plain 的 CDC 
	CFont f, * fp;
	f.CreatePointFont(160, "Times New Roman");	// 產生 font f; 160表示16 point的字
	fp = pDC->SelectObject(&f);					// 選用 font f
	pDC->SetBkColor(RGB(150, 150, 150));
	pDC->SetTextColor(RGB(0, 0, 0));
	char str[80];								// Demo 數字對字串的轉換
	sprintf(str, "上下左右操縱火人");
	pDC->TextOut(220, 270, str);
	sprintf(str, "ABCD操縱冰人");
	pDC->TextOut(240, 295, str);
	sprintf(str, "Ctrl可以跳關");
	pDC->TextOut(250, 320, str);
	sprintf(str, "協力集滿所有寶石並抵達出口吧！");
	pDC->TextOut(150, 345, str);
	pDC->SelectObject(fp);					
	CDDraw::ReleaseBackCDC();
	if (state == 1) {							// 叫出關於畫面 
		Back.ShowBitmap();
		CDC* pDC = CDDraw::GetBackCDC();		
		CFont f, * fp;
		f.CreatePointFont(160, "Times New Roman");	
		fp = pDC->SelectObject(&f);					
		pDC->SetBkColor(RGB(150, 150, 150));
		pDC->SetTextColor(RGB(0, 0, 0));
		char str[80];								
		sprintf(str, "台北科技大學 物件導向程式設計課程");
		pDC->TextOut(140, 150, str);
		sprintf(str, "遊戲仿作");
		pDC->TextOut(270, 180, str);
		sprintf(str, "作者：林紀緯、許庭瑋");
		pDC->TextOut(210, 210, str);
		sprintf(str, "授課教師：陳碩漢");
		pDC->TextOut(240, 240, str);
		pDC->SelectObject(fp);
		CDDraw::ReleaseBackCDC();
	}
}							
/////////////////////////////////////////////////////////////////////////////
// 這個class為遊戲的關卡選擇狀態(Game State Opinion)
/////////////////////////////////////////////////////////////////////////////
CGameStateOpinion::CGameStateOpinion(CGame* g)
	: CGameState(g)
{
}
CGameStateOpinion::~CGameStateOpinion()
{
}
void CGameStateOpinion::OnBeginState() {
	CAudio::Instance()->Play(AUDIO_MENU, true);
}
void CGameStateOpinion::OnInit() {
	ShowInitProgress(17);	// 一開始的loading進度為0%
	// 開始載入資料
	Background.LoadBitmap(IDB_STAGE);
	Back.LoadBitmap(IDB_BACK,RGB(0,0,0));
	Level.LoadBitmap(IDB_LEVEL,RGB(255,255,255));
}
void CGameStateOpinion::OnShow() {
	Background.SetTopLeft(0, 0);
	Background.ShowBitmap();
	Back.SetTopLeft(50,420);
	Back.ShowBitmap();
	Level.SetTopLeft(450, 420);
}
void CGameStateOpinion::OnLButtonDown(UINT nFlags, CPoint point)
{
	if (point.x >= 300 && point.y >= 400 && point.x <= 340 && point.y <= 430) {		//進入第一關
		gamenumber = 1;
		CAudio::Instance()->Stop(AUDIO_MENU);
		GotoGameState(GAME_STATE_RUN);
	}
	if (point.x >= 335 && point.y >= 360 && point.x <= 360 && point.y <= 380) {		//進入第二關
		gamenumber = 2;
		CAudio::Instance()->Stop(AUDIO_MENU);
		GotoGameState(GAME_STATE_RUN);
	}// 切換至GAME_STATE_RUN
	if (point.x >= 305 && point.y >= 315 && point.x <= 340 && point.y <= 340) {		//進入第三關
		gamenumber = 3;
		CAudio::Instance()->Stop(AUDIO_MENU);
		GotoGameState(GAME_STATE_RUN);
	}
	if (point.x >= 310 && point.y >= 250 && point.x <= 335 && point.y <= 275) {		//進入第四關
		gamenumber = 4;
		CAudio::Instance()->Stop(AUDIO_MENU);
		GotoGameState(GAME_STATE_RUN);
	}
	if (point.x >= 310 && point.y >= 185 && point.x <= 335 && point.y <= 210) {		//進入第五關
		gamenumber = 5;
		CAudio::Instance()->Stop(AUDIO_MENU);
		GotoGameState(GAME_STATE_RUN);
	}
	if (point.x >= 50 && point.y >= 420 && point.x <= 151 && point.y <= 459) {		//返回
		CAudio::Instance()->Stop(AUDIO_MENU);
		GotoGameState(GAME_STATE_INIT);
	}
}
/////////////////////////////////////////////////////////////////////////////
// 這個class為遊戲的結束狀態(Game Over)
/////////////////////////////////////////////////////////////////////////////
CGameStateOver::CGameStateOver(CGame *g)
: CGameState(g)
{
}
void CGameStateOver::OnMove()
{

}
void CGameStateOver::OnBeginState()
{
	if (gameover) {
	}
	else {
		CAudio::Instance()->Play(AUDIO_DEATH, false);	//死亡音樂
	}
	CAudio::Instance()->Stop(AUDIO_BGM);				//關閉遊戲BGM
	CAudio::Instance()->Play(AUDIO_OVER,false);			//OVER音效
}

void CGameStateOver::OnInit()
{
	// 當圖很多時，OnInit載入所有的圖要花很多時間。為避免玩遊戲的人
	//     等的不耐煩，遊戲會出現「Loading ...」，顯示Loading的進度。
	ShowInitProgress(66);	// 接個前一個狀態的進度，此處進度視為66%
	// 開始載入資料
	Back.LoadBitmap(IDB_ENDBACK);
	J.AddBitmap(IDB_PURPLE, RGB(255, 255, 255));
	J.AddBitmap(IDB_ORANGE, RGB(255, 255, 255));
	P.AddBitmap(IDB_MARK, RGB(255, 255, 255));
	P.AddBitmap(IDB_X, RGB(255, 255, 255));
	D.AddBitmap(IDB_MARK, RGB(255, 255, 255));
	D.AddBitmap(IDB_X, RGB(255, 255, 255));
	Over.LoadBitmap(IDB_GAMEOVER);
	// 最終進度為100%
	ShowInitProgress(100);
}
void CGameStateOver::OnLButtonDown(UINT nFlags, CPoint point)
{
	if (gameover) {
		if (point.x >= 264 && point.y >= 197 && point.x <= 384 && point.y <= 327) {				//通關時的返回鍵
			CAudio::Instance()->Stop(AUDIO_OVER);
			GotoGameState(GAME_STATE_OPINION);
		}
	}
	else {
		if (point.x >= 177 && point.y >= 275 && point.x <= 259 && point.y <= 307){				//輸掉時的返回鍵
			CAudio::Instance()->Stop(AUDIO_OVER);
			GotoGameState(GAME_STATE_OPINION);
		}
		else if(point.x >= 386 && point.y >= 275 && point.x <= 468 && point.y <= 307) {			//輸掉時的返回鍵
			CAudio::Instance()->Stop(AUDIO_OVER);
			GotoGameState(GAME_STATE_OPINION);
		}
		else if(point.x >= 282 && point.y >= 275 && point.x <= 364 && point.y <= 307) {			//通關時的再完一次鍵
			CAudio::Instance()->Stop(AUDIO_OVER);
			GotoGameState(GAME_STATE_RUN);
		}
	}
}
void CGameStateOver::OnShow()
{
	if (gameover) {
		Back.SetTopLeft(114, 122);
		Back.ShowBitmap();
		P.SetTopLeft(254, 172);
		D.SetTopLeft(254, 202);
		J.SetTopLeft(374, 192);
		P.OnShow();
		if ((RNUM == 0) && (BNUM == 0)) {
			D.Movetonum(0);		//寶石收集完打勾
		}
		else {
			D.Movetonum(1);		//寶石沒收集完打叉
		}
		D.OnShow();
		if (D.GetCurrentBitmapNumber() == 1) {
			J.Movetonum(0);		//右邊寶石的變動
		}
		else {
			J.Movetonum(1);		
		}
		J.OnShow();
	}
	else {
		Over.SetTopLeft(114, 122);
		Over.ShowBitmap();
	}
}
/////////////////////////////////////////////////////////////////////////////
// 這個class為遊戲的遊戲執行物件，主要的遊戲程式都在這裡
/////////////////////////////////////////////////////////////////////////////
CGameStateRun::CGameStateRun(CGame* g)
	: CGameState(g)
{
	picX = picY = 0;
}
CGameStateRun::~CGameStateRun()
{
	delete[] RD;
	delete[] BD;
	delete[] elevator;
	delete[] button;
	delete[] lever;
	delete[] Velevator;
	delete[] Delevator;
}
void CGameStateRun::OnBeginState()
{
	CAudio::Instance()->Play(AUDIO_BGM, true);
	const int BALL_GAP = 90;
	const int BALL_XY_OFFSET = 45;
	const int BALL_PER_ROW = 7;
	const int HITS_LEFT = 10;
	const int HITS_LEFT_X = 590;
	const int HITS_LEFT_Y = 0;
	const int BACKGROUND_X = 0;
	const int ANIMATION_SPEED = 15;
	RD = new CRDiamond[gameRDiamond[gamenumber - 1]];
	BD = new CBDiamond[gameBDiamond[gamenumber - 1]];
	elevator = new CMovingBitmap[elenum[gamenumber - 1]];
	Velevator = new CMovingBitmap[velenum[gamenumber - 1]];
	Delevator = new CMovingBitmap[delenum[gamenumber - 1]];
	button = new CMovingBitmap[buttonnum[gamenumber - 1]];
	lever = new CAnimation[levernum[gamenumber - 1]];
	RNUM = gameRDiamond[gamenumber - 1];
	BNUM = gameBDiamond[gamenumber - 1];
	background.Movetonum(gamenumber-1);
	passAll = 0;
	for (int i = 0; i < elenum[gamenumber - 1]; i++) {
		elevator[i].LoadBitmap(IDB_ELEVATOR);
	}
	for (int i = 0; i < velenum[gamenumber - 1]; i++) {
		Velevator[i].LoadBitmap(IDB_VELEVATOR);
	}
	for (int i = 0; i < buttonnum[gamenumber - 1]; i++) {
		button[i].LoadBitmap(IDB_BUTTON,RGB(255,255,255));
	}
	for (int i = 0; i < delenum[gamenumber - 1]; i++) {
		Delevator[i].LoadBitmap(IDB_ELEVATOR);
	}
	for (int i = 0; i < levernum[gamenumber - 1]; i++) {
		lever[i].AddBitmap(IDB_RIGHT, RGB(255, 255, 255));
		lever[i].AddBitmap(IDB_LEFT, RGB(255, 255, 255));
	}
	if (gamenumber == 1){
		for (int i = 0; i < gameRDiamond[gamenumber - 1]; i++) {
			RD[i].SetXY(RD1[i][0], RD1[i][1]);
		}
		for (int i = 0; i < gameBDiamond[gamenumber - 1]; i++) {
			BD[i].SetXY(BD1[i][0], BD1[i][1]);
		}
		for (int i = 0; i < elenum[gamenumber - 1]; i++) {
			elevator[i].SetTopLeft(elevator1[i][0], elevator1[i][1]);
		}
		for (int i = 0; i < buttonnum[gamenumber - 1]; i++) {
			button[i].SetTopLeft(button1[i][0], button1[i][1]);
		}
		for (int i = 0; i < levernum[gamenumber - 1]; i++) {
			lever[i].SetTopLeft(lever1[i][0], lever1[i][1]);
		}
		BDoor.SetTopLeft(560, 55);
		RDoor.SetTopLeft(500, 55);
		Stone.Initialize();
		Stone.SetXY(370, 115);
		fireman.Initialize();
		fireman.SetXY(100, 410);
		icegirl.Initialize();
		icegirl.SetXY(100, 350);
	}
	else if (gamenumber == 2) {
		for (int i = 0; i < gameRDiamond[gamenumber - 1]; i++) {
			RD[i].SetXY(RD2[i][0], RD2[i][1]);
		}
		for (int i = 0; i < gameBDiamond[gamenumber - 1]; i++) {
			BD[i].SetXY(BD2[i][0], BD2[i][1]);
		}
		for (int i = 0; i < elenum[gamenumber - 1]; i++) {
			elevator[i].SetTopLeft(elevator2[i][0], elevator2[i][1]);
		}
		for (int i = 0; i < velenum[gamenumber - 1]; i++) {
			Velevator[i].SetTopLeft(Velevator2[i][0], Velevator2[i][1]);
		}
		for (int i = 0; i < buttonnum[gamenumber - 1]; i++) {
			button[i].SetTopLeft(button2[i][0], button2[i][1]);
		}
		BDoor.SetTopLeft(25, 35);
		RDoor.SetTopLeft(80, 35);
		fireman.Initialize();
		fireman.SetXY(25, 425);
		icegirl.Initialize();
		icegirl.SetXY(55, 425);
	}
	else if (gamenumber == 3) {
		for (int i = 0; i < gameRDiamond[gamenumber - 1]; i++) {
			RD[i].SetXY(RD3[i][0], RD3[i][1]);
		}
		for (int i = 0; i < gameBDiamond[gamenumber - 1]; i++) {
			BD[i].SetXY(BD3[i][0], BD3[i][1]);
		}
		for (int i = 0; i < levernum[gamenumber - 1]; i++) {
			lever[i].SetTopLeft(lever3[i][0], lever3[i][1]);
		}
		for (int i = 0; i < velenum[gamenumber - 1]; i++) {
			Velevator[i].SetTopLeft(Velevator3[i][0], Velevator3[i][1]);
		}
		for (int i = 0; i < buttonnum[gamenumber - 1]; i++) {
			button[i].SetTopLeft(button3[i][0], button3[i][1]);
		}
		for (int i = 0; i < delenum[gamenumber - 1]; i++) {
			Delevator[i].SetTopLeft(Delevator3[i][0], Delevator3[i][1]);
		}
		BDoor.SetTopLeft(80, 335);
		RDoor.SetTopLeft(130, 335);
		fireman.Initialize();
		fireman.SetXY(70, 420);
		icegirl.Initialize();
		icegirl.SetXY(585, 30);
	}
	else if (gamenumber == 4) {
		for (int i = 0; i < gameRDiamond[gamenumber - 1]; i++) {
			RD[i].SetXY(RD4[i][0], RD4[i][1]);
		}
		for (int i = 0; i < gameBDiamond[gamenumber - 1]; i++) {
			BD[i].SetXY(BD4[i][0], BD4[i][1]);
		}
		fan.SetTopLeft(10, 325);
		BDoor.SetTopLeft(25, 90);
		RDoor.SetTopLeft(75, 90);
		Stone.Initialize();
		Stone.SetXY(545, 65);
		fireman.Initialize();
		fireman.SetXY(25, 410);
		icegirl.Initialize();
		icegirl.SetXY(70, 410);
	}
	else if (gamenumber == 5) {
		for (int i = 0; i < gameRDiamond[gamenumber - 1]; i++) {
			RD[i].SetXY(RD5[i][0], RD5[i][1]);
		}
		for (int i = 0; i < gameBDiamond[gamenumber - 1]; i++) {
			BD[i].SetXY(BD5[i][0], BD5[i][1]);
		}
		for (int i = 0; i < elenum[gamenumber - 1]; i++) {
			elevator[i].SetTopLeft(elevator5[i][0], elevator5[i][1]);
		}
		for (int i = 0; i < levernum[gamenumber - 1]; i++) {
			lever[i].SetTopLeft(lever5[i][0], lever5[i][1]);
		}
		for (int i = 0; i < delenum[gamenumber - 1]; i++) {
			Delevator[i].SetTopLeft(Delevator5[i][0], Delevator5[i][1]);
		}
		BDoor.SetTopLeft(475, 235);
		RDoor.SetTopLeft(130, 235);
		fireman.Initialize();
		fireman.SetXY(210, 425);
		icegirl.Initialize();
		icegirl.SetXY(385, 425);
	}
	background.SetTopLeft(0,0);	
}

void CGameStateRun::OnMove()							// 移動遊戲元素
{
	int i;
	int pass = 0;
	int pass2 = 0;
	Stone.OnFloor();
	fireman.OnMove();
	fireman.OnFloor();
	icegirl.OnMove();
	icegirl.OnFloor();
	bool isStand = false;
	bool isWall = false;
	if (gamenumber == 1) {		//第一關
		//////////////////////////////////////////石頭的判斷/////////////////////////////////////
		for (i = 0; i < 21; i++) {
			if (Stone.HitLeftWall(wall1[i][0], wall1[i][1], wall1[i][2], wall1[i][3])) {
				Stone.SetXY(Stone.GetX1(), wall1[i][1] - 24);
				isStand = true;
				break;
			}
			else {
				isStand = false;
			}
			
		}
		for (i = 0; i < 21; i++)
		{
			if (fireman.GetState() == 3) {
				if (Stone.HitRightWall(wall1[i][0], wall1[i][1], wall1[i][2], wall1[i][3])) {
					Stone.SetXY(wall1[i][2] + 1, Stone.GetY1());
					isWall = true;
					break;
				}
			}
			else if (fireman.GetState() == 2) {
				if (Stone.HitRightWall(wall1[i][0], wall1[i][1], wall1[i][2], wall1[i][3])) {
					Stone.SetXY(wall1[i][0] - (Stone.GetX2() - Stone.GetX1()), Stone.GetY1());
					isWall = true;
					break;
				}
			}
		}
		Stone.SetIsStand(isStand);
		Stone.SetWall(isWall);
		isStand = false;
		isWall = false;
		if(fireman.GetState()== 3){
			if (fireman.HitRightWall(Stone.GetX1(),Stone.GetY1(),Stone.GetX2(),Stone.GetY2())) {
				Stone.SetXY(fireman.GetX1()-24, Stone.GetY1());
			}
		}else if (fireman.GetState() == 2) {
			if (fireman.HitRightWall(Stone.GetX1(), Stone.GetY1(), Stone.GetX2(), Stone.GetY2())) {
				Stone.SetXY(fireman.GetX2(), Stone.GetY1());
			}
		}
		//////////////////////////////////////////判斷火人是否在物件上/////////////////////////////////////
		if (fireman.GetJumpState()) {
			for (i = 0; i < 21; i++) {
				if (fireman.HitCeiling(wall1[i][0], wall1[i][1], wall1[i][2], wall1[i][3])) {
					fireman.SetXY(fireman.GetX1(), wall1[i][3]);
					fireman.SetIsJump(false);
					fireman.Seta(375);
					break;
				}
			}
		}
		for (i = 0; i < 21; i++) {
			if (fireman.GetState() == 3) {
				if (fireman.HitRightWall(wall1[i][0], wall1[i][1], wall1[i][2], wall1[i][3])) {
					fireman.SetXY(wall1[i][2]+1, fireman.GetY1());
					isWall = true;
					break;
				}
			}
			else if (fireman.GetState() == 2) {
				if (fireman.HitRightWall(wall1[i][0], wall1[i][1], wall1[i][2], wall1[i][3])) {
					fireman.SetXY(wall1[i][0] - (fireman.GetX2()-fireman.GetX1()), fireman.GetY1());
					isWall = true;
					break;
				}
			}
		}
		fireman.SetWall(isWall);
		for (i = 0; i < 21; i++) {
			if (fireman.HitLeftWall(wall1[i][0], wall1[i][1], wall1[i][2], wall1[i][3])) {
				fireman.SetXY(fireman.GetX1(), wall1[i][1] - 19);
				isStand = true;
				break;
			}
			else {
				isStand = false;
			}
		}
		if (fireman.HitLeftWall(Stone.GetX1(), Stone.GetY1(), Stone.GetX2(), Stone.GetY2())) {
			fireman.SetXY(fireman.GetX1(), Stone.GetY1() - 19);
			isStand = true;
		}
		else {
			isStand = (false || isStand);
		}
		
		for (i = 0; i < elenum[gamenumber - 1]; i++) {
			if (fireman.HitCeiling(elevator[i].Left(), elevator[i].Top(), elevator[i].Left() + elevator[i].Width(), elevator[i].Top() + elevator[i].Height())) {
				fireman.SetXY(fireman.GetX1(), elevator[i].Top() + elevator[i].Height());
				fireman.SetIsJump(false);
				fireman.Seta(375);
				break;
			}
			if (fireman.HitLeftWall(elevator[i].Left(), elevator[i].Top(), elevator[i].Left() +elevator[i].Width(), elevator[i].Top() + elevator[i].Height())) {
				fireman.SetXY(fireman.GetX1(), elevator[i].Top() - 19);
				isStand = true;
				break;
			}
			else {
				isStand = (false || isStand);
			}
		}
		fireman.SetIsStand(isStand);
		isStand = false;
		isWall = false;
		/////////////////////////////////////////火人對石頭的位移/////////////////////////////////////
		for (i = 0; i < 21; i++) {
			if (Stone.HitLeftWall(wall1[i][0], wall1[i][1], wall1[i][2], wall1[i][3])) {
				Stone.SetXY(Stone.GetX1(), wall1[i][1] - 24);
				isStand = true;
				break;
			}
			else {
				isStand = false;
			}
		}
		for (i = 0; i < 21; i++)
		{
			if (fireman.GetState() == 3) {
				if (Stone.HitRightWall(wall1[i][0], wall1[i][1], wall1[i][2], wall1[i][3])) {
					Stone.SetXY(wall1[i][2] + 1, Stone.GetY1());
					isWall = true;
					break;
				}
			}
			else if (fireman.GetState() == 2) {
				if (Stone.HitRightWall(wall1[i][0], wall1[i][1], wall1[i][2], wall1[i][3])) {
					Stone.SetXY(wall1[i][0] - (Stone.GetX2() - Stone.GetX1()), Stone.GetY1());
					isWall = true;
					break;
				}
			}
		}
		Stone.SetIsStand(isStand);
		Stone.SetWall(isWall);
		isStand = false;
		isWall = false;
		//////////////////////////////////////////判斷冰人是否在物件上/////////////////////////////////////
		if (icegirl.GetState() == 3) {
			if (icegirl.HitRightWall(Stone.GetX1(), Stone.GetY1(), Stone.GetX2(), Stone.GetY2())) {
				Stone.SetXY(icegirl.GetX1() - 24, Stone.GetY1());
			}
		}
		else if (icegirl.GetState() == 2) {
			if (icegirl.HitRightWall(Stone.GetX1(), Stone.GetY1(), Stone.GetX2(), Stone.GetY2())) {
				Stone.SetXY(icegirl.GetX2(), Stone.GetY1());
			}
		}
		if (icegirl.GetJumpState()) {
			for (i = 0; i < 21; i++) {
				if (icegirl.HitCeiling(wall1[i][0], wall1[i][1], wall1[i][2], wall1[i][3])) {
					icegirl.SetXY(icegirl.GetX1(), wall1[i][3]);
					icegirl.SetIsJump(false);
					icegirl.Seta(300);
					break;
				}
			}
		}
		for (i = 0; i < 21; i++) {
			if (icegirl.GetState() == 3) {
				if (icegirl.HitRightWall(wall1[i][0], wall1[i][1], wall1[i][2], wall1[i][3])) {
					icegirl.SetXY(wall1[i][2] + 1, icegirl.GetY1());
					isWall = true;
					break;
				}
			}
			else if (icegirl.GetState() == 2) {
				if (icegirl.HitRightWall(wall1[i][0], wall1[i][1], wall1[i][2], wall1[i][3])) {
					icegirl.SetXY(wall1[i][0] - (icegirl.GetX2() - icegirl.GetX1()), icegirl.GetY1());
					isWall = true;
					break;
				}
			}
		}
		icegirl.SetWall(isWall);
		for (i = 0; i < 21; i++) {
			if (icegirl.HitLeftWall(wall1[i][0], wall1[i][1], wall1[i][2], wall1[i][3])) {
				icegirl.SetXY(icegirl.GetX1(), wall1[i][1] - 18);
				isStand = true;
				break;
			}
			else {
				isStand = false;
			}
		}
		if (icegirl.HitLeftWall(Stone.GetX1(), Stone.GetY1(), Stone.GetX2(), Stone.GetY2())) {
			icegirl.SetXY(icegirl.GetX1(), Stone.GetY1() - 19);
			isStand = true;
		}
		else {
			isStand = (false || isStand);
		}
		for (i = 0; i < elenum[gamenumber - 1]; i++) {
			if (icegirl.HitCeiling(elevator[i].Left(), elevator[i].Top(), elevator[i].Left() + elevator[i].Width(), elevator[i].Top() + elevator[i].Height())) {
				icegirl.SetXY(icegirl.GetX1(), elevator[i].Top() + elevator[i].Height());
				icegirl.SetIsJump(false);
				icegirl.Seta(375);
				break;
			}
			if (icegirl.HitLeftWall(elevator[i].Left(), elevator[i].Top(), elevator[i].Left() + elevator[i].Width(), elevator[i].Top() + elevator[i].Height())) {
				icegirl.SetXY(icegirl.GetX1(), elevator[i].Top() - 19);
				isStand = true;
				break;
			}
			else {
				isStand = (false || isStand);
			}
		}
		icegirl.SetIsStand(isStand);
		fireman.Jump();
		icegirl.Jump();
		//////////////////////////////////////////判斷按鈕/////////////////////////////////////
		bool isButton = 0;
		if ((fireman.GetX1() > button1[0][0]) && (fireman.GetX2() < button[0].Left() + button[0].Width()) && (fireman.GetY2() > button1[0][1]) && (fireman.GetY2() < button1[0][1] + button[0].Height() + 10)) {
			isButton = 1;
		}
		else if ((fireman.GetX1() > button1[1][0]) && (fireman.GetX2() < button[1].Left() + button[1].Width()) && (fireman.GetY2() > button1[1][1]) && (fireman.GetY2() < button1[1][1] + button[1].Height() + 10)) {
			isButton = 1;
		}
		else {
			isButton = 0;
		}
		if ((icegirl.GetX1() > button1[0][0]) && (icegirl.GetX2() < button[0].Left() + button[0].Width()) && (icegirl.GetY2() > button1[0][1]) && (icegirl.GetY2() < button1[0][1] + button[0].Height() + 10)) {
			isButton = 1;
		}
		else if ((icegirl.GetX1() > button1[1][0]) && (icegirl.GetX2() < button[1].Left() + button[1].Width()) && (icegirl.GetY2() > button1[1][1]) && (icegirl.GetY2() < button1[1][1] + button[1].Height() + 10)) {
			isButton = 1;
		}
		else {
			isButton = (0 || isButton);
		}
		//////////////////////////////////////////電梯位移/////////////////////////////////////
		if (isButton) {
			if (elevator[1].Top() <= elevator1[1][2]) {
				elevator[1].SetTopLeft(elevator[1].Left(), elevator[1].Top() + 1);
			}
		}
		else {
			if (elevator[1].Top() >= elevator1[1][1]) {
				elevator[1].SetTopLeft(elevator[1].Left(), elevator[1].Top() - 1);
			}
		}
		//////////////////////////////////////////判斷操縱桿/////////////////////////////////////
		for (i = 0; i < levernum[gamenumber - 1]; i++) {
			if (fireman.GetState() == 3) {
				if (fireman.HitRightWall(lever1[i][0], lever1[i][1], lever1[i][0] + lever[i].Width(), lever1[i][1] + lever[i].Height())) {
					if (lever[i].GetCurrentBitmapNumber() == 0) {
						lever[i].Movetonum(1);
					}
				}
			}
			else if(fireman.GetState() == 2){
				if (fireman.HitRightWall(lever1[i][0], lever1[i][1], lever1[i][0] + lever[i].Width(), lever1[i][1] + lever[i].Height())) {
					if (lever[i].GetCurrentBitmapNumber() == 1) {
						lever[i].Movetonum(0);
					}
				}
			}
			if (icegirl.GetState() == 3) {
				if (icegirl.HitRightWall(lever1[i][0], lever1[i][1], lever1[i][0] + lever[i].Width(), lever1[i][1] + lever[i].Height())) {
					if (lever[i].GetCurrentBitmapNumber() == 0) {
						lever[i].Movetonum(1);
					}
				}
			}
			else if (icegirl.GetState() == 2) {
				if (icegirl.HitRightWall(lever1[i][0], lever1[i][1], lever1[i][0] + lever[i].Width(), lever1[i][1] + lever[i].Height())) {
					if (lever[i].GetCurrentBitmapNumber() == 1) {
						lever[i].Movetonum(0);
					}
				}
			}
			if (lever[i].GetCurrentBitmapNumber() == 0) {
				if (elevator[0].Top() >= elevator1[0][1]) {
					elevator[0].SetTopLeft(elevator[0].Left(), elevator[0].Top() - 1);
				}
			}
			else if (lever[i].GetCurrentBitmapNumber() == 1) {
				if (elevator[0].Top() <= elevator1[0][2]) {
					elevator[0].SetTopLeft(elevator[0].Left(), elevator[0].Top() + 1);
				}
			}
		}
		//////////////////////////////////////////鑽石碰撞/////////////////////////////////////
		for (int i = 0; i < gameRDiamond[gamenumber-1]; i++) {
			if (fireman.HitRDiamond(RD[i])) {
				if (RD[i].GetExist()) {
					CAudio::Instance()->Play(AUDIO_DIAMOND, false);
					RNUM--;
				}
				RD[i].SetIsExist(0);
				
			}
		}
		for (int i = 0; i < gameBDiamond[gamenumber-1]; i++) {
			if (icegirl.HitBDiamond(BD[i])) {
				if (BD[i].GetExist()) {
					CAudio::Instance()->Play(AUDIO_DIAMOND, false);
					BNUM--;
				}
				BD[i].SetIsExist(0);
				
			}
		}
		//////////////////////////////////////////過關或失敗/////////////////////////////////////
		if ((fireman.GetX1() + fireman.GetX2()) / 2 > 500 && (fireman.GetX1() + fireman.GetX2()) / 2 < 543 && (fireman.GetY1() + fireman.GetY2()) / 2 > 55 && (fireman.GetY1() + fireman.GetY2()) / 2 < 102) {
			pass = 1;
		}
		else {
			pass = 0;
		}
		if ((icegirl.GetX1() + icegirl.GetX2()) / 2 > 560 && (icegirl.GetX1() + icegirl.GetX2()) / 2 < 603 && (icegirl.GetY1() + icegirl.GetY2()) / 2 > 55 && (icegirl.GetY1() + icegirl.GetY2()) / 2 < 102) {
			pass2 = 1;
		}
		else {
			pass2 = 0;
		}
		if ((((icegirl.GetX1() > 310) && (icegirl.GetX1() < 360)) || ((icegirl.GetX2() > 310) && (icegirl.GetX2() < 360))) && ((icegirl.GetY2() < 470) && (icegirl.GetY2() > 460))) {
			gameover = 0;
			
			GotoGameState(GAME_STATE_OVER);
		}else if ((((fireman.GetX1() > 410) && (fireman.GetX1() < 460)) || ((fireman.GetX2() > 410) && (fireman.GetX2() < 460))) && ((fireman.GetY2() < 370) && (fireman.GetY2() > 360))) {
			gameover = 0;
			
			GotoGameState(GAME_STATE_OVER);
		}
		else if ((((fireman.GetX1() > 440) && (fireman.GetX1() < 490)) || ((fireman.GetX2() > 440) && (fireman.GetX2() < 490))) && ((fireman.GetY2() < 470) && (fireman.GetY2() > 460))) {
			gameover = 0;
			
			GotoGameState(GAME_STATE_OVER);
		}
		else if ((((icegirl.GetX1() > 410) && (icegirl.GetX1() < 460)) || ((icegirl.GetX2() > 410) && (icegirl.GetX2() < 460))) && ((icegirl.GetY2() < 370) && (icegirl.GetY2() > 360))) {
			gameover = 0;
			GotoGameState(GAME_STATE_OVER);
		}
	}else if(gamenumber == 2){
		//////////////////////////////////////////判斷火人是否在物件上/////////////////////////////////////
		if (fireman.GetJumpState()) {
			for (i = 0; i < 20; i++) {
				if (fireman.HitCeiling(wall2[i][0], wall2[i][1], wall2[i][2], wall2[i][3])) {
					fireman.SetXY(fireman.GetX1(), wall2[i][3]);
					fireman.SetIsJump(false);
					fireman.Seta(375);
					break;
				}
			}
		}
		for (i = 0; i < 20; i++) {
			if (fireman.GetState() == 3) {
				if (fireman.HitRightWall(wall2[i][0], wall2[i][1], wall2[i][2], wall2[i][3])) {
					fireman.SetXY(wall2[i][2] + 1, fireman.GetY1());
					isWall = true;
					break;
				}
			}
			else if (fireman.GetState() == 2) {
				if (fireman.HitRightWall(wall2[i][0], wall2[i][1], wall2[i][2], wall2[i][3])) {
					fireman.SetXY(wall2[i][0] - (fireman.GetX2() - fireman.GetX1()), fireman.GetY1());
					isWall = true;
					break;
				}
			}
		}
		for (i = 0; i < velenum[gamenumber - 1]; i++) {
			if (fireman.GetState() == 3) {
				if (fireman.HitRightWall(Velevator[i].Left(), Velevator[i].Top(), Velevator[i].Left() + Velevator[i].Width(), Velevator[i].Top() + Velevator[i].Height())) {
					fireman.SetXY(Velevator[i].Left() + Velevator->Width(), fireman.GetY1());
					isWall = true;
					break;
				}
			}
			else if (fireman.GetState() == 2) {
				if (fireman.HitRightWall(Velevator[i].Left(), Velevator[i].Top(), Velevator[i].Left() + Velevator[i].Width(), Velevator[i].Top() + Velevator[i].Height())) {
					fireman.SetXY(Velevator[i].Left() - (fireman.GetX2() - fireman.GetX1()), fireman.GetY1());
					isWall = true;
					break;
				}
			}
		}
		fireman.SetWall(isWall);
		for (i = 0; i < 20; i++) {
			if (fireman.HitLeftWall(wall2[i][0], wall2[i][1], wall2[i][2], wall2[i][3])) {
				fireman.SetXY(fireman.GetX1(), wall2[i][1] - 19);
				isStand = true;
				break;
			}
			else {
				isStand = false;
			}
		}
		for (i = 0; i < elenum[gamenumber - 1]; i++) {
			if (fireman.HitLeftWall(elevator[i].Left(), elevator[i].Top(), elevator[i].Left() + elevator[i].Width(), elevator[i].Top() + elevator[i].Height())) {
				fireman.SetXY(fireman.GetX1(), elevator[i].Top() - 19);
				isStand = true;
				break;
			}
			else {
				isStand = (false || isStand);
			}
		}
		for (i = 0; i < elenum[gamenumber - 1]; i++) {
			if (fireman.HitCeiling(elevator[i].Left(), elevator[i].Top(), elevator[i].Left() + elevator[i].Width(), elevator[i].Top() + elevator[i].Height())) {
				fireman.SetXY(fireman.GetX1(), elevator[i].Top() + elevator[i].Height());
				fireman.SetIsJump(false);
				fireman.Seta(375);
				break;
			}
			if (fireman.HitLeftWall(elevator[i].Left(), elevator[i].Top(), elevator[i].Left() + elevator[i].Width(), elevator[i].Top() + elevator[i].Height())) {
				fireman.SetXY(fireman.GetX1(), elevator[i].Top() - 19);
				isStand = true;
				break;
			}
			else {
				isStand = (false || isStand);
			}

		}
		fireman.SetIsStand(isStand);
		isStand = false;
		isWall = false;
		//////////////////////////////////////////判斷冰人是否在物件上/////////////////////////////////////
		if (icegirl.GetJumpState()) {
			for (i = 0; i < 20; i++) {
				if (icegirl.HitCeiling(wall2[i][0], wall2[i][1], wall2[i][2], wall2[i][3])) {
					icegirl.SetXY(icegirl.GetX1(), wall2[i][3]);
					icegirl.SetIsJump(false);
					icegirl.Seta(375);
					break;
				}
			}
		}
		for (i = 0; i < 20; i++) {
			if (icegirl.GetState() == 3) {
				if (icegirl.HitRightWall(wall2[i][0], wall2[i][1], wall2[i][2], wall2[i][3])) {
					icegirl.SetXY(wall2[i][2] + 1, icegirl.GetY1());
					isWall = true;
					break;
				}
			}
			else if (icegirl.GetState() == 2) {
				if (icegirl.HitRightWall(wall2[i][0], wall2[i][1], wall2[i][2], wall2[i][3])) {
					icegirl.SetXY(wall2[i][0] - (icegirl.GetX2() - icegirl.GetX1()), icegirl.GetY1());
					isWall = true;
					break;
				}
			}
		}
		for (i = 0; i < velenum[gamenumber - 1]; i++) {
			if (icegirl.GetState() == 3) {
				if (icegirl.HitRightWall(Velevator[i].Left(), Velevator[i].Top(), Velevator[i].Left() + Velevator[i].Width(), Velevator[i].Top() + Velevator[i].Height())) {
					icegirl.SetXY(Velevator[i].Left() + Velevator->Width(), icegirl.GetY1());
					isWall = true;
					break;
				}
			}
			else if (icegirl.GetState() == 2) {
				if (icegirl.HitRightWall(Velevator[i].Left(), Velevator[i].Top(), Velevator[i].Left() + Velevator[i].Width(), Velevator[i].Top() + Velevator[i].Height())) {
					icegirl.SetXY(Velevator[i].Left() - (icegirl.GetX2() - icegirl.GetX1()), icegirl.GetY1());
					isWall = true;
					break;
				}
			}
		}
		icegirl.SetWall(isWall);
		for (i = 0; i < 20; i++) {
			if (icegirl.HitLeftWall(wall2[i][0], wall2[i][1], wall2[i][2], wall2[i][3])) {
				icegirl.SetXY(icegirl.GetX1(), wall2[i][1] - 18);
				isStand = true;
				break;
			}
			else {
				isStand = false;
			}
		}
		for (i = 0; i < elenum[gamenumber - 1]; i++) {
			if (icegirl.HitCeiling(elevator[i].Left(), elevator[i].Top(), elevator[i].Left() + elevator[i].Width(), elevator[i].Top() + elevator[i].Height())) {
				icegirl.SetXY(icegirl.GetX1(), elevator[i].Top() + elevator[i].Height());
				icegirl.SetIsJump(false);
				icegirl.Seta(375);
				break;
			}
			if (icegirl.HitLeftWall(elevator[i].Left(), elevator[i].Top(), elevator[i].Left() + elevator[i].Width(), elevator[i].Top() + elevator[i].Height())) {
				icegirl.SetXY(icegirl.GetX1(), elevator[i].Top() - 19);
				isStand = true;
				break;
			}
			else {
				isStand = (false || isStand);
			}
		}
		icegirl.SetIsStand(isStand);
		fireman.Jump();
		icegirl.Jump();
		bool isButton = 0;
		//////////////////////////////////////////判斷按鈕/////////////////////////////////////
		if ((fireman.GetX1() > button2[2][0]) && (fireman.GetX2() < button[2].Left() + button[2].Width()) && (fireman.GetY2() > button2[2][1]) && (fireman.GetY2() < button2[2][1] + button[2].Height() + 10)) {
			isButton = 1;
		}
		else if ((fireman.GetX1() > button2[3][0]) && (fireman.GetX2() < button[3].Left() + button[3].Width()) && (fireman.GetY2() > button2[3][1]) && (fireman.GetY2() < button2[3][1] + button[3].Height() + 10)) {
			isButton = 1;
		}
		else {
			isButton = 0;
		}
		if ((icegirl.GetX1() > button2[2][0]) && (icegirl.GetX2() < button[2].Left() + button[2].Width()) && (icegirl.GetY2() > button2[2][1]) && (icegirl.GetY2() < button2[2][1] + button[0].Height() + 10)) {
			isButton = 1;
		}
		else if ((icegirl.GetX1() > button2[3][0]) && (icegirl.GetX2() < button[3].Left() + button[3].Width()) && (icegirl.GetY2() > button2[3][1]) && (icegirl.GetY2() < button2[3][1] + button[1].Height() + 10)) {
			isButton = 1;
		}
		else {
			isButton = (0 || isButton);
		}
		//////////////////////////////////////////電梯位移/////////////////////////////////////
		if (isButton) {
			if (elevator[2].Left() >= elevator2[2][2]) {
				elevator[2].SetTopLeft(elevator[2].Left()-1, elevator[2].Top());
			}
		}
		else {
			if (elevator[2].Left() <= elevator2[2][0]) {
				elevator[2].SetTopLeft(elevator[2].Left()+1, elevator[2].Top());
			}
		}
		isButton = 0;
		//////////////////////////////////////////判斷按鈕/////////////////////////////////////
		if ((fireman.GetX1() > button2[0][0]) && (fireman.GetX2() < button[2].Left() + button[2].Width()) && (fireman.GetY2() > button2[0][1]) && (fireman.GetY2() < button2[0][1] + button[0].Height() + 10)) {
			isButton = 1;
		}
		else if ((fireman.GetX1() > button2[1][0]) && (fireman.GetX2() < button[1].Left() + button[1].Width()) && (fireman.GetY2() > button2[1][1]) && (fireman.GetY2() < button2[1][1] + button[1].Height() + 10)) {
			isButton = 1;
		}
		else {
			isButton = 0;
		}
		if ((icegirl.GetX1() > button2[0][0]) && (icegirl.GetX2() < button[2].Left() + button[2].Width()) && (icegirl.GetY2() > button2[0][1]) && (icegirl.GetY2() < button2[0][1] + button[0].Height() + 10)) {
			isButton = 1;
		}
		else if ((icegirl.GetX1() > button2[1][0]) && (icegirl.GetX2() < button[1].Left() + button[1].Width()) && (icegirl.GetY2() > button2[1][1]) && (icegirl.GetY2() < button2[1][1] + button[1].Height() + 10)) {
			isButton = 1;
		}
		else {
			isButton = (0 || isButton);
		}
		//////////////////////////////////////////電梯位移/////////////////////////////////////
		if (isButton) {
			if (Velevator[0].Top() >= Velevator2[0][2]) {
				Velevator[0].SetTopLeft(Velevator[0].Left(), Velevator[0].Top()-1);
			}
		}
		else {
			if (Velevator[0].Top() <= Velevator2[0][1]) {
				Velevator[0].SetTopLeft(Velevator[0].Left(), Velevator[0].Top()+1);
			}
		}
		//////////////////////////////////////////判斷鑽石/////////////////////////////////////
		for (int i = 0; i < gameRDiamond[gamenumber-1]; i++) {
			if (fireman.HitRDiamond(RD[i])) {
				if (RD[i].GetExist()) {
					CAudio::Instance()->Play(AUDIO_DIAMOND, false);
					RNUM--;
				}
				RD[i].SetIsExist(0);
			}
		}
		for (int i = 0; i < gameBDiamond[gamenumber-1]; i++) {
			
			if (icegirl.HitBDiamond(BD[i])) {
				if (BD[i].GetExist()) {
					CAudio::Instance()->Play(AUDIO_DIAMOND, false);
					BNUM--;
				}
				BD[i].SetIsExist(0);
			}
		}
		//////////////////////////////////////////過關或失敗/////////////////////////////////////
		if ((fireman.GetX1() + fireman.GetX2()) / 2 > 80 && (fireman.GetX1() + fireman.GetX2()) / 2 < 120 && (fireman.GetY1() + fireman.GetY2()) / 2 > 35 && (fireman.GetY1() + fireman.GetY2()) / 2 < 85) {
			pass = 1;
		}
		else {
			pass = 0;
		}
		if ((icegirl.GetX1() + icegirl.GetX2()) / 2 > 25 && (icegirl.GetX1() + icegirl.GetX2()) / 2 < 65 && (icegirl.GetY1() + icegirl.GetY2()) / 2 > 35 && (icegirl.GetY1() + icegirl.GetY2()) / 2 < 85) {
			pass2 = 1;
		}
		else {
			pass2 = 0;
		}
		if ((((icegirl.GetX1() > 375) && (icegirl.GetX1() < 495)) || ((icegirl.GetX2() > 375) && (icegirl.GetX2() < 495))) && ((icegirl.GetY2() < 420) && (icegirl.GetY2() > 410))) {
			gameover = 0;
			GotoGameState(GAME_STATE_OVER);
		}
		else if ((((fireman.GetX1() > 110) && (fireman.GetX1() < 230)) || ((fireman.GetX2() > 110) && (fireman.GetX2() < 230))) && ((fireman.GetY2() < 420) && (fireman.GetY2() > 410))) {
			gameover = 0;
			GotoGameState(GAME_STATE_OVER);
		}
		else if ((((fireman.GetX1() > 375) && (fireman.GetX1() < 495)) || ((fireman.GetX2() > 375) && (fireman.GetX2() < 495))) && ((fireman.GetY2() < 470) && (fireman.GetY2() > 460))) {
			gameover = 0;
			GotoGameState(GAME_STATE_OVER);
		}
		else if ((((icegirl.GetX1() > 110) && (icegirl.GetX1() < 230)) || ((icegirl.GetX2() > 110) && (icegirl.GetX2() < 230))) && ((icegirl.GetY2() < 470) && (icegirl.GetY2() > 460))) {
			gameover = 0;
			GotoGameState(GAME_STATE_OVER);
		}else if ((((icegirl.GetX1() > 160) && (icegirl.GetX1() < 260)) || ((icegirl.GetX2() > 160) && (icegirl.GetX2() < 260))) && ((icegirl.GetY2() < 255) && (icegirl.GetY2() > 245))) {
			gameover = 0;
			GotoGameState(GAME_STATE_OVER);
		}
		else if ((((fireman.GetX1() > 395) && (fireman.GetX1() < 475)) || ((fireman.GetX2() > 395) && (fireman.GetX2() < 475))) && ((fireman.GetY2() < 255) && (fireman.GetY2() > 245))) {
			gameover = 0;
			GotoGameState(GAME_STATE_OVER);
		}
		else if ((((fireman.GetX1() > 160) && (fireman.GetX1() < 260)) || ((fireman.GetX2() > 160) && (fireman.GetX2() < 260))) && ((fireman.GetY2() < 255) && (fireman.GetY2() > 245))) {
			gameover = 0;
			GotoGameState(GAME_STATE_OVER);
		}
		else if ((((icegirl.GetX1() > 395) && (icegirl.GetX1() < 475)) || ((icegirl.GetX2() > 395) && (icegirl.GetX2() < 475))) && ((icegirl.GetY2() < 255) && (icegirl.GetY2() > 245))) {
			gameover = 0;
			GotoGameState(GAME_STATE_OVER);
		}
	}
	else if (gamenumber == 3) {
	//////////////////////////////////////////判斷火人是否在物件上/////////////////////////////////////
		if (fireman.GetJumpState()) {
			for (i = 0; i < 32; i++) {
				if (fireman.HitCeiling(wall3[i][0], wall3[i][1], wall3[i][2], wall3[i][3])) {
					fireman.SetXY(fireman.GetX1(), wall3[i][3]);
					fireman.SetIsJump(false);
					fireman.Seta(375);
					break;
				}
			}
		}
		for (i = 0; i < 32; i++) {
			if (fireman.GetState() == 3) {
				if (fireman.HitRightWall(wall3[i][0], wall3[i][1], wall3[i][2], wall3[i][3])) {
					fireman.SetXY(wall3[i][2] + 1, fireman.GetY1());
					isWall = true;
					break;
				}
			}
			else if (fireman.GetState() == 2) {
				if (fireman.HitRightWall(wall3[i][0], wall3[i][1], wall3[i][2], wall3[i][3])) {
					fireman.SetXY(wall3[i][0] - (fireman.GetX2() - fireman.GetX1()), fireman.GetY1());
					isWall = true;
					break;
				}
			}
		}
		for (i = 0; i < velenum[gamenumber - 1]; i++) {
			if (fireman.GetState() == 3) {
				if (fireman.HitRightWall(Velevator[i].Left(), Velevator[i].Top(), Velevator[i].Left() + Velevator[i].Width(), Velevator[i].Top() + Velevator[i].Height())) {
					fireman.SetXY(Velevator[i].Left() + Velevator->Width(), fireman.GetY1());
					isWall = true;
					break;
				}
			}
			else if (fireman.GetState() == 2) {
				if (fireman.HitRightWall(Velevator[i].Left(), Velevator[i].Top(), Velevator[i].Left() + Velevator[i].Width(), Velevator[i].Top() + Velevator[i].Height())) {
					fireman.SetXY(Velevator[i].Left() - (fireman.GetX2() - fireman.GetX1()), fireman.GetY1());
					isWall = true;
					break;
				}
			}
		}
		fireman.SetWall(isWall);
		for (i = 0; i < 32; i++) {
			if (fireman.HitLeftWall(wall3[i][0], wall3[i][1], wall3[i][2], wall3[i][3])) {
				fireman.SetXY(fireman.GetX1(), wall3[i][1] - 19);
				isStand = true;
				break;
			}
			else {
				isStand = false;
			}
		}
		bool isele[2] = { 0, 0 };
		int isplayer[2] = { 0,0 };
		for (i = 0; i < delenum[gamenumber - 1]; i++) {
			if (fireman.HitCeiling(Delevator[i].Left(), Delevator[i].Top(), Delevator[i].Left() + Delevator[i].Width(), Delevator[i].Top() + Delevator[i].Height())) {
				fireman.SetXY(fireman.GetX1(), Delevator[i].Top() + Delevator[i].Height());
				fireman.SetIsJump(false);
				fireman.Seta(375);
				break;
			}
			if (fireman.HitLeftWall(Delevator[i].Left(), Delevator[i].Top(), Delevator[i].Left() + Delevator[i].Width(), Delevator[i].Top() + Delevator[i].Height())) {
				fireman.SetXY(fireman.GetX1(), Delevator[i].Top() - 19);
				isStand = true;
				isele[i] = true;
				isplayer[0] = 2;
				break;
			}
			else {
				isele[i] = false;
				isplayer[0] = 0;
				isStand = (false || isStand);
			}

		}
		fireman.SetIsStand(isStand);
		isStand = false;
		isWall = false;
		//////////////////////////////////////////判斷冰人是否在物件上/////////////////////////////////////
		if (icegirl.GetJumpState()) {
			for (i = 0; i < 32; i++) {
				if (icegirl.HitCeiling(wall3[i][0], wall3[i][1], wall3[i][2], wall3[i][3])) {
					icegirl.SetXY(icegirl.GetX1(), wall3[i][3]);
					icegirl.SetIsJump(false);
					icegirl.Seta(375);
					break;
				}
			}
		}
		for (i = 0; i < 32; i++) {
			if (icegirl.GetState() == 3) {
				if (icegirl.HitRightWall(wall3[i][0], wall3[i][1], wall3[i][2], wall3[i][3])) {
					icegirl.SetXY(wall3[i][2] + 1, icegirl.GetY1());
					isWall = true;
					break;
				}
			}
			else if (icegirl.GetState() == 2) {
				if (icegirl.HitRightWall(wall3[i][0], wall3[i][1], wall3[i][2], wall3[i][3])) {
					icegirl.SetXY(wall3[i][0] - (icegirl.GetX2() - icegirl.GetX1()), icegirl.GetY1());
					isWall = true;
					break;
				}
			}
		}
		for (i = 0; i < velenum[gamenumber - 1]; i++) {
			if (icegirl.GetState() == 3) {
				if (icegirl.HitRightWall(Velevator[i].Left(), Velevator[i].Top(), Velevator[i].Left() + Velevator[i].Width(), Velevator[i].Top() + Velevator[i].Height())) {
					icegirl.SetXY(Velevator[i].Left() + Velevator->Width(), icegirl.GetY1());
					isWall = true;
					break;
				}
			}
			else if (icegirl.GetState() == 2) {
				if (icegirl.HitRightWall(Velevator[i].Left(), Velevator[i].Top(), Velevator[i].Left() + Velevator[i].Width(), Velevator[i].Top() + Velevator[i].Height())) {
					icegirl.SetXY(Velevator[i].Left() - (icegirl.GetX2() - icegirl.GetX1()), icegirl.GetY1());
					isWall = true;
					break;
				}
			}
		}
		icegirl.SetWall(isWall);
		for (i = 0; i < 32; i++) {
			if (icegirl.HitLeftWall(wall3[i][0], wall3[i][1], wall3[i][2], wall3[i][3])) {
				icegirl.SetXY(icegirl.GetX1(), wall3[i][1] - 18);
				isStand = true;
				break;
			}
			else {
				isStand = false;
			}
		}
		for (i = 0; i < delenum[gamenumber - 1]; i++) {
			if (icegirl.HitCeiling(Delevator[i].Left(), Delevator[i].Top(), Delevator[i].Left() + Delevator[i].Width(), Delevator[i].Top() + Delevator[i].Height())) {
				icegirl.SetXY(icegirl.GetX1(), Delevator[i].Top() + Delevator[i].Height());
				icegirl.SetIsJump(false);
				icegirl.Seta(375);
				break;
			}
			if (icegirl.HitLeftWall(Delevator[i].Left(), Delevator[i].Top(), Delevator[i].Left() + Delevator[i].Width(), Delevator[i].Top() + Delevator[i].Height())) {
				icegirl.SetXY(icegirl.GetX1(), Delevator[i].Top() - 19);
				isStand = true;
				isele[i] = true;
				isplayer[1] = 2;
				break;
			}
			else {
				isplayer[1] = 0;
				isele[i] = (false || isele[i]);
				isStand = (false || isStand);
			}

		}
		icegirl.SetIsStand(isStand);
		fireman.Jump();
		icegirl.Jump();
		//////////////////////////////////////////判斷按鈕是否在物件上/////////////////////////////////////
		bool isButton = 0;
		if ((fireman.GetX1() > button3[0][0]) && (fireman.GetX2() < button[0].Left() + button[0].Width()) && (fireman.GetY2() > button3[0][1]) && (fireman.GetY2() < button3[0][1] + button[0].Height() + 10)) {
			isButton = 1;
		}
		else {
			isButton = 0;
		}
		if ((icegirl.GetX1() > button3[0][0]) && (icegirl.GetX2() < button[0].Left() + button[0].Width()) && (icegirl.GetY2() > button3[0][1]) && (icegirl.GetY2() < button3[0][1] + button[0].Height() + 10)) {
			isButton = 1;
		}
		else {
			isButton = (0 || isButton);
		}
		//////////////////////////////////////////電梯位移/////////////////////////////////////
		if (isButton) {
			if (Velevator[0].Top() <= Velevator3[0][2]) {
				Velevator[0].SetTopLeft(Velevator[0].Left(), Velevator[0].Top() + 1);
			}
		}
		else {
			if (Velevator[0].Top() >= Velevator3[0][1]) {
				Velevator[0].SetTopLeft(Velevator[0].Left(), Velevator[0].Top() - 1);
			}
		}
		//////////////////////////////////////////判斷操縱桿/////////////////////////////////////
		for (i = 0; i < levernum[gamenumber - 1]; i++) {
			if (fireman.GetState() == 3) {
				if (fireman.HitRightWall(lever3[i][0], lever3[i][1], lever3[i][0] + lever[i].Width(), lever3[i][1] + lever[i].Height())) {
					if (lever[i].GetCurrentBitmapNumber() == 0) {
						lever[i].Movetonum(1);
					}
				}
			}
			else if (fireman.GetState() == 2) {
				if (fireman.HitRightWall(lever3[i][0], lever3[i][1], lever3[i][0] + lever[i].Width(), lever3[i][1] + lever[i].Height())) {
					if (lever[i].GetCurrentBitmapNumber() == 1) {
						lever[i].Movetonum(0);
					}
				}
			}
			if (icegirl.GetState() == 3) {
				if (icegirl.HitRightWall(lever3[i][0], lever3[i][1], lever3[i][0] + lever[i].Width(), lever3[i][1] + lever[i].Height())) {
					if (lever[i].GetCurrentBitmapNumber() == 0) {
						lever[i].Movetonum(1);
					}
				}
			}
			else if (icegirl.GetState() == 2) {
				if (icegirl.HitRightWall(lever3[i][0], lever3[i][1], lever3[i][0] + lever[i].Width(), lever3[i][1] + lever[i].Height())) {
					if (lever[i].GetCurrentBitmapNumber() == 1) {
						lever[i].Movetonum(0);
					}
				}
			}
			if (lever[i].GetCurrentBitmapNumber() == 0) {
				if (Velevator[1].Top() >= Velevator3[1][1]) {
					Velevator[1].SetTopLeft(Velevator[1].Left(), Velevator[1].Top() - 1);
				}
			}
			else if (lever[i].GetCurrentBitmapNumber() == 1) {
				if (Velevator[1].Top() <= Velevator3[1][2]) {
					Velevator[1].SetTopLeft(Velevator[1].Left(), Velevator[1].Top() + 1);
				}
			}
		}
		//////////////////////////////////////////判斷鑽石/////////////////////////////////////
		for (int i = 0; i < gameRDiamond[gamenumber - 1]; i++) {
			if (fireman.HitRDiamond(RD[i])) {
				if (RD[i].GetExist()) {
					CAudio::Instance()->Play(AUDIO_DIAMOND, false);
					RNUM--;
				}
				RD[i].SetIsExist(0);
				
				
			}
		}
		for (int i = 0; i < gameBDiamond[gamenumber - 1]; i++) {
			if (icegirl.HitBDiamond(BD[i])) {
				if (BD[i].GetExist()) {
					CAudio::Instance()->Play(AUDIO_DIAMOND, false);
					BNUM--;
				}
				BD[i].SetIsExist(0);
				
			}
		}
		//////////////////////////////////////////成對電梯位移/////////////////////////////////////
		if (isele[0]) {
			if (Delevator[0].Top() <= 445) {
				if ((Delevator[0].Top() >= 230) && (Delevator[0].Top() <= 450)) {
					Delevator[0].SetTopLeft(Delevator[0].Left(), Delevator[0].Top() + isplayer[0] + isplayer[1]);
					Delevator[1].SetTopLeft(Delevator[1].Left(), Delevator[1].Top() - isplayer[0] - isplayer[1]);
				}
			}
		}
		else if (isele[1]) {
			if (Delevator[0].Top() >= 100) {
				if ((Delevator[1].Top() >= 90) && (Delevator[1].Top() <= 315)) {
					Delevator[1].SetTopLeft(Delevator[1].Left(), Delevator[1].Top() + isplayer[0] + isplayer[1]);
					Delevator[0].SetTopLeft(Delevator[0].Left(), Delevator[0].Top() - isplayer[0] - isplayer[1]);
				}
			}
		}
		//////////////////////////////////////////判斷過關或失敗/////////////////////////////////////
		if ((fireman.GetX1() + fireman.GetX2()) / 2 > 130 && (fireman.GetX1() + fireman.GetX2()) / 2 < 170 && (fireman.GetY1() + fireman.GetY2()) / 2 > 335 && (fireman.GetY1() + fireman.GetY2()) / 2 < 385) {
			pass = 1;
		}
		else {
			pass = 0;
		}
		if ((icegirl.GetX1() + icegirl.GetX2()) / 2 > 80 && (icegirl.GetX1() + icegirl.GetX2()) / 2 < 120 && (icegirl.GetY1() + icegirl.GetY2()) / 2 > 335 && (icegirl.GetY1() + icegirl.GetY2()) / 2 < 385) {
			pass2 = 1;
		}
		else {
			pass2 = 0;
		}
		if ((((icegirl.GetX1() > 195) && (icegirl.GetX1() < 430)) || ((icegirl.GetX2() > 195) && (icegirl.GetX2() < 430))) && ((icegirl.GetY2() < 450) && (icegirl.GetY2() > 440))) {
			gameover = 0;
			GotoGameState(GAME_STATE_OVER);
		}
		else if ((((fireman.GetX1() > 195) && (fireman.GetX1() < 430)) || ((fireman.GetX2() > 195) && (fireman.GetX2() < 430))) && ((fireman.GetY2() < 450) && (fireman.GetY2() > 440))) {
			gameover = 0;
			GotoGameState(GAME_STATE_OVER);
		}
	}
	else if (gamenumber == 4) {
	//////////////////////////////////////////石頭對火人判斷/////////////////////////////////////
		for (i = 0; i < 29; i++) {
			if (Stone.HitLeftWall(wall4[i][0], wall4[i][1], wall4[i][2], wall4[i][3])) {
				Stone.SetXY(Stone.GetX1(), wall4[i][1] - 24);
				isStand = true;
				break;
			}
			else {
				isStand = false;
			}

		}
		for (i = 0; i < 29; i++)
		{
			if (fireman.GetState() == 3) {
				if (Stone.HitRightWall(wall4[i][0], wall4[i][1], wall4[i][2], wall4[i][3])) {
					Stone.SetXY(wall4[i][2] + 1, Stone.GetY1());
					isWall = true;
					break;
				}
			}
			else if (fireman.GetState() == 2) {
				if (Stone.HitRightWall(wall4[i][0], wall4[i][1], wall4[i][2], wall4[i][3])) {
					Stone.SetXY(wall4[i][0] - (Stone.GetX2() - Stone.GetX1()), Stone.GetY1());
					isWall = true;
					break;
				}
			}
		}
		Stone.SetIsStand(isStand);
		Stone.SetWall(isWall);
		isStand = false;
		isWall = false;
		if (fireman.GetState() == 3) {
			if (fireman.HitRightWall(Stone.GetX1(), Stone.GetY1(), Stone.GetX2(), Stone.GetY2())) {
				Stone.SetXY(fireman.GetX1() - 24, Stone.GetY1());
			}
		}
		else if (fireman.GetState() == 2) {
			if (fireman.HitRightWall(Stone.GetX1(), Stone.GetY1(), Stone.GetX2(), Stone.GetY2())) {
				Stone.SetXY(fireman.GetX2(), Stone.GetY1());
			}
		}
		//////////////////////////////////////////判斷火人是否在物件上/////////////////////////////////////
		if (fireman.GetJumpState()) {
			for (i = 0; i < 29; i++) {
				if (fireman.HitCeiling(wall4[i][0], wall4[i][1], wall4[i][2], wall4[i][3])) {
					fireman.SetXY(fireman.GetX1(), wall4[i][3]);
					fireman.SetIsJump(false);
					fireman.Seta(375);
					break;
				}
			}
		}
		for (i = 0; i < 29; i++) {
			if (fireman.GetState() == 3) {
				if (fireman.HitRightWall(wall4[i][0], wall4[i][1], wall4[i][2], wall4[i][3])) {
					fireman.SetXY(wall4[i][2] + 1, fireman.GetY1());
					isWall = true;
					break;
				}
			}
			else if (fireman.GetState() == 2) {
				if (fireman.HitRightWall(wall4[i][0], wall4[i][1], wall4[i][2], wall4[i][3])) {
					fireman.SetXY(wall4[i][0] - (fireman.GetX2() - fireman.GetX1()), fireman.GetY1());
					isWall = true;
					break;
				}
			}
		}
		fireman.SetWall(isWall);
		for (i = 0; i < 29; i++) {
			if (fireman.HitLeftWall(wall4[i][0], wall4[i][1], wall4[i][2], wall4[i][3])) {
				fireman.SetXY(fireman.GetX1(), wall4[i][1] - 19);
				isStand = true;
				break;
			}
			else {
				isStand = false;
			}
		}
		if (fireman.HitLeftWall(Stone.GetX1(), Stone.GetY1(), Stone.GetX2(), Stone.GetY2())) {
			fireman.SetXY(fireman.GetX1(), Stone.GetY1() - 19);
			isStand = true;
		}
		else {
			isStand = (false || isStand);
		}
		fireman.SetIsStand(isStand);
		isStand = false;
		isWall = false;
		//////////////////////////////////////////石頭位移/////////////////////////////////////
		for (i = 0; i < 29; i++) {
			if (Stone.HitLeftWall(wall4[i][0], wall4[i][1], wall4[i][2], wall4[i][3])) {
				Stone.SetXY(Stone.GetX1(), wall4[i][1] - 24);
				isStand = true;
				break;
			}
			else {
				isStand = false;
			}

		}
		for (i = 0; i < 29; i++)
		{
			if (fireman.GetState() == 3) {
				if (Stone.HitRightWall(wall4[i][0], wall4[i][1], wall4[i][2], wall4[i][3])) {
					Stone.SetXY(wall4[i][2] + 1, Stone.GetY1());
					isWall = true;
					break;
				}
			}
			else if (fireman.GetState() == 2) {
				if (Stone.HitRightWall(wall4[i][0], wall4[i][1], wall4[i][2], wall4[i][3])) {
					Stone.SetXY(wall4[i][0] - (Stone.GetX2() - Stone.GetX1()), Stone.GetY1());
					isWall = true;
					break;
				}
			}
		}
		Stone.SetIsStand(isStand);
		Stone.SetWall(isWall);
		isStand = false;
		isWall = false;
		//////////////////////////////////////////石頭對冰人判斷/////////////////////////////////////
		if (icegirl.GetState() == 3) {
			if (icegirl.HitRightWall(Stone.GetX1(), Stone.GetY1(), Stone.GetX2(), Stone.GetY2())) {
				Stone.SetXY(icegirl.GetX1() - 24, Stone.GetY1());
			}
		}
		else if (icegirl.GetState() == 2) {
			if (icegirl.HitRightWall(Stone.GetX1(), Stone.GetY1(), Stone.GetX2(), Stone.GetY2())) {
				Stone.SetXY(icegirl.GetX2(), Stone.GetY1());
			}
		}
		//////////////////////////////////////////判斷冰人是否在物件上/////////////////////////////////////
		if (icegirl.GetJumpState()) {
			for (i = 0; i < 29; i++) {
				if (icegirl.HitCeiling(wall4[i][0], wall4[i][1], wall4[i][2], wall4[i][3])) {
					icegirl.SetXY(icegirl.GetX1(), wall4[i][3]);
					icegirl.SetIsJump(false);
					icegirl.Seta(375);
					break;
				}
			}
		}
		for (i = 0; i < 29; i++) {
			if (icegirl.GetState() == 3) {
				if (icegirl.HitRightWall(wall4[i][0], wall4[i][1], wall4[i][2], wall4[i][3])) {
					icegirl.SetXY(wall4[i][2] + 1, icegirl.GetY1());
					isWall = true;
					break;
				}
			}
			else if (icegirl.GetState() == 2) {
				if (icegirl.HitRightWall(wall4[i][0], wall4[i][1], wall4[i][2], wall4[i][3])) {
					icegirl.SetXY(wall4[i][0] - (icegirl.GetX2() - icegirl.GetX1()), icegirl.GetY1());
					isWall = true;
					break;
				}
			}
		}
		icegirl.SetWall(isWall);
		for (i = 0; i < 29; i++) {
			if (icegirl.HitLeftWall(wall4[i][0], wall4[i][1], wall4[i][2], wall4[i][3])) {
				icegirl.SetXY(icegirl.GetX1(), wall4[i][1] - 18);
				isStand = true;
				break;
			}
			else {
				isStand = false;
			}
		}
		icegirl.SetIsStand(isStand);
		fireman.Jump();
		icegirl.Jump();
		//////////////////////////////////////////電風扇影響玩家/////////////////////////////////////
		if ((fireman.GetX1() < 60) && (fireman.GetX2() > 10) && (fireman.GetY2() > 150) && (fireman.GetY2() < 345)) {
			fireman.SetXY(fireman.GetX1(), fireman.GetY1() - 9);
		}
		if ((icegirl.GetX1() < 60) && (icegirl.GetX2() > 10) && (icegirl.GetY2() > 150) && (icegirl.GetY2() < 345)) {
			icegirl.SetXY(icegirl.GetX1(), icegirl.GetY1() - 9);
		}
		//////////////////////////////////////////判斷鑽石/////////////////////////////////////
		for (int i = 0; i < gameRDiamond[gamenumber - 1]; i++) {
			if (fireman.HitRDiamond(RD[i])) {
				if (RD[i].GetExist()) {
					CAudio::Instance()->Play(AUDIO_DIAMOND, false);
					RNUM--;
				}
				RD[i].SetIsExist(0);
				
			}
		}
		for (int i = 0; i < gameBDiamond[gamenumber - 1]; i++) {
			if (icegirl.HitBDiamond(BD[i])) {
				if (BD[i].GetExist()) {
					CAudio::Instance()->Play(AUDIO_DIAMOND, false);
					BNUM--;
				}
				BD[i].SetIsExist(0);
				
			}
		}
		//////////////////////////////////////////過關或失敗/////////////////////////////////////
		if ((fireman.GetX1() + fireman.GetX2()) / 2 > 75 && (fireman.GetX1() + fireman.GetX2()) / 2 < 115 && (fireman.GetY1() + fireman.GetY2()) / 2 > 80 && (fireman.GetY1() + fireman.GetY2()) / 2 < 130) {
			pass = 1;
		}
		else {
			pass = 0;
		}
		if ((icegirl.GetX1() + icegirl.GetX2()) / 2 > 25 && (icegirl.GetX1() + icegirl.GetX2()) / 2 < 65 && (icegirl.GetY1() + icegirl.GetY2()) / 2 > 80 && (icegirl.GetY1() + icegirl.GetY2()) / 2 < 130) {
			pass2 = 1;
		}
		else {
			pass2 = 0;
		}
		if ((((icegirl.GetX1() > 130) && (icegirl.GetX1() < 595)) || ((icegirl.GetX2() > 130) && (icegirl.GetX2() < 595))) && ((icegirl.GetY2() < 455) && (icegirl.GetY2() > 445))) {
			gameover = 0;
			GotoGameState(GAME_STATE_OVER);
		}
		else if ((((fireman.GetX1() > 130) && (fireman.GetX1() < 595)) || ((fireman.GetX2() > 130) && (fireman.GetX2() < 595))) && ((fireman.GetY2() < 455) && (fireman.GetY2() > 445))) {
			gameover = 0;
			GotoGameState(GAME_STATE_OVER);
		}
	}
	else if (gamenumber == 5) {				//第五關
		//////////////////////////////////////////判斷火人是否在物件上/////////////////////////////////////
		if (fireman.GetJumpState()) {
			for (i = 0; i < 27; i++) {
				if (fireman.HitCeiling(wall5[i][0], wall5[i][1], wall5[i][2], wall5[i][3])) {
					fireman.SetXY(fireman.GetX1(), wall5[i][3]);
					fireman.SetIsJump(false);
					fireman.Seta(375);
					break;
				}
			}
		}
		for (i = 0; i < 27; i++) {
			if (fireman.GetState() == 3) {
				if (fireman.HitRightWall(wall5[i][0], wall5[i][1], wall5[i][2], wall5[i][3])) {
					fireman.SetXY(wall5[i][2] + 1, fireman.GetY1());
					isWall = true;
					break;
				}
			}
			else if (fireman.GetState() == 2) {
				if (fireman.HitRightWall(wall5[i][0], wall5[i][1], wall5[i][2], wall5[i][3])) {
					fireman.SetXY(wall5[i][0] - (fireman.GetX2() - fireman.GetX1()), fireman.GetY1());
					isWall = true;
					break;
				}
			}
		}
		fireman.SetWall(isWall);
		for (i = 0; i < 27; i++) {
			if (fireman.HitLeftWall(wall5[i][0], wall5[i][1], wall5[i][2], wall5[i][3])) {
				fireman.SetXY(fireman.GetX1(), wall5[i][1] - 19);
				isStand = true;
				break;
			}
			else {
				isStand = false;
			}
		}
		for (i = 0; i < elenum[gamenumber - 1]; i++) {
			if (fireman.HitCeiling(elevator[i].Left(), elevator[i].Top(), elevator[i].Left() + elevator[i].Width(), elevator[i].Top() + elevator[i].Height())) {
				fireman.SetXY(fireman.GetX1(), elevator[i].Top() + elevator[i].Height());
				fireman.SetIsJump(false);
				fireman.Seta(375);
				break;
			}
			if (fireman.HitLeftWall(elevator[i].Left(), elevator[i].Top(), elevator[i].Left() + elevator[i].Width(), elevator[i].Top() + elevator[i].Height())) {
				fireman.SetXY(fireman.GetX1(), elevator[i].Top() - 19);
				isStand = true;
				break;
			}
			else {
				isStand = (false || isStand);
			}
		}
		bool isele[2] = { 0, 0};
		int isplayer[2] = { 0,0 };
		for (i = 0; i < delenum[gamenumber - 1]; i++) {
			if (fireman.HitCeiling(Delevator[i].Left(), Delevator[i].Top(), Delevator[i].Left() + Delevator[i].Width(), Delevator[i].Top() + Delevator[i].Height())) {
				fireman.SetXY(fireman.GetX1(), Delevator[i].Top() + Delevator[i].Height());
				fireman.SetIsJump(false);
				fireman.Seta(375);
				break;
			}
			if (fireman.HitLeftWall(Delevator[i].Left(), Delevator[i].Top(), Delevator[i].Left() + Delevator[i].Width(), Delevator[i].Top() + Delevator[i].Height())) {
				fireman.SetXY(fireman.GetX1(), Delevator[i].Top() - 19);
				isStand = true;
				isele[i] = true;
				isplayer[0] = 2;
				break;
			}
			else {
				isele[i] = false;
				isplayer[0] = 0;
				isStand = (false || isStand);
			}

		}
		fireman.SetIsStand(isStand);

		isStand = false;
		isWall = false;
		//////////////////////////////////////////判斷冰人是否在物件上/////////////////////////////////////
		if (icegirl.GetJumpState()) {
			for (i = 0; i < 27; i++) {
				if (icegirl.HitCeiling(wall5[i][0], wall5[i][1], wall5[i][2], wall5[i][3])) {
					icegirl.SetXY(icegirl.GetX1(), wall5[i][3]);
					icegirl.SetIsJump(false);
					icegirl.Seta(375);
					break;
				}
			}
		}
		for (i = 0; i < 27; i++) {
			if (icegirl.GetState() == 3) {
				if (icegirl.HitRightWall(wall5[i][0], wall5[i][1], wall5[i][2], wall5[i][3])) {
					icegirl.SetXY(wall5[i][2] + 1, icegirl.GetY1());
					isWall = true;
					break;
				}
			}
			else if (icegirl.GetState() == 2) {
				if (icegirl.HitRightWall(wall5[i][0], wall5[i][1], wall5[i][2], wall5[i][3])) {
					icegirl.SetXY(wall5[i][0] - (icegirl.GetX2() - icegirl.GetX1()), icegirl.GetY1());
					isWall = true;
					break;
				}
			}
		}
		icegirl.SetWall(isWall);
		for (i = 0; i < 27; i++) {
			if (icegirl.HitLeftWall(wall5[i][0], wall5[i][1], wall5[i][2], wall5[i][3])) {
				icegirl.SetXY(icegirl.GetX1(), wall5[i][1] - 18);
				isStand = true;
				break;
			}
			else {
				isStand = false;
			}
		}
		for (i = 0; i < elenum[gamenumber - 1]; i++) {
			if (icegirl.HitCeiling(elevator[i].Left(), elevator[i].Top(), elevator[i].Left() + elevator[i].Width(), elevator[i].Top() + elevator[i].Height())) {
				icegirl.SetXY(icegirl.GetX1(), elevator[i].Top() + elevator[i].Height());
				icegirl.SetIsJump(false);
				icegirl.Seta(375);
				break;
			}
			if (icegirl.HitLeftWall(elevator[i].Left(), elevator[i].Top(), elevator[i].Left() + elevator[i].Width(), elevator[i].Top() + elevator[i].Height())) {
				icegirl.SetXY(icegirl.GetX1(), elevator[i].Top() - 19);
				isStand = true;
				break;
			}
			else {
				isStand = (false || isStand);
			}
		}
		for (i = 0; i < delenum[gamenumber - 1]; i++) {
			if (icegirl.HitCeiling(Delevator[i].Left(), Delevator[i].Top(), Delevator[i].Left() + Delevator[i].Width(), Delevator[i].Top() + Delevator[i].Height())) {
				icegirl.SetXY(icegirl.GetX1(), Delevator[i].Top() + Delevator[i].Height());
				icegirl.SetIsJump(false);
				icegirl.Seta(375);
				break;
			}
			if (icegirl.HitLeftWall(Delevator[i].Left(), Delevator[i].Top(), Delevator[i].Left() + Delevator[i].Width(), Delevator[i].Top() + Delevator[i].Height())) {
				icegirl.SetXY(icegirl.GetX1(), Delevator[i].Top() - 19);
				isStand = true;
				isele[i] = true;
				isplayer[1] = 2;
				break;
			}
			else {
				isplayer[1] = 0;
				isele[i] = (false || isele[i]);
				isStand = (false || isStand);
			}

		}
		icegirl.SetIsStand(isStand);

		fireman.Jump();
		icegirl.Jump();
		//////////////////////////////////////////判斷操縱桿/////////////////////////////////////
		for (i = 0; i < levernum[gamenumber - 1]; i++) {
			if (fireman.GetState() == 3) {
				if (fireman.HitRightWall(lever5[i][0], lever5[i][1]-5, lever5[i][0] + lever[i].Width(), lever5[i][1] + lever[i].Height())) {
					if (lever[i].GetCurrentBitmapNumber() == 0) {
						lever[i].Movetonum(1);
					}
				}
			}
			else if (fireman.GetState() == 2) {
				if (fireman.HitRightWall(lever5[i][0], lever5[i][1] -5, lever5[i][0] + lever[i].Width(), lever5[i][1] + lever[i].Height())) {
					if (lever[i].GetCurrentBitmapNumber() == 1) {
						lever[i].Movetonum(0);
					}
				}
			}
			if (icegirl.GetState() == 3) {
				if (icegirl.HitRightWall(lever5[i][0], lever5[i][1] -5, lever5[i][0] + lever[i].Width(), lever5[i][1] + lever[i].Height())) {
					if (lever[i].GetCurrentBitmapNumber() == 0) {
						lever[i].Movetonum(1);
					}
				}
			}
			else if (icegirl.GetState() == 2) {
				if (icegirl.HitRightWall(lever5[i][0], lever5[i][1] -5, lever5[i][0] + lever[i].Width(), lever5[i][1] + lever[i].Height())) {
					if (lever[i].GetCurrentBitmapNumber() == 1) {
						lever[i].Movetonum(0);
					}
				}
			}
		}
		//////////////////////////////////////////電梯位移/////////////////////////////////////
		if (lever[0].GetCurrentBitmapNumber() == 0) {
			if (elevator[0].Left() >= elevator5[0][0]) {
				elevator[0].SetTopLeft(elevator[0].Left()-1, elevator[0].Top());
			}
		}
		else if (lever[0].GetCurrentBitmapNumber() == 1) {
			if (elevator[0].Left() <= elevator5[0][2]) {
				elevator[0].SetTopLeft(elevator[0].Left()+1, elevator[0].Top());
			}
		}
		if (lever[1].GetCurrentBitmapNumber() == 0) {
			if (elevator[1].Left() <= elevator5[1][0]) {
				elevator[1].SetTopLeft(elevator[1].Left() + 1, elevator[1].Top());
			}
		}
		else if (lever[1].GetCurrentBitmapNumber() == 1) {
			
			if (elevator[1].Left() >= elevator5[1][2]) {
				elevator[1].SetTopLeft(elevator[1].Left() - 1, elevator[1].Top());
			}
		}
		if (lever[2].GetCurrentBitmapNumber() == 0) {
			if (elevator[2].Left() >= elevator5[2][0]) {
				elevator[2].SetTopLeft(elevator[2].Left() - 1, elevator[2].Top());
			}
		}
		else if (lever[2].GetCurrentBitmapNumber() == 1) {
			if (elevator[2].Left() <= elevator5[2][2]) {
				elevator[2].SetTopLeft(elevator[2].Left() + 1, elevator[2].Top());
			}
		}
		//////////////////////////////////////////判斷鑽石/////////////////////////////////////
		for (int i = 0; i < gameRDiamond[gamenumber - 1]; i++) {
			if (fireman.HitRDiamond(RD[i])) {
				if (RD[i].GetExist()) {
					CAudio::Instance()->Play(AUDIO_DIAMOND, false);
					RNUM--;
				}
				RD[i].SetIsExist(0);
				
			}
		}
		for (int i = 0; i < gameBDiamond[gamenumber - 1]; i++) {
			if (icegirl.HitBDiamond(BD[i])) {
				if (BD[i].GetExist()) {
					CAudio::Instance()->Play(AUDIO_DIAMOND, false);
					BNUM--;
				}
				BD[i].SetIsExist(0);
				
			}
		}
		//////////////////////////////////////////成對電梯位移/////////////////////////////////////
		if (isele[0]) {
			if ((Delevator[0].Top() >= 90) && (Delevator[0].Top() <= 460)) {
				Delevator[0].SetTopLeft(Delevator[0].Left(),Delevator[0].Top() + isplayer[0]+isplayer[1]);
				Delevator[1].SetTopLeft(Delevator[1].Left(), Delevator[1].Top() - isplayer[0] - isplayer[1]);
			}
		}
		else if (isele[1]) {
			if ((Delevator[1].Top() >= 90) && (Delevator[1].Top() <= 460)) {
				Delevator[1].SetTopLeft(Delevator[1].Left(), Delevator[1].Top() + isplayer[0] + isplayer[1]);
				Delevator[0].SetTopLeft(Delevator[0].Left(), Delevator[0].Top() - isplayer[0] - isplayer[1]);
			}
		}
		//////////////////////////////////////////過關或失敗/////////////////////////////////////
		if ((fireman.GetX1() + fireman.GetX2()) / 2 > 130 && (fireman.GetX1() + fireman.GetX2()) / 2 < 170 && (fireman.GetY1() + fireman.GetY2()) / 2 > 235 && (fireman.GetY1() + fireman.GetY2()) / 2 < 285) {
			pass = 1;
		}
		else {
			pass = 0;
		}
		if ((icegirl.GetX1() + icegirl.GetX2()) / 2 > 475 && (icegirl.GetX1() + icegirl.GetX2()) / 2 < 515 && (icegirl.GetY1() + icegirl.GetY2()) / 2 > 235 && (icegirl.GetY1() + icegirl.GetY2()) / 2 < 285) {
			pass2 = 1;
		}
		else {
			pass2 = 0;
		}
		if ((((icegirl.GetX1() > 25) && (icegirl.GetX1() < 165)) || ((icegirl.GetX2() > 25) && (icegirl.GetX2() < 165))) && ((icegirl.GetY2() < 450) && (icegirl.GetY2() > 440))) {
			gameover = 0;
			GotoGameState(GAME_STATE_OVER);
		}
		else if ((((fireman.GetX1() > 475) && (fireman.GetX1() < 640)) || ((fireman.GetX2() > 475) && (fireman.GetX2() < 640))) && ((fireman.GetY2() < 450) && (fireman.GetY2() > 440))) {
			gameover = 0;
			GotoGameState(GAME_STATE_OVER);
		}
		else if ((((fireman.GetX1() > 125) && (fireman.GetX1() < 215)) || ((fireman.GetX2() > 125) && (fireman.GetX2() < 215))) && ((fireman.GetY2() < 70) && (fireman.GetY2() > 60))) {
			gameover = 0;
			GotoGameState(GAME_STATE_OVER);
		}
		else if ((((icegirl.GetX1() > 425) && (icegirl.GetX1() < 510)) || ((icegirl.GetX2() > 425) && (icegirl.GetX2() < 510))) && ((icegirl.GetY2() < 70) && (icegirl.GetY2() > 60))) {
			gameover = 0;
			GotoGameState(GAME_STATE_OVER);
		}
	}
	//////////////////////////////////////////過關/////////////////////////////////////
	if (pass == 1 && pass2 == 1) {
		passAll = 1;
		gameover = 1;
		GotoGameState(GAME_STATE_OVER);
	}
	else {
		gameover = 0;
	}

}

void CGameStateRun::OnInit()  								// 遊戲的初值及圖形設定
{
	// 當圖很多時，OnInit載入所有的圖要花很多時間。為避免玩遊戲的人
	//     等的不耐煩，遊戲會出現「Loading ...」，顯示Loading的進度。
	ShowInitProgress(33);	// 接個前一個狀態的進度，此處進度視為33%
	// 開始載入資料
	background.AddBitmap(IDB_BACKGROUND1);
	background.AddBitmap(IDB_BACKGROUND2);
	background.AddBitmap(IDB_BACKGROUND3);
	background.AddBitmap(IDB_BACKGROUND4);
	background.AddBitmap(IDB_BACKGROUND5);
	BDoor.AddBitmap(IDB_BDOOR);
	RDoor.AddBitmap(IDB_RDOOR);
	Stone.LoadBitmap();
	fireman.Setplayer(1);
	icegirl.Setplayer(0);
	fireman.LoadBitmap();
	icegirl.LoadBitmap();
	fan.LoadBitmap(IDB_FAN,RGB(255,255,255));
	// 完成部分Loading動作，提高進度
	ShowInitProgress(50);					
	///////////////////////////////初始化音樂/////////////////////////////////////////////////
	CAudio::Instance()->Load(AUDIO_DEATH,  "Sounds\\Death.mp3");	
	CAudio::Instance()->Load(AUDIO_DIAMOND,  "Sounds\\Diamond.mp3");	
	CAudio::Instance()->Load(AUDIO_BJUMP,  "Sounds\\Jump_blue.mp3");
	CAudio::Instance()->Load(AUDIO_RJUMP, "Sounds\\Jump_red.mp3");
	CAudio::Instance()->Load(AUDIO_BGM, "Sounds\\LevelMusic.mp3");
	CAudio::Instance()->Load(AUDIO_OVER, "Sounds\\LevelMusicOver.mp3");
	CAudio::Instance()->Load(AUDIO_MENU, "Sounds\\MenuMusic.mp3");
	///////////////////////////////初始化音樂/////////////////////////////////////////////////
	// 此OnInit動作會接到CGameStaterOver::OnInit()，所以進度還沒到100%
}
void CGameStateRun::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	const char KEY_LEFT  = 0x25; // keyboard左箭頭
	const char KEY_UP    = 0x26; // keyboard上箭頭
	const char KEY_RIGHT = 0x27; // keyboard右箭頭
	const char KEY_DOWN  = 0x28; // keyboard下箭頭
	const char KEY_CTRL = 0x11;
	const char KEY_P = 0x50;
	const char KEY_A = 0x41;
	const char KEY_D = 0x44;
	const char KEY_S = 0x53;
	const char KEY_W = 0x57;
	if (nChar == KEY_LEFT)
		fireman.SetMovingLeft(true);
	if (nChar == KEY_RIGHT)
		fireman.SetMovingRight(true);
	if (nChar == KEY_UP) {
		CAudio::Instance()->Play(AUDIO_RJUMP, false);
		fireman.SetMovingUp(true);
	}
	if (nChar == KEY_DOWN)
		fireman.SetMovingDown(true);
	if (nChar == KEY_A)
		icegirl.SetMovingLeft(true);
	if (nChar == KEY_D)
		icegirl.SetMovingRight(true);
	if (nChar == KEY_W) {
		CAudio::Instance()->Play(AUDIO_BJUMP, false);
		icegirl.SetMovingUp(true);
	}
	if (nChar == KEY_S)
		icegirl.SetMovingDown(true);
	if (nChar == KEY_CTRL) {				//密技
		if (gamenumber == 1) {
			fireman.SetXY(500, 55);
			icegirl.SetXY(560, 55);
		}
		else if (gamenumber == 2) {
			fireman.SetXY(80, 35);
			icegirl.SetXY(25, 35);
		}
		else if (gamenumber == 3) {
			fireman.SetXY(130, 335);
			icegirl.SetXY(80, 335);
		}
		else if (gamenumber == 4) {
			fireman.SetXY(75, 80);
			icegirl.SetXY(25, 80);
		}
		else if (gamenumber == 5) {
			fireman.SetXY(130, 235);
			icegirl.SetXY(475, 235);
		}
	}
}
void CGameStateRun::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	const char KEY_LEFT  = 0x25; // keyboard左箭頭
	const char KEY_UP    = 0x26; // keyboard上箭頭
	const char KEY_RIGHT = 0x27; // keyboard右箭頭
	const char KEY_DOWN  = 0x28; // keyboard下箭頭
	const char KEY_A = 0x41;
	const char KEY_D = 0x44;
	const char KEY_S = 0x53;
	const char KEY_W = 0x57;
	if (nChar == KEY_LEFT)
		fireman.SetMovingLeft(false);
	if (nChar == KEY_RIGHT)
		fireman.SetMovingRight(false);
	if (nChar == KEY_UP)
		fireman.SetMovingUp(false);
	if (nChar == KEY_DOWN)
		fireman.SetMovingDown(false);
	if (nChar == KEY_A)
		icegirl.SetMovingLeft(false);
	if (nChar == KEY_D)
		icegirl.SetMovingRight(false);
	if (nChar == KEY_W)
		icegirl.SetMovingUp(false);
	if (nChar == KEY_S)
		icegirl.SetMovingDown(false);
}
void CGameStateRun::OnLButtonDown(UINT nFlags, CPoint point)  // 處理滑鼠的動作
{
}
void CGameStateRun::OnLButtonUp(UINT nFlags, CPoint point)	// 處理滑鼠的動作
{
}
void CGameStateRun::OnMouseMove(UINT nFlags, CPoint point)	// 處理滑鼠的動作
{
}
void CGameStateRun::OnRButtonDown(UINT nFlags, CPoint point)  // 處理滑鼠的動作
{
}
void CGameStateRun::OnRButtonUp(UINT nFlags, CPoint point)	// 處理滑鼠的動作
{
}
void CGameStateRun::OnShow()
{
	background.OnShow();
	//////////////////////////////////////////對應關卡OnShow物件/////////////////////////////////////
	if (gamenumber == 1) {
		Stone.OnShow();
		for (int i = 0; i < elenum[gamenumber - 1]; i++) {
			elevator[i].ShowBitmap();
		}
		for (int i = 0; i < buttonnum[gamenumber - 1]; i++) {
			button[i].ShowBitmap();
		}
		for (int i = 0; i < levernum[gamenumber - 1]; i++) {
			lever[i].OnShow();
		}
		for (int i = 0; i < gameRDiamond[gamenumber-1]; i++) {
			RD[i].OnShow();
		}
		for (int i = 0; i < gameBDiamond[gamenumber-1]; i++) {
			BD[i].OnShow();
		}
	}
	else if (gamenumber == 2) {
		for (int i = 0; i < elenum[gamenumber - 1]; i++) {
			elevator[i].ShowBitmap();
		}
		for (int i = 0; i < buttonnum[gamenumber - 1]; i++) {
			button[i].ShowBitmap();
		}
		for (int i = 0; i < velenum[gamenumber - 1]; i++) {
			Velevator[i].ShowBitmap();
		}
		for (int i = 0; i < gameRDiamond[gamenumber - 1]; i++) {
			RD[i].OnShow();
		}
		for (int i = 0; i < gameBDiamond[gamenumber - 1]; i++) {
			BD[i].OnShow();
		}
	}
	else if (gamenumber == 3) {
		for (int i = 0; i < velenum[gamenumber - 1]; i++) {
			Velevator[i].ShowBitmap();
		}
		for (int i = 0; i < buttonnum[gamenumber - 1]; i++) {
			button[i].ShowBitmap();
		}
		for (int i = 0; i < levernum[gamenumber - 1]; i++) {
			lever[i].OnShow();
		}
		for (int i = 0; i < delenum[gamenumber - 1]; i++) {
			Delevator[i].ShowBitmap();
		}
		for (int i = 0; i < gameRDiamond[gamenumber - 1]; i++) {
			RD[i].OnShow();
		}
		for (int i = 0; i < gameBDiamond[gamenumber - 1]; i++) {
			BD[i].OnShow();
		}
	}
	else if (gamenumber == 4) {
		fan.ShowBitmap();
		Stone.OnShow();
		for (int i = 0; i < gameRDiamond[gamenumber - 1]; i++) {
			RD[i].OnShow();
		}
		for (int i = 0; i < gameBDiamond[gamenumber - 1]; i++) {
			BD[i].OnShow();
		}
	}
	else if (gamenumber == 5) {
		for (int i = 0; i < elenum[gamenumber - 1]; i++) {
			elevator[i].ShowBitmap();
		}
		for (int i = 0; i < levernum[gamenumber - 1]; i++) {
			lever[i].OnShow();
		}
		for (int i = 0; i < delenum[gamenumber - 1]; i++) {
			Delevator[i].ShowBitmap();
		}
		for (int i = 0; i < gameRDiamond[gamenumber - 1]; i++) {
			RD[i].OnShow();
		}
		for (int i = 0; i < gameBDiamond[gamenumber - 1]; i++) {
			BD[i].OnShow();
		}
	}
	RDoor.OnShow();
	BDoor.OnShow();
	fireman.OnShow();
	icegirl.OnShow();
}
}