#include "stdafx.h"

Monster::Monster(){};
Monster::Monster(const long x, const long y, const SIZE size, const int type){
	cp.x = x;			cp.y = y;
	ObjectSize = size;
	monsterType = type;
	ObjectRect.left = x - size.cx / 2;
	ObjectRect.top = y - size.cy / 2;
	ObjectRect.right = x + size.cx / 2;
	ObjectRect.bottom = y + size.cy / 2;

	monsterType = type;
};
Monster::~Monster(){};

void Monster::draw(){
	HBITMAP hBitmap;									//이미지를 가져오기 위한 hBitmap;							//추가된 변수
	BITMAP bmp;											//이미지의 크기를 알기 위한 bmp;							//추가된 변수
	int mWidth, mHeight;								//이미지의 크기를 저장하기 위한  mWidth, mHeight;;		//추가된 변수
	HDC memdc;											//이미지를 임시저장하기 위한 memdc;						//추가된 변수

	static int BodyDrawCnt = 0;									//몇번 불러진 지를 체크하기 위한 Cnt;
	static int SkillDrawCnt = 0;


	///스킬을 사용할시 일어나는 페인트		//1, 4번만 가지고 있음
	if (skillPaint && (monsterType == 1 || monsterType == 4))
	{

		if (monsterType == 1)
			hBitmap = (HBITMAP)LoadBitmap(hInst, MAKEINTRESOURCE(IDB_MONSTER1SKILL));		//이미지 설정
		else if (monsterType == 4)
			hBitmap = (HBITMAP)LoadBitmap(hInst, MAKEINTRESOURCE(IDB_MONSTER4SKILL));
		else
			hBitmap = CreateCompatibleBitmap(bufferdc, 0, 0);							//잘못된 타입일 경우 이미지를 생성하지 않는다

		memdc = CreateCompatibleDC(bufferdc);
		SelectObject(memdc, hBitmap);												//이미지 로드	

		GetObject(hBitmap, sizeof(BITMAP), &bmp);									//이미지 크기 가져오기
		mWidth = bmp.bmWidth;
		mHeight = bmp.bmHeight;

		TransparentBlt(bufferdc, ObjectRect.left, ObjectRect.top, ObjectSize.cx, ObjectSize.cy, memdc, mWidth / 4 * SkillDrawCnt, mHeight / 2, mWidth / 4, mHeight / 2, RGB(0, 255, 255));
		SkillDrawCnt++;

		if (SkillDrawCnt > 3)
		{
			SkillDrawCnt = 0;
			skillPaint = false;
		}

	}

	else
	{
		////몬스터 타입에 따른 리소스 설정
		if (monsterType == 1)
			hBitmap = (HBITMAP)LoadBitmap(hInst, MAKEINTRESOURCE(IDB_MONSTER1));		//이미지 설정
		else if (monsterType == 2)
			hBitmap = (HBITMAP)LoadBitmap(hInst, MAKEINTRESOURCE(IDB_MONSTER2));		//이미지 설정
		else if (monsterType == 3)
			hBitmap = (HBITMAP)LoadBitmap(hInst, MAKEINTRESOURCE(IDB_MONSTER3));		//이미지 설정
		else if (monsterType == 4)
			hBitmap = (HBITMAP)LoadBitmap(hInst, MAKEINTRESOURCE(IDB_MONSTER4));		//이미지 설정
		else
			hBitmap = CreateCompatibleBitmap(bufferdc, 0, 0);							//잘못된 타입일 경우 이미지를 생성하지 않는다

		memdc = CreateCompatibleDC(bufferdc);
		SelectObject(memdc, hBitmap);												//이미지 로드	

		GetObject(hBitmap, sizeof(BITMAP), &bmp);									//이미지 크기 가져오기
		mWidth = bmp.bmWidth;
		mHeight = bmp.bmHeight;

		TransparentBlt(bufferdc, ObjectRect.left, ObjectRect.top, ObjectSize.cx, ObjectSize.cy,
			memdc, mWidth / 4 * BodyDrawCnt, mHeight / 2, mWidth / 4, mHeight / 2, RGB(0, 255, 255));
		
		BodyDrawCnt++;

		if (BodyDrawCnt > 3)
		{
			BodyDrawCnt = 0;
		}
	 
		//다른애들 스킬은 나중에 생각좀
	}

	DeleteObject(hBitmap);
	DeleteDC(memdc);

};

// 멤버에 access하기 위한 함수들

void Monster::SetResistance(long RESISTANCEXPOS, long RESISTANCEYPOS){				//저항값 세팅;
	resistanceXpos = RESISTANCEXPOS;
	resistanceYpos = RESISTANCEYPOS;
	
}
void Monster::MoveTo(const long x, const long y){			//이동할 x 방향 , y 방향		
	
}
void Monster::Move(){										//이동							

}

