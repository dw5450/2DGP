#include "stdafx.h"
#include <fstream>
#include <mmsystem.h>

#define OBJECTMAX 255
#define MAXLENGTH 8000
int itemStockCounter = 0;

GameManager::GameManager(){
	
	objectArray = new Object*[OBJECTMAX];

	load(1);
	
};

GameManager::~GameManager(){
		for (int i = 0; i < objectCount; ++i){
			delete objectArray[i];
		}
	delete[] objectArray;
};

void GameManager::crash(){
	bool crash = false;
	for (int i = 0; i < objectCount; ++i){
		Monster* pM;
		pM = dynamic_cast<Monster*>(objectArray[i]);
		if (pM != nullptr){
			if (controlPlayer->crash(pM))
			{
				crash = true;
			}
		}
	}
	if (crash == false)
		controlPlayer->MoveTo(0, gravity);
}
void GameManager::draw(HDC hdc){
	if (controlPlayer->getPlayer().x >= MAXLENGTH - 200){
		switch (stage){
		cameraView.left = 0;
		cameraView.right = rectView.right * 2 / 5;
		case 1:
			stage = 2;		load(stage);		
			PlaySound("20. Cyphers_Theme_of_Charlotte.WAV", NULL, SND_ASYNC | SND_LOOP);
			break;
		case 2:
			stage = 3;		load(stage);
			break;
		case 3 :
			stage = 1;		load(stage);		
			PlaySound("Tranquilly -Night Ver.WAV", NULL, SND_ASYNC | SND_LOOP);
			break;

		}
	}

	static HBITMAP hBitmap1;                     //�̹����� �������� ���� hBitmap;                     //�߰��� ����
	BITMAP bmp;                                 //�̹����� ũ�⸦ �˱� ���� bmp;                     //�߰��� ����
	int mWidth, mHeight;                        //�̹����� ũ�⸦ �����ϱ� ����  mWidth, mHeight;;      //�߰��� ����
	HDC memdc1;									  //�̹����� �ӽ������ϱ� ���� memdc;                  //�߰��� ����

	static HBITMAP hBufferBitmap;                         //�̹����� �������� ���� hBitmap;                     //�߰��� ����

	static BOOL cameraMove;



	bufferdc = CreateCompatibleDC(hdc);
	memdc1 = CreateCompatibleDC(bufferdc);
	//if (hBufferBitmap == NULL)												 //ȭ���� �����ؼ� �ݾƵ�
	hBufferBitmap = CreateCompatibleBitmap(hdc, MAXLENGTH, rectView.bottom);

	SelectObject(bufferdc, hBufferBitmap);

	if (ScreenType == 1)
	{
		hBitmap1 = (HBITMAP)LoadBitmap(hInst, MAKEINTRESOURCE(IDB_STARTSCREEN));		 //��� �̹��� ��������
		SelectObject(memdc1, hBitmap1);
		GetObject(hBitmap1, sizeof(BITMAP), &bmp);                              //�̹��� ���� ũ�� ��������
		mWidth = bmp.bmWidth;
		mHeight = bmp.bmHeight;

		StretchBlt(hdc, 0, 0, rectView.right, rectView.bottom, memdc1, 0, 0, mWidth, mHeight, SRCCOPY);
	}

	else if (ScreenType == 2)
	{
		hBitmap1 = (HBITMAP)LoadBitmap(hInst, MAKEINTRESOURCE(IDB_EXPLAINSCREEN1));		 //��� �̹��� ��������
		SelectObject(memdc1, hBitmap1);
		GetObject(hBitmap1, sizeof(BITMAP), &bmp);                              //�̹��� ���� ũ�� ��������
		mWidth = bmp.bmWidth;
		mHeight = bmp.bmHeight;

		StretchBlt(hdc, 0, 0, rectView.right, rectView.bottom, memdc1, 0, 0, mWidth, mHeight, SRCCOPY);
	}

	else if (ScreenType == 3)
	{
		hBitmap1 = (HBITMAP)LoadBitmap(hInst, MAKEINTRESOURCE(IDB_EXPLAINSCREEN2));		 //��� �̹��� ��������
		SelectObject(memdc1, hBitmap1);
		GetObject(hBitmap1, sizeof(BITMAP), &bmp);                              //�̹��� ���� ũ�� ��������
		mWidth = bmp.bmWidth;
		mHeight = bmp.bmHeight;

		StretchBlt(hdc, 0, 0, rectView.right, rectView.bottom, memdc1, 0, 0, mWidth, mHeight, SRCCOPY);
	}

	else if (ScreenType == 4)
	{
		hBitmap1 = (HBITMAP)LoadBitmap(hInst, MAKEINTRESOURCE(IDB_EXPLAINSCREEN3));		 //��� �̹��� ��������
		SelectObject(memdc1, hBitmap1);
		GetObject(hBitmap1, sizeof(BITMAP), &bmp);                              //�̹��� ���� ũ�� ��������
		mWidth = bmp.bmWidth;
		mHeight = bmp.bmHeight;

		StretchBlt(hdc, 0, 0, rectView.right, rectView.bottom, memdc1, 0, 0, mWidth, mHeight, SRCCOPY);
	}


	else if (ScreenType == 5)
	{
		//if (hBitmap == NULL)	//ȭ���� �����ؼ� �ݾƵ�		
		if (stage == 1)
		{
			hBitmap1 = (HBITMAP)LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BACKGROUND1));		 //��� �̹��� ��������
			//PlaySound("Tranquilly -Night Ver.WAV", NULL, SND_ASYNC | SND_LOOP);
		}
		else if (stage == 2)
		{
			hBitmap1 = (HBITMAP)LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BACKGROUND2));
			//PlaySound("20. Cyphers_Theme_of_Charlotte.WAV", NULL, SND_ASYNC | SND_LOOP);
		}
		else 
			hBitmap1 = (HBITMAP)LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BACKGROUND2));		 //��� �̹��� ��������
		SelectObject(memdc1, hBitmap1);

		GetObject(hBitmap1, sizeof(BITMAP), &bmp);                              //�̹��� ���� ũ�� ��������
		mWidth = bmp.bmWidth;
		mHeight = bmp.bmHeight;

		//����̹��� ũ�� ������ 

		StretchBlt(bufferdc, 0, 0, MAXLENGTH, rectView.bottom, memdc1, 0, 0, mWidth, mHeight, SRCCOPY);

		//����̹��� ȭ�鿡 �׸��� ��

		//StretchBlt(bufferdc, 0, 0, rectView.right, rectView.bottom, memdc2, cameraView.left, cameraView.top, rectView.right, rectView.bottom, SRCCOPY);

		//������Ʈ�� �׸���
		for (int i = 0; i < objectCount; ++i){
			objectArray[i]->draw();
		}

		if (cameraView.left - controlPlayer->getPlayer().x > -250){
			int rightWidth = cameraView.right - cameraView.left;
			//cameraView.left = (controlPlayer->getPlayer().x - 100) ;
			//cameraView.right = cameraView.left + rightWidth;
			cameraView.left -= (cameraView.left - controlPlayer->getPlayer().x + 150) / 10;
		}
		else if (cameraView.right - controlPlayer->getPlayer().x < 0){
			int rightWidth = cameraView.right - cameraView.left;
			cameraView.left += (controlPlayer->getPlayer().x - cameraView.left) * 1 / 50;
			cameraView.right = cameraView.left + rightWidth;
		}


		
		Rectangle(bufferdc, cameraView.left + 100, cameraView.bottom - 60, cameraView.left + 500, cameraView.bottom - 20);

		hBitmap1 = (HBITMAP)LoadBitmap(hInst, MAKEINTRESOURCE(IDB_CHARACTER));		 //��� �̹��� ��������
		SelectObject(memdc1, hBitmap1);

		GetObject(hBitmap1, sizeof(BITMAP), &bmp);                              //�̹��� ���� ũ�� ��������
		mWidth = bmp.bmWidth;
		mHeight = bmp.bmHeight;

		StretchBlt(bufferdc, cameraView.left + 100 + PLAYER->getPlayer().x / 20 - 20, cameraView.bottom - 60, 40, 40, memdc1, mWidth / 4, mHeight / 2, mWidth / 4, mHeight / 2, SRCCOPY);
		DeleteObject(hBitmap1);

		BitBlt(hdc, rectView.left, rectView.top, rectView.right, rectView.bottom, bufferdc, cameraView.left, 0, SRCCOPY);
		// �� �ٲܰ�.
	}

	else if (ScreenType == 6)
	{
		hBitmap1 = (HBITMAP)LoadBitmap(hInst, MAKEINTRESOURCE(IDB_DEADSCREEN));		 //��� �̹��� ��������
		SelectObject(memdc1, hBitmap1);
		GetObject(hBitmap1, sizeof(BITMAP), &bmp);                              //�̹��� ���� ũ�� ��������
		mWidth = bmp.bmWidth;
		mHeight = bmp.bmHeight;

		StretchBlt(hdc, 0, 0, rectView.right, rectView.bottom, memdc1, 0, 0, mWidth, mHeight, SRCCOPY);
	}


	DeleteObject(hBitmap1);
	DeleteDC(memdc1);

	DeleteObject(hBufferBitmap);
	DeleteDC(bufferdc);


};

