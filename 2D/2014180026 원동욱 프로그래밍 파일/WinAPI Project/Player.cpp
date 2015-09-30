#include "stdafx.h"
											// 100 부분을 원하는값으로 바꾼다. 소녀의 크기. -> 굳이 멤버변수로 저장하지 않는 이유는 하나만 쓰기때문.
											// 모션따라 바꿀거면 멤버변수로 저장해야겠지. 근데 귀찮아		//변경한다 왜냐면 하고싶기 때문이다! ㅋㅋㅋ
Player::Player(const long x, const long y, const SIZE size){			//int -> long형 형변환 일어나기에 애초에 long형으로 받음
	cp.x = x;			cp.y = y;

	ObjectSize = size;

	ObjectRect.left = x - size.cx / 2;
	ObjectRect.top = y - size.cy / 2;
	ObjectRect.right = x + size.cx / 2;
	ObjectRect.bottom = y + size.cy / 2;

};
Player::~Player(){};

bool Player::crash(Monster * MonsterPt)			// 변경된 코드
{
	RECT tempRect;										//충돌 면적을 알기 위한 tempRect	//추가된 변수
	bool crash = false;

	///monsterType이 1일 경우				-> 중력증가	+ 팅겨짐
	if (IntersectRect(&tempRect, &ObjectRect, &MonsterPt->ObjectRect) && MonsterPt->getMonsterType() == 1)
	{
		if (SpeedXpos < 0)
		{
			SpeedXpos = -SpeedXpos + resistanceXpos;
			crash = true;
		}

		else if (SpeedXpos > 0)
		{
			SpeedXpos = -SpeedXpos - resistanceXpos;
			crash = true;
		}
		if (SpeedYpos < 0)
		{
			SpeedYpos = -SpeedYpos + resistanceYpos;
			crash = true;
		}
		else if (SpeedYpos > 0)
		{
			SpeedYpos = -SpeedYpos - resistanceYpos;
			crash = true;
		}

		gravity += 2;
	}


	//monsterTyped이 2일 경우				-> 바람게이지 감소 + 팅겨짐

	if (IntersectRect(&tempRect, &ObjectRect, &MonsterPt->ObjectRect) && MonsterPt->getMonsterType() == 2)
	{
		if (SpeedXpos < 0)
		{
			SpeedXpos = -SpeedXpos + resistanceXpos;
			crash = true;
		}

		else if (SpeedXpos > 0)
		{
			SpeedXpos = -SpeedXpos - resistanceXpos;
			crash = true;
		}
		if (SpeedYpos < 0)
		{
			SpeedYpos = -SpeedYpos + resistanceYpos;
			crash = true;
		}
		else if (SpeedYpos > 0)
		{
			SpeedYpos = -SpeedYpos - resistanceYpos;
			crash = true;
		}


		if (WIND->GetWindGage() > 100)
			WIND->PlusWindGage(-100);
	}

	///monsterType이 3일 경우				-> hp 감소			+ 팅겨짐
	if (IntersectRect(&tempRect, &ObjectRect, &MonsterPt->ObjectRect) && MonsterPt->getMonsterType() == 3)
	{
		if (SpeedXpos < 0)
		{
			SpeedXpos = -SpeedXpos + resistanceXpos;
			crash = true;
		}

		else if (SpeedXpos > 0)
		{
			SpeedXpos = -SpeedXpos - resistanceXpos;
			crash = true;
		}
		if (SpeedYpos < 0)
		{
			SpeedYpos = -SpeedYpos + resistanceYpos;
			crash = true;
		}
		else if (SpeedYpos > 0)
		{
			SpeedYpos = -SpeedYpos - resistanceYpos;
			crash = true;
		}


		Hp -= 100;

		if (Hp < 0)
			end = true;
	}

	//몬스터 타입이 4일경우										//시간 감소		+ 팅겨짐

	if (IntersectRect(&tempRect, &ObjectRect, &MonsterPt->ObjectRect) && MonsterPt->getMonsterType() == 4)
	{
		if (SpeedXpos < 0)
		{
			SpeedXpos = -SpeedXpos + resistanceXpos;
			crash = true;
		}

		else if (SpeedXpos > 0)
		{
			SpeedXpos = -SpeedXpos - resistanceXpos;
			crash = true;
		}
		if (SpeedYpos < 0)
		{
			SpeedYpos = -SpeedYpos + resistanceYpos;
			crash = true;
		}
		else if (SpeedYpos > 0)
		{
			SpeedYpos = -SpeedYpos - resistanceYpos;
			crash = true;
		}


		Time -= 100;

		if (Time < 0)
			end = true;
	}




	if (crash == true)
		MonsterPt->skillPaint = true;
	
	else {}

	return crash;
}

