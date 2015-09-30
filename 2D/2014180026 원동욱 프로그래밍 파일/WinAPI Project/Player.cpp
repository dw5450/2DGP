#include "stdafx.h"
											// 100 �κ��� ���ϴ°����� �ٲ۴�. �ҳ��� ũ��. -> ���� ��������� �������� �ʴ� ������ �ϳ��� ���⶧��.
											// ��ǵ��� �ٲܰŸ� ��������� �����ؾ߰���. �ٵ� ������		//�����Ѵ� �ֳĸ� �ϰ�ͱ� �����̴�! ������
Player::Player(const long x, const long y, const SIZE size){			//int -> long�� ����ȯ �Ͼ�⿡ ���ʿ� long������ ����
	cp.x = x;			cp.y = y;

	ObjectSize = size;

	ObjectRect.left = x - size.cx / 2;
	ObjectRect.top = y - size.cy / 2;
	ObjectRect.right = x + size.cx / 2;
	ObjectRect.bottom = y + size.cy / 2;

};
Player::~Player(){};

bool Player::crash(Monster * MonsterPt)			// ����� �ڵ�
{
	RECT tempRect;										//�浹 ������ �˱� ���� tempRect	//�߰��� ����
	bool crash = false;

	///monsterType�� 1�� ���				-> �߷�����	+ �ð���
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


	//monsterTyped�� 2�� ���				-> �ٶ������� ���� + �ð���

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

	///monsterType�� 3�� ���				-> hp ����			+ �ð���
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

	//���� Ÿ���� 4�ϰ��										//�ð� ����		+ �ð���

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

void Player::crash(Item * Item){			//�浹 üũ (������ ������)		//����� �ڵ�

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

	//�׸��� �κ�

	HBITMAP hBitmap;									//�̹����� �������� ���� hBitmap;							//�߰��� ����
	BITMAP bmp;											//�̹����� ũ�⸦ �˱� ���� bmp;							//�߰��� ����
	int mWidth, mHeight;								//�̹����� ũ�⸦ �����ϱ� ����  mWidth, mHeight;;		//�߰��� ����
	HDC memdc;											//�̹����� �ӽ������ϱ� ���� memdc;						//�߰��� ����
	HBITMAP hRotationBitmap;							//ȸ���� ���� hRotationBitmap							//�߰��� ����
	HDC rotationdc;										//ȸ���� ���� rotationdc;								//�߰��� ����
	hBitmap = (HBITMAP)LoadBitmap(hInst, MAKEINTRESOURCE(IDB_CHARACTER));		//�̹��� ����
	static int drawCnt;									//��� �ҷ��� ���� üũ�ϱ� ���� Cnt;
	

	

	memdc=CreateCompatibleDC (bufferdc);
	SelectObject (memdc, hBitmap);												//�̹��� �ε�	

	GetObject(hBitmap, sizeof(BITMAP), &bmp);									//�̹��� ũ�� ��������
	mWidth = bmp.bmWidth;
	mHeight = bmp.bmHeight;


	rotationdc = CreateCompatibleDC(bufferdc);
	hRotationBitmap = CreateCompatibleBitmap(bufferdc, rectView.right, rectView.bottom);
	SelectObject(rotationdc, hRotationBitmap);		//�̹��� �ε�	

	float degree = 0;										//����
	XFORM xFormRotate;
	SetGraphicsMode(rotationdc, GM_ADVANCED);					 // ��带 ��������.
	xFormRotate.eM11 = (float)cos(degree*3.14 / 180);		// ������ ���Q ���� ��������.
	xFormRotate.eM12 = (float)sin(degree*3.14 / 180);
	xFormRotate.eM21 = (float)-sin(degree*3.14 / 180);
	xFormRotate.eM22 = (float)cos(degree*3.14 / 180);
	xFormRotate.eDx = 00;
	xFormRotate.eDy = 00;
	SetWorldTransform(rotationdc, &xFormRotate);					// �׸� DC�� ���Q�� ��������

	if (SpeedXpos >= 0)
		StretchBlt(rotationdc, 0, 0, rectView.right, rectView.bottom, memdc, mWidth / 4 * drawCnt, mHeight / 2, mWidth / 4, mHeight / 2, SRCCOPY);
	else if (SpeedXpos < 0)
		StretchBlt(rotationdc, 0, 0, rectView.right, rectView.bottom, memdc, mWidth / 4 * drawCnt, 0, mWidth / 4, mHeight / 2, SRCCOPY);

	
	TransparentBlt(bufferdc, ObjectRect.left, ObjectRect.top, ObjectSize.cx, ObjectSize.cy, rotationdc, 0, 0, rectView.right, rectView.bottom, RGB(0, 255, 255));
	

	drawCnt++;

	if (drawCnt > 3)
		drawCnt = 0;

	hBitmap = (HBITMAP)LoadBitmap(hInst, MAKEINTRESOURCE(IDB_HPGAGE));      //�̹��� ����
	memdc = CreateCompatibleDC(bufferdc);
	SelectObject(memdc, hBitmap);

	GetObject(hBitmap, sizeof(BITMAP), &bmp);                           //�̹��� ũ�� ��������
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

//-----------��ǥ���� access�ϱ� ���� �Լ���--------------
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
void Player::SetResistance(long RESISTANCEXPOS, long RESISTANCEYPOS){				//���װ� ����;			
	resistanceXpos = RESISTANCEXPOS;
	resistanceYpos = RESISTANCEYPOS;
}

void Player::MoveTo(const long x, const long y){			//�̵��� x ���� , y ����			

	SpeedXpos += x;
	SpeedYpos += y;

}
void Player::Move(){										//�̵�							

	double tmpResistanceXpos = 0;								//X�� ����	
	double tmpResistanceYpos = 0;								//Y�� ����
	// ���� �߻�
	
	if (SpeedXpos != 0)
		tmpResistanceXpos = SpeedXpos * (resistanceXpos / MAXRESISTANCE);
	if (SpeedYpos != 0)
		tmpResistanceYpos = SpeedYpos * (resistanceYpos / MAXRESISTANCE);

		//���װ� = ���ǵ� * ���׻��;
	SpeedXpos -= tmpResistanceXpos;
	SpeedYpos -= tmpResistanceYpos;
	//�̵�
	cp.x += (long)SpeedXpos;
	cp.y += (long)SpeedYpos;

	
	ObjectRect.left = cp.x - ObjectSize.cx / 2;
	ObjectRect.top = cp.y - ObjectSize.cy / 2;
	ObjectRect.right = cp.x + ObjectSize.cx / 2;
	ObjectRect.bottom = cp.y + ObjectSize.cy / 2;


}
long Player::GetResistance(){								//���� ��������					//�߰��� �ڵ�
	return (long)resistanceXpos;
}
