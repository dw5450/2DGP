#include "stdafx.h"


BOOL CALLBACK Config(HWND hDlg, UINT iMessage, WPARAM wParam, LPARAM lParam){
	
	static HWND hCheckDebug;			// 
	switch (iMessage){
	case WM_INITDIALOG:

		SetDlgItemInt(hDlg, IDC_PLAYER_XRES, playerXres, FALSE);
		SetDlgItemInt(hDlg, IDC_PLAYER_YRES, playerYres, FALSE);
		SetDlgItemInt(hDlg, IDC_PLAYER_GRAVITY, gravity,FALSE);

		hCheckDebug = GetDlgItem(hDlg, IDC_DEBUG);
		if (debugMode)
			SendMessage(hCheckDebug, BM_SETCHECK, BST_CHECKED, 0);

		return true;
	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		case IDOK: // 확인버튼

			playerXres = GetDlgItemInt(hDlg, IDC_PLAYER_XRES, NULL, FALSE);		// 플레이어의 x저항값 전역변수를 받는다.
			playerYres = GetDlgItemInt(hDlg, IDC_PLAYER_YRES, NULL, FALSE);		// 플레이어의 y저항값 전역변수를 받는다.
			gravity = GetDlgItemInt(hDlg, IDC_PLAYER_GRAVITY, NULL, FALSE);		// 중력값을 받는다.
			
			GM.setPlayerRes(playerXres, playerYres);
			if (SendMessage(hCheckDebug, BM_GETCHECK, 0, 0))							// 디버그모드 온/오프
				debugMode = TRUE;
			else
				debugMode = FALSE;
			break;
		case IDCANCEL: // 종료버튼
			EndDialog(hDlg, 0);
			break;
		}
		break;

	}
	return 0;
}