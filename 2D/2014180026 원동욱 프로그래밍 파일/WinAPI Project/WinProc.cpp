#include "stdafx.h"
#include <fstream>
#include <mmsystem.h>
//
//  �Լ�: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  ����:  �� â�� �޽����� ó���մϴ�.
//
//  WM_COMMAND	- ���� ���α׷� �޴��� ó���մϴ�.
//  WM_PAINT	- �� â�� �׸��ϴ�.
//  WM_DESTROY	- ���� �޽����� �Խ��ϰ� ��ȯ�մϴ�.
//
//
// -----------��������-------------
GameManager GM;
HDC bufferdc;
int gravity = 10;
int playerXres = 20, playerYres = 20;
RECT rectView;												//ȭ�� ũ�� ����			�߰��� ����

BOOL debugMode = TRUE;

HWND mapEditer;
Wind * WIND;												//�ٶ�					����� ����

Player * PLAYER;
RECT cameraView;
//----------------------------------

// ------------�����Լ�-------------
BOOL CALLBACK Config(HWND hDlg, UINT iMessage, WPARAM wParam, LPARAM lParam);
//----------------------------------

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	HDC hdc;
	PAINTSTRUCT ps;
	static POINT OldMousePoint;								//���� ���콺 ����Ʈ    �߰��� ����
	static POINT MousePoint;								//���콺 ����Ʈ		   �߰��� ����
	static bool Drag;										//�巡�� ���� �Ǵ�      �߰��� ����
	static int time1;										//time1 ��� �ð�	   �߰��� ����
	static SIZE tempSize;									//�ӽ� ������		   �߰��� ����
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

		cameraView.right = rectView.right * 2 / 5;					// ī�޶��� ũ��� x������ ȭ���� 2/5
		cameraView.bottom = rectView.bottom;
		PlaySound(NULL, 0, 0); // �񵿱��� ���� ��� ����
		

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

				WIND->PlusWindGage(15);										//���� ������ ���  //�� �߷�ġ + ���ϴ� �̵� �ӵ� ��ŭ�� ����
				PLAYER->SetTime(PLAYER->GetTime() - 1);

				GM.crash();
				PLAYER->Move();
				//����üũ �κ� �ð��� ��� ���⼭ ����
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
		// �޴� ������ ���� �м��մϴ�.
		switch (wmId)
		{
		case ID_CONFIG:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG1), hWnd, Config);
			break;
		case ID_MAPEDIT:
			if (mapEditer == NULL){
				KillTimer(hWnd, 1);
				mapEditer = CreateWindow("MapTool", "����", WS_CHILD | WS_VISIBLE, 0, 0, rectView.right, rectView.bottom, hWnd, NULL, hInst, NULL);
			}
			break;

		case ID_RETURN:
			GM.SetScreenType(1);
			PlaySound(NULL, 0, 0); // �񵿱��� ���� ��� ����
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


		///���� ȭ�鿡 ���� ��ɾ �ٸ�
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
			PlaySound(NULL, 0, 0); // �񵿱��� ���� ��� ����
		}
		else if (GM.GetScreenType() == 4)
		{
			GM.SetScreenType(1);
			PlaySound(NULL, 0, 0); // �񵿱��� ���� ��� ����
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
		// TODO: ���⿡ �׸��� �ڵ带 �߰��մϴ�;

		if (PlayGame)
			PLAYER->crash(hWnd);

		GM.draw(hdc);

		//����׿� �ڵ�
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