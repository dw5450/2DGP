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
	HBITMAP hBitmap;									//�̹����� �������� ���� hBitmap;							//�߰��� ����
	BITMAP bmp;											//�̹����� ũ�⸦ �˱� ���� bmp;							//�߰��� ����
	int mWidth, mHeight;								//�̹����� ũ�⸦ �����ϱ� ����  mWidth, mHeight;;		//�߰��� ����
	HDC memdc;											//�̹����� �ӽ������ϱ� ���� memdc;						//�߰��� ����

	static int BodyDrawCnt = 0;									//��� �ҷ��� ���� üũ�ϱ� ���� Cnt;
	static int SkillDrawCnt = 0;


	///��ų�� ����ҽ� �Ͼ�� ����Ʈ		//1, 4���� ������ ����
	if (skillPaint && (monsterType == 1 || monsterType == 4))
	{

		if (monsterType == 1)
			hBitmap = (HBITMAP)LoadBitmap(hInst, MAKEINTRESOURCE(IDB_MONSTER1SKILL));		//�̹��� ����
		else if (monsterType == 4)
			hBitmap = (HBITMAP)LoadBitmap(hInst, MAKEINTRESOURCE(IDB_MONSTER4SKILL));
		else
			hBitmap = CreateCompatibleBitmap(bufferdc, 0, 0);							//�߸��� Ÿ���� ��� �̹����� �������� �ʴ´�

		memdc = CreateCompatibleDC(bufferdc);
		SelectObject(memdc, hBitmap);												//�̹��� �ε�	

		GetObject(hBitmap, sizeof(BITMAP), &bmp);									//�̹��� ũ�� ��������
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
		////���� Ÿ�Կ� ���� ���ҽ� ����
		if (monsterType == 1)
			hBitmap = (HBITMAP)LoadBitmap(hInst, MAKEINTRESOURCE(IDB_MONSTER1));		//�̹��� ����
		else if (monsterType == 2)
			hBitmap = (HBITMAP)LoadBitmap(hInst, MAKEINTRESOURCE(IDB_MONSTER2));		//�̹��� ����
		else if (monsterType == 3)
			hBitmap = (HBITMAP)LoadBitmap(hInst, MAKEINTRESOURCE(IDB_MONSTER3));		//�̹��� ����
		else if (monsterType == 4)
			hBitmap = (HBITMAP)LoadBitmap(hInst, MAKEINTRESOURCE(IDB_MONSTER4));		//�̹��� ����
		else
			hBitmap = CreateCompatibleBitmap(bufferdc, 0, 0);							//�߸��� Ÿ���� ��� �̹����� �������� �ʴ´�

		memdc = CreateCompatibleDC(bufferdc);
		SelectObject(memdc, hBitmap);												//�̹��� �ε�	

		GetObject(hBitmap, sizeof(BITMAP), &bmp);									//�̹��� ũ�� ��������
		mWidth = bmp.bmWidth;
		mHeight = bmp.bmHeight;

		TransparentBlt(bufferdc, ObjectRect.left, ObjectRect.top, ObjectSize.cx, ObjectSize.cy,
			memdc, mWidth / 4 * BodyDrawCnt, mHeight / 2, mWidth / 4, mHeight / 2, RGB(0, 255, 255));
		
		BodyDrawCnt++;

		if (BodyDrawCnt > 3)
		{
			BodyDrawCnt = 0;
		}
	 
		//�ٸ��ֵ� ��ų�� ���߿� ������
	}

	DeleteObject(hBitmap);
	DeleteDC(memdc);

};

// ����� access�ϱ� ���� �Լ���

void Monster::SetResistance(long RESISTANCEXPOS, long RESISTANCEYPOS){				//���װ� ����;
	resistanceXpos = RESISTANCEXPOS;
	resistanceYpos = RESISTANCEYPOS;
	
}
void Monster::MoveTo(const long x, const long y){			//�̵��� x ���� , y ����		
	
}
void Monster::Move(){										//�̵�							

}

