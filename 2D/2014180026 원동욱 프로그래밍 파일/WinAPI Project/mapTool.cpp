#include "stdafx.h"
#include <fstream>

#define ID_MONSTER1 100
#define ID_MONSTER2 101
#define ID_MONSTER3 102
#define ID_MONSTER4 103

#define ID_ITEM1 151

#define ID_SAVE 200
#define ID_LOAD 201
#define ID_EXIT 404

//========draw=======
#define ID_SCROLL 500

#define MAXLENGTH 8000

int select;

Object* createdObject[255];						// 새로 만들 오브젝트 관련
int count;
LRESULT CALLBACK mapTool(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam){
	static HWND mapTool_draw,hMonsterButton[4];

	static HBITMAP monster[4];

	FILE* fp;

	static BOOL edit;
	switch (iMessage){
	case WM_CREATE:
		monster[0] = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_MONSTER1_BUTTON));
		monster[1] = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_MONSTER2_BUTTON));
		monster[2] = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_MONSTER3_BUTTON));
		monster[3] = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_MONSTER4_BUTTON));

		mapTool_draw = CreateWindow("mapTool_draw", "그림화면", BS_BITMAP | WS_CHILD | WS_BORDER | WS_VISIBLE, 50, 25, 600, rectView.bottom - 50, hWnd, NULL, hInst, NULL);

		hMonsterButton[0] = CreateWindow("button", "monster1", BS_BITMAP | WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 700, 50, 75, 75, hWnd, (HMENU)ID_MONSTER1, hInst, NULL);
		SendMessage(hMonsterButton[0], BM_SETIMAGE, 0, (LPARAM)monster[0]);
		hMonsterButton[1] = CreateWindow("button", "monster2", BS_BITMAP | WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 700, 150, 75, 75, hWnd, (HMENU)ID_MONSTER2, hInst, NULL);
		SendMessage(hMonsterButton[1], BM_SETIMAGE, 0, (LPARAM)monster[1]);
		hMonsterButton[2] = CreateWindow("button", "monster3", BS_BITMAP | WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 700, 250, 75, 75, hWnd, (HMENU)ID_MONSTER3, hInst, NULL);
		SendMessage(hMonsterButton[2], BM_SETIMAGE, 0, (LPARAM)monster[2]);
		hMonsterButton[3] = CreateWindow("button", "monster4", BS_BITMAP | WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 700, 350, 75, 75, hWnd, (HMENU)ID_MONSTER4, hInst, NULL);
		SendMessage(hMonsterButton[3], BM_SETIMAGE, 0, (LPARAM)monster[3]);

		//CreateWindow("button", "Item1", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 800, 300, 75, 75, hWnd, (HMENU)ID_ITEM1, hInst, NULL);

		CreateWindow("button", "Save", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 800, 100, 75, 50, hWnd, (HMENU)ID_SAVE, hInst, NULL);
		CreateWindow("button", "Load", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 800, 200, 75, 50, hWnd, (HMENU)ID_LOAD, hInst, NULL);
		CreateWindow("button", "Exit", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 800, 300, 75, 75, hWnd, (HMENU)ID_EXIT, hInst, NULL);
		break;
	case WM_COMMAND:
		switch (wParam){
		case ID_MONSTER1:
			select = ID_MONSTER1;
			break;
		case ID_MONSTER2:
			select = ID_MONSTER2;
			break;
		case ID_MONSTER3:
			select = ID_MONSTER3;
			break;
		case ID_MONSTER4:
			select = ID_MONSTER4;
			break;
		case ID_ITEM1:
			select = ID_ITEM1;
			break;
		case ID_SAVE:
			fopen_s(&fp, "stage1.txt", "w");
			for (int i = 0; i < count; ++i){
				Monster* pM = dynamic_cast<Monster*>(createdObject[i]);
				Item* pI = dynamic_cast<Item*>(createdObject[i]);
				if (pM != nullptr){
					fprintf_s(fp, " %d %d %d %d %d %d", 1,pM->cp.x, pM->cp.y, pM->getMonsterType(), pM->ObjectSize.cx, pM->ObjectSize.cy);
				}
				else if (pI != nullptr){
					fprintf_s(fp, "%d %d %d %d %d %d", 2,pI->cp.x, pI->cp.y, pI->getItemType(), pI->ObjectSize.cx, pI->ObjectSize.cy);
				}
			}
			fclose(fp);
			break;
		case ID_LOAD:
			fopen_s(&fp, "stage1.txt", "r");
			
			for (int i = 0; i < count; ++i){
				count = 0;
				delete createdObject[i];
			}// 배열 초기화

			for (int i = 0; !feof(fp); ++i){
				int cx, cy, type;
				int objectType;
				SIZE size;
				fscanf(fp, "%d", &objectType);
				if (objectType==1){		// monster
					fscanf(fp, "%d %d %d %d %d", &cx, &cy, &type, &size.cx, &size.cy);
					
					createdObject[i] = new Monster(cx, cy, size, type);
				}
				else if (objectType == 2){
					fscanf(fp, "%d %d %d %d %d", &cx, &cy, &type, &size.cx, &size.cy);
					createdObject[i] = new Item(cx, cy, type);
				}
				count++;
			}
			InvalidateRect(mapTool_draw, NULL, TRUE);
			fclose(fp);
			break;
		case ID_EXIT:
			for (int i = 0; i < count; ++i)
				delete createdObject[i];
			DestroyWindow(hWnd);
			//CloseWindow(hWnd);
			break;
		}
		break;
	case WM_DESTROY:
		SetTimer(GetParent(hWnd), 1, 100, NULL);
		return 0;
	case WM_MOUSEMOVE:

		break;
	case WM_KEYDOWN:


		break;
	default:
		return DefWindowProc(hWnd, iMessage, wParam, lParam);
	}
	return 0;
}


