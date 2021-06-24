#ifndef CRDIAMOND_H
#define CRDIAMOND_H
#endif
namespace game_framework {
	class CRDiamond {
	public:
		CRDiamond();
		int GetX1();
		int GetY1();
		int GetX2();
		int GetY2();
		void Initialize();
		void LoadBitmap();
		void OnShow();
		int GetExist();
		void SetIsExist(bool n);
		void SetXY(int nx, int ny);
	protected:
		CMovingBitmap Diamond;
		bool isExist;
		int x1, y1;
		int x2, y2;
	};
}