void GameManager::insertObject(Object* a){
	//�׽�Ʈ��
	objectArray[objectCount++] = a;
};
void GameManager::setPlayer(Player* c){
	controlPlayer = c;
}
void GameManager::setPlayerRes(long x, long y){
	controlPlayer->SetResistance(x, y);
}
void GameManager::load(int st){
	FILE *fp;
	SIZE tempSize;

	cameraView.left = 0;
	cameraView.right = rectView.right * 2 / 5;

	objectCount = 0;
	tempSize.cx = 100, tempSize.cy = 100;
	PLAYER = new Player(150, 150, tempSize);
	
	insertObject(PLAYER);
	setPlayer(PLAYER);
	PLAYER->SetResistance(playerXres, playerYres);

	WIND = new Wind();
	insertObject(WIND);
	if (st == 1){
		PlaySound("Tranquilly -Night Ver.WAV", NULL, SND_ASYNC | SND_LOOP);
		fopen_s(&fp, "stage1.txt", "r");

		for (int i = 0; !feof(fp); ++i){
			int cx, cy, type;
			int objectType;
			SIZE size;
			fscanf(fp, "%d", &objectType);
			if (objectType == 1){		// monster
				fscanf(fp, "%d %d %d %d %d", &cx, &cy, &type, &size.cx, &size.cy);

				insertObject(new Monster(cx, cy, size, type));
			}
			else if (objectType == 2){
				fscanf(fp, "%d %d %d %d %d", &cx, &cy, &type, &size.cx, &size.cy);
				insertObject(new Item(cx, cy, type));
			}
		}
		fclose(fp);
	}
	else if (st == 2){
		PlaySound("20. Cyphers_Theme_of_Charlotte.WAV", NULL, SND_ASYNC | SND_LOOP);
		fopen_s(&fp, "stage2.txt", "r");

		for (int i = 0; !feof(fp); ++i){
			int cx, cy, type;
			int objectType;
			SIZE size;
			fscanf(fp, "%d", &objectType);
			if (objectType == 1){		// monster
				fscanf(fp, "%d %d %d %d %d", &cx, &cy, &type, &size.cx, &size.cy);

				insertObject(new Monster(cx, cy, size, type));
			}
			else if (objectType == 2){
				fscanf(fp, "%d %d %d %d %d", &cx, &cy, &type, &size.cx, &size.cy);
				insertObject(new Item(cx, cy, type));
			}
		}
		fclose(fp);
	}
	else if (st == 3){
		fopen_s(&fp, "stage2.txt", "r");

		for (int i = 0; !feof(fp); ++i){
			int cx, cy, type;
			int objectType;
			SIZE size;
			fscanf(fp, "%d", &objectType);
			if (objectType == 1){		// monster
				fscanf(fp, "%d %d %d %d %d", &cx, &cy, &type, &size.cx, &size.cy);

				insertObject(new Monster(cx, cy, size, type));
			}
			else if (objectType == 2){
				fscanf(fp, "%d %d %d %d %d", &cx, &cy, &type, &size.cx, &size.cy);
				insertObject(new Item(cx, cy, type));
			}
		}
		fclose(fp);
	}
}
