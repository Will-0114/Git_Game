#include "CRDiamond.h"
#include "CBDiamond.h"
namespace game_framework {
	class CPlayer
	{
	public:
		CPlayer();
		//bool HitWall(CWall *wall);
		int  GetX1();					// ���l���W�� x �y��
		int  GetY1();					// ���l���W�� y �y��
		int  GetX2();					// ���l�k�U�� x �y��
		int  GetY2();					// ���l�k�U�� y �y��
		void Initialize();				// �]�w���l����l��
		void LoadBitmap();				// ���J�ϧ�
		void OnMove();					// �������l
		void OnShow();					// �N���l�ϧζK��e��
		void SetMovingDown(bool flag);	// �]�w�O�_���b���U����
		void SetMovingLeft(bool flag);	// �]�w�O�_���b��������
		void SetMovingRight(bool flag); // �]�w�O�_���b���k����
		void SetMovingUp(bool flag);	// �]�w�O�_���b���W����
		void SetXY(int nx, int ny);		// �]�w���l���W���y��
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
		CAnimation animation;		// ���l���ʵe
		int x1, y1;					// ���l���W���y��
		int x2, y2;
		int a;
		int k;
		int floor;
		bool isplayer;  
		bool isWall;
		bool isMovingDown;			// �O�_���b���U����
		bool isMovingLeft;			// �O�_���b��������
		bool isMovingRight;			// �O�_���b���k����
		bool isMovingUp;			// �O�_���b���W����
		bool isStand;
		bool isJump;
	private:
	};
}