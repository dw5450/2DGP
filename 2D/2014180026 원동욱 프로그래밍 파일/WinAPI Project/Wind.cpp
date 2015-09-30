#include "stdafx.h"


void Wind::PlusWindGage(double PlusWindGage)
{

	WindGage += PlusWindGage;

	if (WindGage > MaxWindGage)
		WindGage = MaxWindGage;
}

void Wind::Blow(Player * PLAYER, POINT MousePoint, const long x, const long y)
{
	long moveX;                        //캐릭터가 이동할 X 좌표
	long moveY;                        //캐릭터가 이동할 Y 좌표   
	cp.x = MousePoint.x;         cp.y = MousePoint.y;

	if (sqrt(pow((float)x, 2) + pow((float)y, 2)) < MaxBlow)
	{
		ObjectSize.cx = (LONG)sqrt(pow((float)x, 2) + pow((float)y, 2));
		ObjectSize.cy = (LONG)sqrt(pow((float)x, 2) + pow((float)y, 2));

		ObjectRect.left = cp.x - ObjectSize.cx / 2;
		ObjectRect.top = cp.y - ObjectSize.cy / 2;
		ObjectRect.right = cp.x + ObjectSize.cx / 2;
		ObjectRect.bottom = cp.y + ObjectSize.cy / 2;
		moveX = x;
		moveY = y;
	}
	else if (sqrt(pow((float)x, 2) + pow((float)y, 2)) >= MaxBlow)
	{
		ObjectSize.cx = MaxBlow;
		ObjectSize.cy = MaxBlow;

		ObjectRect.left = cp.x - ObjectSize.cx / 2;
		ObjectRect.top = cp.y - ObjectSize.cy / 2;
		ObjectRect.right = cp.x + ObjectSize.cx / 2;
		ObjectRect.bottom = cp.y + ObjectSize.cy / 2;

		moveX = MaxBlow * x / (abs(x) + abs(y));
		moveY = MaxBlow * y / (abs(x) + abs(y));

	}

	if (WindGage - sqrt(pow((float)x, 2) + pow((float)y, 2)) > 0)
	{
		PLAYER->MoveTo(moveX, moveY);
		WindGage -= sqrt(pow((float)x, 2) + pow((float)y, 2));
		DrawWind = true;

		if (x > 0)
			windDirection = 1;
		else if (x < 0)
			windDirection = -1;
		else
			windDirection = 0;
	}
}

void Wind::draw()
{
	HBITMAP hBitmap;                           //이미지를 가져오기 위한 hBitmap;                     //추가된 변수
	BITMAP bmp;                                 //이미지의 크기를 알기 위한 bmp;                     //추가된 변수
	int mWidth, mHeight;                        //이미지의 크기를 저장하기 위한  mWidth, mHeight;;      //추가된 변수
	HDC memdc;                                 //이미지를 임시저장하기 위한 memdc;                  //추가된 변수

	static int drawCnt;                           //몇번 불러진 지를 체크하기 위한 Cnt;

	if (DrawWind)
	{
		hBitmap = (HBITMAP)LoadBitmap(hInst, MAKEINTRESOURCE(IDB_WIND));      //이미지 설정
		memdc = CreateCompatibleDC(bufferdc);
		SelectObject(memdc, hBitmap);                                    //이미지 로드   

		GetObject(hBitmap, sizeof(BITMAP), &bmp);                           //이미지 크기 가져오기
		mWidth = bmp.bmWidth;
		mHeight = bmp.bmHeight;

		if (windDirection < 0)
			TransparentBlt(bufferdc, ObjectRect.left + cameraView.left, ObjectRect.top, ObjectSize.cx, ObjectSize.cy, memdc, mWidth / 4 * drawCnt, mHeight / 2, mWidth / 4, mHeight / 2, RGB(0, 255, 255));
		else if (windDirection > 0)
			TransparentBlt(bufferdc, ObjectRect.left + cameraView.left, ObjectRect.top, ObjectSize.cx, ObjectSize.cy, memdc, mWidth / 4 * drawCnt, 0, mWidth / 4, mHeight / 2, RGB(0, 255, 255));


		drawCnt++;

		if (drawCnt > 3)
		{
			drawCnt = 0;
			DrawWind = false;
		}

	}

	//게이지 출력 부분 추후 수정 필요
	hBitmap = (HBITMAP)LoadBitmap(hInst, MAKEINTRESOURCE(IDB_WINDGAGE));      //이미지 설정
	memdc = CreateCompatibleDC(bufferdc);
	SelectObject(memdc, hBitmap);

	GetObject(hBitmap, sizeof(BITMAP), &bmp);                           //이미지 크기 가져오기
	mWidth = bmp.bmWidth;
	mHeight = bmp.bmHeight;

	TransparentBlt(bufferdc, rectView.right - 100 + cameraView.left, rectView.bottom - MaxWindGage / 4, 40, MaxWindGage / 4, memdc, 0, 0, mWidth / 2, mHeight, RGB(0, 255, 255));
	TransparentBlt(bufferdc, rectView.right - 100 + cameraView.left, rectView.bottom - WindGage / 4, 40, WindGage / 4, memdc, mWidth / 2, 0, mWidth / 2, mHeight, RGB(0, 255, 255));


	DeleteObject(hBitmap);
	DeleteDC(memdc);

}


////사용하지 않는 부분
void Wind::SetResistance(long RESISTANCEXPOS, long RESISTANCEYPOS){}
void Wind::MoveTo(const long x, const long y){}            //이동할 x 방향 , y 방향         //추가된 코드
void Wind::Move(){}                                 //이동                     //추가된 코드
