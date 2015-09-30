#pragma once

#include "Object.h"
#include "resource.h"
#include "Item.h"
#include "Player.h"
#include "Monster.h"
#include "Wind.h"
#include "GameManager.h"
#include <Windows.h>

//��������
extern HINSTANCE hInst;								// ���� �ν��Ͻ��Դϴ�.		 extern Ű���� �𸣰����� �˻� ����
extern HDC bufferdc;								// �ٸ� ���ϵ鿡�� �� �������� �������� ��������, ������۸��� ���� bufferdc;

extern GameManager GM;								// ������ ���ư��� ����� ���� ��ɵ��� ����
extern int itemStockCounter;
extern RECT rectView;								// Ŭ���̾�Ʈ ũ��			�߰��� ����;

extern RECT cameraView;				// 0614 �߰�. ī�޶�. �÷��̾��� �̵��� ���� �����̴� �Ⱥ��̴� �簢��

extern Wind * WIND;										//�ٶ�					����� ����
extern Player* PLAYER;

extern int gravity;
extern int playerXres, playerYres;

extern BOOL debugMode;
