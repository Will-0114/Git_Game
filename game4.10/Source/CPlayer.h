#include "CRDiamond.h"
#include "CBDiamond.h"
namespace game_framework {
	class CPlayer
	{
	public:
		CPlayer();
		//bool HitWall(CWall *wall);
		int  GetX1();					// 擦子左上角 x 座標
		int  GetY1();					// 擦子左上角 y 座標
		int  GetX2();					// 擦子右下角 x 座標
		int  GetY2();					// 擦子右下角 y 座標
		void Initialize();				// 設定擦子為初始值
		void LoadBitmap();				// 載入圖形
		void OnMove();					// 移動擦子
		void OnShow();					// 將擦子圖形貼到畫面
		void SetMovingDown(bool flag);	// 設定是否正在往下移動
		void SetMovingLeft(bool flag);	// 設定是否正在往左移動
		void SetMovingRight(bool flag); // 設定是否正在往右移動
		void SetMovingUp(bool flag);	// 設定是否正在往上移動
		void SetXY(int nx, int ny);		// 設定擦子左上角座標
		void OnFloor();
		void Jump();
		void SetIsStand(bool stand);
		void Setplayer(int a);
		bool HitLeftWall(int tx1, int ty1, int tx2, int ty2);
		bool HitRightWall(int tx1, int ty1, int tx2, int ty2);
		void Seta(int na);
		bool StandFloor(int tx1, int ty1, int tx2, int ty2);
		bool HitCeiling(int tx1, int ty1, int tx2, int ty2);
		void SetIsJump(bool jump);
		bool GetJumpState();
		int GetState();
		void SetWall(bool wall);
		void SetFloor(int _floor);
		bool HitBDiamond(CBDiamond  BDiamond);
		bool HitRDiamond(CRDiamond  RDiamond);
	protected:
		CAnimation animation;		// 擦子的動畫
		int x1, y1;					// 擦子左上角座標
		int x2, y2;
		int a;
		int k;
		int floor;
		bool isplayer;  
		bool isWall;
		bool isMovingDown;			// 是否正在往下移動
		bool isMovingLeft;			// 是否正在往左移動
		bool isMovingRight;			// 是否正在往右移動
		bool isMovingUp;			// 是否正在往上移動
		bool isStand;
		bool isJump;
	private:
	};
}