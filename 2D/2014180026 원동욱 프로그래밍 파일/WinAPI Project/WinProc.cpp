#include "stdafx.h"
#include <fstream>
#include <mmsystem.h>
//
//  함수: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  목적:  주 창의 메시지를 처리합니다.
//
//  WM_COMMAND	- 응용 프로그램 메뉴를 처리합니다.
//  WM_PAINT	- 주 창을 그립니다.
//  WM_DESTROY	- 종료 메시지를 게시하고 반환합니다.
//
//
// -----------전역변수-------------
GameManager GM;
HDC bufferdc;
int gravity = 10;
int playerXres = 20, playerYres = 20;
RECT rectView;												//화면 크기 저장			추가된 변수

BOOL debugMode = TRUE;

HWND mapEditer;
Wind * WIND;												//바람					변경된 변수

Player * PLAYER;
RECT cameraView;
//----------------------------------

// ------------전역함수-------------
BOOL CALLBACK Config(HWND hDlg, UINT iMessage, WPARAM wParam, LPARAM lParam);
//----------------------------------

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	HDC hdc;
	PAINTSTRUCT ps;
	static POINT OldMousePoint;								//이전 마우스 포인트    추가된 변수
	static POINT MousePoint;								//마우스 포인트		   추가된 변수
	static bool Drag;										//드래그 여부 판단      추가된 변수
	static int time1;										//time1 경과 시간	   추가된 변수
	static SIZE tempSize;									//임시 사이즈		   추가된 변수
	static int PlayGame;
	static bool Sound;

	
	//static Monster * MONSTER;
	char tempStr[100];
	//static long experiment;
	
	switch (message)
	{
	case WM_CREATE:
		
		PlayGame = false;
		SetTimer(hWnd, 1, 100, NULL);
		
		GM.SetScreenType(1);
		GetClientRect(hWnd, &rectView);

		cameraView.right = rectView.right * 2 / 5;					// 카메라의 크기는 x축으로 화면의 2/5
		cameraView.bottom = rectView.bottom;
		PlaySound(NULL, 0, 0); // 비동기적 연주 재생 정지
		

		GM.insertObject(PLAYER);
		
		GM.insertObject(WIND);
		
		break;

	case WM_SIZE:
		hdc = GetDC(hWnd);
		GetClientRect(hWnd, &rectView);
		GM.draw(hdc);
		ReleaseDC(hWnd, hdc);
		break;
	case WM_TIMER:
		switch (wParam)
		{
		case 1:

		
			if (PlayGame)
			{
				time1++;

				WIND->PlusWindGage(15);										//윈드 게이지 상승  //딱 중력치 + 원하는 이동 속도 만큼이 적당
				PLAYER->SetTime(PLAYER->GetTime() - 1);

				GM.crash();
				PLAYER->Move();
				//종료체크 부분 시간이 없어서 여기서 만듬
				if (PLAYER->GetEnd())
				{
					PlayGame = false;
					GM.SetScreenType(6);
					PlaySound("last_choice.WAV", NULL, SND_ASYNC | SND_LOOP);
				}
				
			}
			InvalidateRect(hWnd, NULL, false);
		}
	case WM_COMMAND:
		wmId = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		// 메뉴 선택을 구문 분석합니다.
		switch (wmId)
		{
		case ID_CONFIG:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG1), hWnd, Config);
			break;
		case ID_MAPEDIT:
			if (mapEditer == NULL){
				KillTimer(hWnd, 1);
				mapEditer = CreateWindow("MapTool", "맵툴", WS_CHILD | WS_VISIBLE, 0, 0, rectView.right, rectView.bottom, hWnd, NULL, hInst, NULL);
			}
			break;

		case ID_RETURN:
			GM.SetScreenType(1);
			PlaySound(NULL, 0, 0); // 비동기적 연주 재생 정지
			break;
		case ID_STAGE_1:
			GM.setStage(1);
			break;
		case ID_STAGE_2:
			GM.setStage(2);
			break;

		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;


	case WM_CHAR:


	case WM_LBUTTONDOWN:
		Drag = true;

		OldMousePoint.x = LOWORD(lParam);
		OldMousePoint.y = HIWORD(lParam);

		break;

	case WM_LBUTTONUP:
		MousePoint.x = LOWORD(lParam);
		MousePoint.y = HIWORD(lParam);


		///지금 화면에 따라 명령어가 다름
		if (GM.GetScreenType() == 1)
		{
			if (rectView.bottom / 8 * 5 - rectView.bottom / 12 < MousePoint.y && MousePoint.y < rectView.bottom / 8 * 5 + rectView.bottom / 24
				&& rectView.right / 2 - rectView.right / 15 * 1 < MousePoint.x && MousePoint.x < rectView.right / 2 + rectView.right / 6)
			{
				PlayGame = true;
				GM.SetScreenType(5);
				GM.setStage(GM.getStage());

				if (GM.getStage() == 1)
					PlaySound("Tranquilly -Night Ver.WAV", NULL, SND_ASYNC | SND_LOOP);
				if (GM.getStage() == 2)
					PlaySound("20. Cyphers_Theme_of_Charlotte.WAV", NULL, SND_ASYNC | SND_LOOP);
			}

			else if (rectView.bottom / 8 * 6 - rectView.bottom / 12 < MousePoint.y && MousePoint.y < rectView.bottom / 8 * 6 + rectView.bottom / 24
				&& rectView.right / 2 - rectView.right / 15 * 1 < MousePoint.x && MousePoint.x < rectView.right / 2 + rectView.right / 6)
			{
				GM.SetScreenType(2);
			}

			else if (rectView.bottom / 8 * 7 - rectView.bottom / 12 < MousePoint.y && MousePoint.y < rectView.bottom / 8 * 7 + rectView.bottom / 24
				&& rectView.right / 2 - rectView.right / 15 * 1 < MousePoint.x && MousePoint.x < rectView.right / 2 + rectView.right / 6)
			{
				DestroyWindow(hWnd);
			}
		}

		else if (GM.GetScreenType() == 2)
		{
			GM.SetScreenType(3);
				
		}
		else if (GM.GetScreenType() == 3)
		{
			GM.SetScreenType(4);
			PlaySound(NULL, 0, 0); // 비동기적 연주 재생 정지
		}
		else if (GM.GetScreenType() == 4)
		{
			GM.SetScreenType(1);
			PlaySound(NULL, 0, 0); // 비동기적 연주 재생 정지
		}
		else if (PlayGame || GM.GetScreenType() == 5)
			WIND->Blow(PLAYER, MousePoint, MousePoint.x - OldMousePoint.x, MousePoint.y - OldMousePoint.y);
		else if (GM.GetScreenType() == 6){
			//DestroyWindow(hWnd);
			
		}
			

		Drag = false;
		break;

	case WM_MOUSEMOVE:
		if (Drag == true)
		{

		}

		break;

	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		// TODO: 여기에 그리기 코드를 추가합니다;

		if (PlayGame)
			PLAYER->crash(hWnd);

		GM.draw(hdc);

		//디버그용 코드
		if (debugMode && PlayGame){
			wsprintf(tempStr, " SpeedXpos : %d", (int)PLAYER->GetSpeedXpos());
			TextOut(hdc, 0, 0, tempStr, strlen(tempStr));
			wsprintf(tempStr, " SpeedYpos : %d", (int)PLAYER->GetSpeedYpos());
			TextOut(hdc, 0, 20, tempStr, strlen(tempStr));
			wsprintf(tempStr, " WinGage : %d", (int)WIND->GetWindGage());
			TextOut(hdc, 0, 40, tempStr, strlen(tempStr));
			wsprintf(tempStr, " Hp : %d", (int)PLAYER->GetHp());
			TextOut(hdc, 0, 60, tempStr, strlen(tempStr));
			wsprintf(tempStr, " Player xPos : %d", (int)PLAYER->getPlayer().x);
			TextOut(hdc, 0, 80, tempStr, strlen(tempStr));
		}

		if (PlayGame)
		{
			wsprintf(tempStr, " time : %d", (int)PLAYER->GetTime());
			TextOut(hdc, rectView.right / 2, 80, tempStr, strlen(tempStr));
		}


		EndPaint(hWnd, &ps);
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}