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

	static HBITMAP hBitmap1;                     //이미지를 가져오기 위한 hBitmap;                     //추가된 변수
	BITMAP bmp;                                 //이미지의 크기를 알기 위한 bmp;                     //추가된 변수
	int mWidth, mHeight;                        //이미지의 크기를 저장하기 위한  mWidth, mHeight;;      //추가된 변수
	HDC memdc1;									  //이미지를 임시저장하기 위한 memdc;                  //추가된 변수

	static HBITMAP hBufferBitmap;                         //이미지를 가져오기 위한 hBitmap;                     //추가된 변수

	static BOOL cameraMove;



	bufferdc = CreateCompatibleDC(hdc);
	memdc1 = CreateCompatibleDC(bufferdc);
	//if (hBufferBitmap == NULL)												 //화면이 정지해서 닫아둠
	hBufferBitmap = CreateCompatibleBitmap(hdc, MAXLENGTH, rectView.bottom);

	SelectObject(bufferdc, hBufferBitmap);

	if (ScreenType == 1)
	{
		hBitmap1 = (HBITMAP)LoadBitmap(hInst, MAKEINTRESOURCE(IDB_STARTSCREEN));		 //배경 이미지 가져오기
		SelectObject(memdc1, hBitmap1);
		GetObject(hBitmap1, sizeof(BITMAP), &bmp);                              //이미지 본래 크기 가져오기
		mWidth = bmp.bmWidth;
		mHeight = bmp.bmHeight;

		StretchBlt(hdc, 0, 0, rectView.right, rectView.bottom, memdc1, 0, 0, mWidth, mHeight, SRCCOPY);
	}

	else if (ScreenType == 2)
	{
		hBitmap1 = (HBITMAP)LoadBitmap(hInst, MAKEINTRESOURCE(IDB_EXPLAINSCREEN1));		 //배경 이미지 가져오기
		SelectObject(memdc1, hBitmap1);
		GetObject(hBitmap1, sizeof(BITMAP), &bmp);                              //이미지 본래 크기 가져오기
		mWidth = bmp.bmWidth;
		mHeight = bmp.bmHeight;

		StretchBlt(hdc, 0, 0, rectView.right, rectView.bottom, memdc1, 0, 0, mWidth, mHeight, SRCCOPY);
	}

	else if (ScreenType == 3)
	{
		hBitmap1 = (HBITMAP)LoadBitmap(hInst, MAKEINTRESOURCE(IDB_EXPLAINSCREEN2));		 //배경 이미지 가져오기
		SelectObject(memdc1, hBitmap1);
		GetObject(hBitmap1, sizeof(BITMAP), &bmp);                              //이미지 본래 크기 가져오기
		mWidth = bmp.bmWidth;
		mHeight = bmp.bmHeight;

		StretchBlt(hdc, 0, 0, rectView.right, rectView.bottom, memdc1, 0, 0, mWidth, mHeight, SRCCOPY);
	}

	else if (ScreenType == 4)
	{
		hBitmap1 = (HBITMAP)LoadBitmap(hInst, MAKEINTRESOURCE(IDB_EXPLAINSCREEN3));		 //배경 이미지 가져오기
		SelectObject(memdc1, hBitmap1);
		GetObject(hBitmap1, sizeof(BITMAP), &bmp);                              //이미지 본래 크기 가져오기
		mWidth = bmp.bmWidth;
		mHeight = bmp.bmHeight;

		StretchBlt(hdc, 0, 0, rectView.right, rectView.bottom, memdc1, 0, 0, mWidth, mHeight, SRCCOPY);
	}


	else if (ScreenType == 5)
	{
		//if (hBitmap == NULL)	//화면이 정지해서 닫아둠		
		if (stage == 1)
		{
			hBitmap1 = (HBITMAP)LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BACKGROUND1));		 //배경 이미지 가져오기
			//PlaySound("Tranquilly -Night Ver.WAV", NULL, SND_ASYNC | SND_LOOP);
		}
		else if (stage == 2)
		{
			hBitmap1 = (HBITMAP)LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BACKGROUND2));
			//PlaySound("20. Cyphers_Theme_of_Charlotte.WAV", NULL, SND_ASYNC | SND_LOOP);
		}
		else 
			hBitmap1 = (HBITMAP)LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BACKGROUND2));		 //배경 이미지 가져오기
		SelectObject(memdc1, hBitmap1);

		GetObject(hBitmap1, sizeof(BITMAP), &bmp);                              //이미지 본래 크기 가져오기
		mWidth = bmp.bmWidth;
		mHeight = bmp.bmHeight;

		//배경이미지 크기 설정용 

		StretchBlt(bufferdc, 0, 0, MAXLENGTH, rectView.bottom, memdc1, 0, 0, mWidth, mHeight, SRCCOPY);

		//배경이미지 화면에 그리기 용

		//StretchBlt(bufferdc, 0, 0, rectView.right, rectView.bottom, memdc2, cameraView.left, cameraView.top, rectView.right, rectView.bottom, SRCCOPY);

		//오브젝트들 그리기
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

		hBitmap1 = (HBITMAP)LoadBitmap(hInst, MAKEINTRESOURCE(IDB_CHARACTER));		 //배경 이미지 가져오기
		SelectObject(memdc1, hBitmap1);

		GetObject(hBitmap1, sizeof(BITMAP), &bmp);                              //이미지 본래 크기 가져오기
		mWidth = bmp.bmWidth;
		mHeight = bmp.bmHeight;

		StretchBlt(bufferdc, cameraView.left + 100 + PLAYER->getPlayer().x / 20 - 20, cameraView.bottom - 60, 40, 40, memdc1, mWidth / 4, mHeight / 2, mWidth / 4, mHeight / 2, SRCCOPY);
		DeleteObject(hBitmap1);

		BitBlt(hdc, rectView.left, rectView.top, rectView.right, rectView.bottom, bufferdc, cameraView.left, 0, SRCCOPY);
		// 로 바꿀것.
	}

	else if (ScreenType == 6)
	{
		hBitmap1 = (HBITMAP)LoadBitmap(hInst, MAKEINTRESOURCE(IDB_DEADSCREEN));		 //배경 이미지 가져오기
		SelectObject(memdc1, hBitmap1);
		GetObject(hBitmap1, sizeof(BITMAP), &bmp);                              //이미지 본래 크기 가져오기
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
	//테스트용
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