void Player::crash(Item * Item){			//충돌 체크 (아이템 포인터)		//변경된 코드

}

void Player::crash(HWND hWnd)
{
	RECT rectView;
	GetClientRect(hWnd, &rectView);

	if (0 > cp.x - ObjectSize.cx / 2 && SpeedXpos <= 0)
	{
		SpeedXpos = -SpeedXpos;
		cp.x = rectView.left + ObjectSize.cx / 2;
		ObjectRect.left = cp.x - ObjectSize.cx / 2;
		ObjectRect.right = cp.x + ObjectSize.cx / 2;
	}
	/*else if (28000 < cp.x + ObjectSize.cx / 2 && SpeedXpos >= 0)
	{
		SpeedXpos = -SpeedXpos;
		cp.x = rectView.right - ObjectSize.cx / 2;
		ObjectRect.left = cp.x - ObjectSize.cx / 2;
		ObjectRect.right = cp.x + ObjectSize.cx / 2;
	}*/

	if (-100 > cp.y - ObjectSize.cy / 2 && SpeedYpos <= 0)
	{
		SpeedYpos = -SpeedYpos;
		cp.y = rectView.top + ObjectSize.cy / 2;
		ObjectRect.top = cp.y - ObjectSize.cy / 2;
		ObjectRect.bottom = cp.y + ObjectSize.cy / 2;
	}

	else if (rectView.bottom < cp.y + ObjectSize.cy / 2 && SpeedYpos >= 0)
	{
		SpeedYpos = -SpeedYpos;
		cp.y = rectView.bottom - ObjectSize.cy / 2;
		ObjectRect.top = cp.y - ObjectSize.cy / 2;
		ObjectRect.bottom = cp.y + ObjectSize.cy / 2;

		end = true;
	}

}
void Player::draw(){									

	//그리는 부분

	HBITMAP hBitmap;									//이미지를 가져오기 위한 hBitmap;							//추가된 변수
	BITMAP bmp;											//이미지의 크기를 알기 위한 bmp;							//추가된 변수
	int mWidth, mHeight;								//이미지의 크기를 저장하기 위한  mWidth, mHeight;;		//추가된 변수
	HDC memdc;											//이미지를 임시저장하기 위한 memdc;						//추가된 변수
	HBITMAP hRotationBitmap;							//회전을 위한 hRotationBitmap							//추가된 변수
	HDC rotationdc;										//회전을 위한 rotationdc;								//추가된 변수
	hBitmap = (HBITMAP)LoadBitmap(hInst, MAKEINTRESOURCE(IDB_CHARACTER));		//이미지 설정
	static int drawCnt;									//몇번 불러진 지를 체크하기 위한 Cnt;
	

	

	memdc=CreateCompatibleDC (bufferdc);
	SelectObject (memdc, hBitmap);												//이미지 로드	

	GetObject(hBitmap, sizeof(BITMAP), &bmp);									//이미지 크기 가져오기
	mWidth = bmp.bmWidth;
	mHeight = bmp.bmHeight;


	rotationdc = CreateCompatibleDC(bufferdc);
	hRotationBitmap = CreateCompatibleBitmap(bufferdc, rectView.right, rectView.bottom);
	SelectObject(rotationdc, hRotationBitmap);		//이미지 로드	

	float degree = 0;										//각도
	XFORM xFormRotate;
	SetGraphicsMode(rotationdc, GM_ADVANCED);					 // 모드를 설정핚다.
	xFormRotate.eM11 = (float)cos(degree*3.14 / 180);		// 적용핛 변홖 값을 설정핚다.
	xFormRotate.eM12 = (float)sin(degree*3.14 / 180);
	xFormRotate.eM21 = (float)-sin(degree*3.14 / 180);
	xFormRotate.eM22 = (float)cos(degree*3.14 / 180);
	xFormRotate.eDx = 00;
	xFormRotate.eDy = 00;
	SetWorldTransform(rotationdc, &xFormRotate);					// 그릴 DC에 변홖을 적용핚다

	if (SpeedXpos >= 0)
		StretchBlt(rotationdc, 0, 0, rectView.right, rectView.bottom, memdc, mWidth / 4 * drawCnt, mHeight / 2, mWidth / 4, mHeight / 2, SRCCOPY);
	else if (SpeedXpos < 0)
		StretchBlt(rotationdc, 0, 0, rectView.right, rectView.bottom, memdc, mWidth / 4 * drawCnt, 0, mWidth / 4, mHeight / 2, SRCCOPY);

	
	TransparentBlt(bufferdc, ObjectRect.left, ObjectRect.top, ObjectSize.cx, ObjectSize.cy, rotationdc, 0, 0, rectView.right, rectView.bottom, RGB(0, 255, 255));
	

	drawCnt++;

	if (drawCnt > 3)
		drawCnt = 0;

	hBitmap = (HBITMAP)LoadBitmap(hInst, MAKEINTRESOURCE(IDB_HPGAGE));      //이미지 설정
	memdc = CreateCompatibleDC(bufferdc);
	SelectObject(memdc, hBitmap);

	GetObject(hBitmap, sizeof(BITMAP), &bmp);                           //이미지 크기 가져오기
	mWidth = bmp.bmWidth;
	mHeight = bmp.bmHeight;

	TransparentBlt(bufferdc, rectView.right - 140 + cameraView.left, rectView.bottom - 1000 / 4, 40, 1000 / 4, memdc, 0, 0, mWidth / 2, mHeight, RGB(0, 255, 255));
	TransparentBlt(bufferdc, rectView.right - 140 + cameraView.left, rectView.bottom - Hp / 4, 40, Hp / 4, memdc, mWidth / 2, 0, mWidth / 2, mHeight, RGB(0, 255, 255));


	DeleteObject(hBitmap);
	DeleteDC(memdc);

	DeleteObject(hRotationBitmap);
	DeleteDC(rotationdc);
	DeleteObject(hBitmap);
	DeleteDC(memdc);
};

