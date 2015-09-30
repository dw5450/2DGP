#include "stdafx.h"


void Wind::PlusWindGage(double PlusWindGage)
{

	WindGage += PlusWindGage;

	if (WindGage > MaxWindGage)
		WindGage = MaxWindGage;
}

void Wind::Blow(Player * PLAYER, POINT MousePoint, const long x, const long y)
{
	long moveX;                        //ĳ���Ͱ� �̵��� X ��ǥ
	long moveY;                        //ĳ���Ͱ� �̵��� Y ��ǥ   
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
	HBITMAP hBitmap;                           //�̹����� �������� ���� hBitmap;                     //�߰��� ����
	BITMAP bmp;                                 //�̹����� ũ�⸦ �˱� ���� bmp;                     //�߰��� ����
	int mWidth, mHeight;                        //�̹����� ũ�⸦ �����ϱ� ����  mWidth, mHeight;;      //�߰��� ����
	HDC memdc;                                 //�̹����� �ӽ������ϱ� ���� memdc;                  //�߰��� ����

	static int drawCnt;                           //��� �ҷ��� ���� üũ�ϱ� ���� Cnt;

	if (DrawWind)
	{
		hBitmap = (HBITMAP)LoadBitmap(hInst, MAKEINTRESOURCE(IDB_WIND));      //�̹��� ����
		memdc = CreateCompatibleDC(bufferdc);
		SelectObject(memdc, hBitmap);                                    //�̹��� �ε�   

		GetObject(hBitmap, sizeof(BITMAP), &bmp);                           //�̹��� ũ�� ��������
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

	//������ ��� �κ� ���� ���� �ʿ�
	hBitmap = (HBITMAP)LoadBitmap(hInst, MAKEINTRESOURCE(IDB_WINDGAGE));      //�̹��� ����
	memdc = CreateCompatibleDC(bufferdc);
	SelectObject(memdc, hBitmap);

	GetObject(hBitmap, sizeof(BITMAP), &bmp);                           //�̹��� ũ�� ��������
	mWidth = bmp.bmWidth;
	mHeight = bmp.bmHeight;

	TransparentBlt(bufferdc, rectView.right - 100 + cameraView.left, rectView.bottom - MaxWindGage / 4, 40, MaxWindGage / 4, memdc, 0, 0, mWidth / 2, mHeight, RGB(0, 255, 255));
	TransparentBlt(bufferdc, rectView.right - 100 + cameraView.left, rectView.bottom - WindGage / 4, 40, WindGage / 4, memdc, mWidth / 2, 0, mWidth / 2, mHeight, RGB(0, 255, 255));


	DeleteObject(hBitmap);
	DeleteDC(memdc);

}


////������� �ʴ� �κ�
void Wind::SetResistance(long RESISTANCEXPOS, long RESISTANCEYPOS){}
void Wind::MoveTo(const long x, const long y){}            //�̵��� x ���� , y ����         //�߰��� �ڵ�
void Wind::Move(){}                                 //�̵�                     //�߰��� �ڵ�
