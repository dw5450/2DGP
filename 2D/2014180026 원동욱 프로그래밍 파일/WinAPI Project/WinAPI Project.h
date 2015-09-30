#pragma once

#include "Object.h"
#include "resource.h"
#include "Item.h"
#include "Player.h"
#include "Monster.h"
#include "Wind.h"
#include "GameManager.h"
#include <Windows.h>

//전역변수
extern HINSTANCE hInst;								// 현재 인스턴스입니다.		 extern 키워드 모르겠으면 검색 ㄱㄱ
extern HDC bufferdc;								// 다른 파일들에서 이 변수들을 쓰기위해 선언했음, 더블버퍼링을 위한 bufferdc;

extern GameManager GM;								// 게임이 돌아가게 만드는 각종 기능들을 관리
extern int itemStockCounter;
extern RECT rectView;								// 클라이언트 크기			추가된 변수;

extern RECT cameraView;				// 0614 추가. 카메라. 플레이어의 이동에 따라 움직이는 안보이는 사각형

extern Wind * WIND;										//바람					변경된 변수
extern Player* PLAYER;

extern int gravity;
extern int playerXres, playerYres;

extern BOOL debugMode;
