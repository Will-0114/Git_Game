
namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// �o��class���ѥi�H����L�ηƹ�������l
	// �����N�i�H��g���ۤv���{���F
	/////////////////////////////////////////////////////////////////////////////
	class CStone
	{
	public:
		CStone();
		//bool HitWall(CWall *wall);
		int  GetX1();					// ���l���W�� x �y��
		int  GetY1();					// ���l���W�� y �y��
		int  GetX2();					// ���l�k�U�� x �y��
		int  GetY2();					// ���l�k�U�� y �y��
		void Initialize();				// �]�w���l����l��
		void LoadBitmap();				// ���J�ϧ�
		void OnMove();					// �������l
		void OnShow();					// �N���l�ϧζK��e��
		void SetXY(int nx, int ny);		// �]�w���l���W���y��
		void OnFloor();
		void SetIsStand(bool stand);	
		bool HitLeftWall(int tx1, int ty1, int tx2, int ty2);
		bool HitRightWall(int tx1, int ty1, int tx2, int ty2);
		bool StandFloor(int tx1, int ty1, int tx2, int ty2);
		bool HitCeiling(int tx1, int ty1, int tx2, int ty2);
		void SetWall(bool wall);

	protected:
		CAnimation animation;		// ���l���ʵe
		int x1, y1;					// ���l���W���y��
		int x2, y2;
		int a;
		int k;
		int floor;
		bool isWall;
		bool isStand;
	private:

	};
}