LRESULT CALLBACK mapTool_draw(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam){
	HDC hdc, memDC, memDC2;
	PAINTSTRUCT ps;

	static RECT rect;

	//--- 스크롤바------
	static HWND scrollBar;
	static int scrollX;
	int tempX;
	//-------------------

	static HBITMAP hBit1, background;
	BITMAP bitsize,bitsize2;

	int mx, my;							// 마우스 좌표
	
	SIZE size;
	
	static HBITMAP monster[4];
	switch (iMessage){
	case WM_CREATE:
		monster[0] = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_MONSTER1_BUTTON));
		monster[1] = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_MONSTER2_BUTTON));
		monster[2] = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_MONSTER3_BUTTON));
		monster[3] = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_MONSTER4_BUTTON));

		background = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BACKGROUND1));
		GetClientRect(hWnd, &rect);

		scrollBar = CreateWindow("scrollbar", NULL, WS_CHILD | WS_VISIBLE | SBS_HORZ,
			0, rect.bottom - 20, rect.right, 20, hWnd, (HMENU)ID_SCROLL, hInst, NULL);
		SetScrollRange(scrollBar, SB_CTL, 0, MAXLENGTH - 800, TRUE);
		SetScrollPos(scrollBar, SB_CTL, 0, TRUE);
		break;
	case WM_HSCROLL:
		if ((HWND)lParam == scrollBar)	tempX = scrollX;
		switch (LOWORD(wParam)){
		case SB_LINELEFT:	tempX = max(0, scrollX - 1);		break;
		case SB_LINERIGHT:	tempX = min(MAXLENGTH, scrollX + 1);	break;
		case SB_PAGELEFT:	tempX = max(0, scrollX - 10);		break;
		case SB_PAGERIGHT:	tempX = min(MAXLENGTH, scrollX + 10);	break;
		case SB_THUMBTRACK:	tempX = HIWORD(wParam);				break;
		}

		scrollX = tempX;
		SetScrollPos((HWND)lParam, SB_CTL, scrollX, TRUE);
		InvalidateRect(hWnd, NULL, TRUE);
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		memDC = CreateCompatibleDC(hdc);
		memDC2 = CreateCompatibleDC(memDC);
		//-------------------배경------------------------------
		//GetObject(background, sizeof(BITMAP), &bitsize);

		(HBITMAP)SelectObject(memDC, background);
		GetObject(background, sizeof(BITMAP), &bitsize);

		StretchBlt(hdc, 0, 0, MAXLENGTH, rect.bottom, memDC, scrollX*bitsize.bmWidth / MAXLENGTH, 0, bitsize.bmWidth, bitsize.bmHeight, SRCCOPY);
		DeleteDC(memDC);
		//-----------------------------------------------------

		//====================오브젝트=========================
		memDC = CreateCompatibleDC(hdc);

		for (int i = 0; i < count; ++i){
			Monster* pM = dynamic_cast<Monster*>(createdObject[i]);
			Item* pI = dynamic_cast<Item*>(createdObject[i]);
			if (pM != nullptr){
				switch (pM->getMonsterType()){
				case 1:
					SelectObject(memDC, monster[0]);
					GetObject(monster[0], sizeof(BITMAP), &bitsize2);
					break;
				case 2:
					SelectObject(memDC, monster[1]);
					GetObject(monster[1], sizeof(BITMAP), &bitsize2);
					break;
				case 3:
					SelectObject(memDC, monster[2]);
					GetObject(monster[2], sizeof(BITMAP), &bitsize2);
					break;
				case 4:
					SelectObject(memDC, monster[3]);
					GetObject(monster[3], sizeof(BITMAP), &bitsize2);
					break;
				}
				TransparentBlt(hdc, pM->cp.x - scrollX, pM->cp.y, pM->ObjectSize.cx, pM->ObjectSize.cy,
						memDC, 0, 0, bitsize2.bmWidth, bitsize2.bmHeight, RGB(0, 0, 0));
			}
			else if (pI != nullptr){
				Ellipse(hdc, pI->cp.x - pI->ObjectSize.cx * bitsize.bmWidth / 8000 - scrollX, pI->cp.y - pI->ObjectSize.cy * bitsize.bmWidth / 8000,
					pI->cp.x + pI->ObjectSize.cx * bitsize.bmWidth / 8000 - scrollX, pI->cp.y + pI->ObjectSize.cy * bitsize.bmWidth / 8000);
			}
		}

		DeleteDC(memDC);
		//=====================================================

		EndPaint(hWnd, &ps);
		break;
	case WM_LBUTTONDOWN:
		// 마우스 좌표
		mx = LOWORD(lParam);
		my = HIWORD(lParam);
		GetObject(background, sizeof(BITMAP), &bitsize);
		switch (select){
		case ID_MONSTER1:
			size.cx = 120;		size.cy = 120;
			createdObject[count++] = new Monster(mx + scrollX, my, size, 1);
			break;
		case ID_MONSTER2:
			size.cx = 120;		size.cy = 120;
			createdObject[count++] = new Monster(mx + scrollX, my, size, 2);
			break;
		case ID_MONSTER3:
			size.cx = 120;		size.cy = 120;
			createdObject[count++] = new Monster(mx + scrollX, my, size, 3);
			break;
		case ID_MONSTER4:
			size.cx = 100;		size.cy = 100;
			createdObject[count++] = new Monster(mx + scrollX, my, size, 4);
			break;
		case ID_ITEM1:
			size.cx = 120;		size.cy = 120;
			createdObject[count++] = new Item(mx + scrollX, my, 1);
			break;
		}
		InvalidateRect(hWnd, NULL, TRUE);
		break;
	case WM_DESTROY:
		return 0;
	default:
		return DefWindowProc(hWnd, iMessage, wParam, lParam);
	}

	return 0;
}