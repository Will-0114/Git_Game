
namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// 這個class提供可以用鍵盤或滑鼠控制的擦子
	// 看懂就可以改寫成自己的程式了
	/////////////////////////////////////////////////////////////////////////////
	class CStone
	{
	public:
		CStone();
		//bool HitWall(CWall *wall);
		int  GetX1();					// 擦子左上角 x 座標
		int  GetY1();					// 擦子左上角 y 座標
		int  GetX2();					// 擦子右下角 x 座標
		int  GetY2();					// 擦子右下角 y 座標
		void Initialize();				// 設定擦子為初始值
		void LoadBitmap();				// 載入圖形
		void OnMove();					// 移動擦子
		void OnShow();					// 將擦子圖形貼到畫面
		void SetXY(int nx, int ny);		// 設定擦子左上角座標
		void OnFloor();
		void SetIsStand(bool stand);	
		bool HitLeftWall(int tx1, int ty1, int tx2, int ty2);
		bool HitRightWall(int tx1, int ty1, int tx2, int ty2);
		bool StandFloor(int tx1, int ty1, int tx2, int ty2);
		bool HitCeiling(int tx1, int ty1, int tx2, int ty2);
		void SetWall(bool wall);

	protected:
		CAnimation animation;		// 擦子的動畫
		int x1, y1;					// 擦子左上角座標
		int x2, y2;
		int a;
		int k;
		int floor;
		bool isWall;
		bool isStand;
	private:

	};
}