//-----------좌표값에 access하기 위한 함수들--------------
const POINT Player::getPlayer(){
	POINT tp;
	tp.x = cp.x;			tp.y = cp.y;

	return tp;
};
void Player::putPlayer(const int x, const int y){
	cp.x = x;			cp.y = y;
};
//----------------------------------------------------------

//----------------------------------------------------------
void Player::SetResistance(long RESISTANCEXPOS, long RESISTANCEYPOS){				//저항값 세팅;			
	resistanceXpos = RESISTANCEXPOS;
	resistanceYpos = RESISTANCEYPOS;
}

void Player::MoveTo(const long x, const long y){			//이동할 x 방향 , y 방향			

	SpeedXpos += x;
	SpeedYpos += y;

}
void Player::Move(){										//이동							

	double tmpResistanceXpos = 0;								//X축 저항	
	double tmpResistanceYpos = 0;								//Y축 저항
	// 저항 발생
	
	if (SpeedXpos != 0)
		tmpResistanceXpos = SpeedXpos * (resistanceXpos / MAXRESISTANCE);
	if (SpeedYpos != 0)
		tmpResistanceYpos = SpeedYpos * (resistanceYpos / MAXRESISTANCE);

		//저항값 = 스피드 * 저항상수;
	SpeedXpos -= tmpResistanceXpos;
	SpeedYpos -= tmpResistanceYpos;
	//이동
	cp.x += (long)SpeedXpos;
	cp.y += (long)SpeedYpos;

	
	ObjectRect.left = cp.x - ObjectSize.cx / 2;
	ObjectRect.top = cp.y - ObjectSize.cy / 2;
	ObjectRect.right = cp.x + ObjectSize.cx / 2;
	ObjectRect.bottom = cp.y + ObjectSize.cy / 2;


}
long Player::GetResistance(){								//저항 가져오기					//추가된 코드
	return (long)resistanceXpos;
}
