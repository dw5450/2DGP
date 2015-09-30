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
		case IDOK: // Ȯ�ι�ư

			playerXres = GetDlgItemInt(hDlg, IDC_PLAYER_XRES, NULL, FALSE);		// �÷��̾��� x���װ� ���������� �޴´�.
			playerYres = GetDlgItemInt(hDlg, IDC_PLAYER_YRES, NULL, FALSE);		// �÷��̾��� y���װ� ���������� �޴´�.
			gravity = GetDlgItemInt(hDlg, IDC_PLAYER_GRAVITY, NULL, FALSE);		// �߷°��� �޴´�.
			
			GM.setPlayerRes(playerXres, playerYres);
			if (SendMessage(hCheckDebug, BM_GETCHECK, 0, 0))							// ����׸�� ��/����
				debugMode = TRUE;
			else
				debugMode = FALSE;
			break;
		case IDCANCEL: // �����ư
			EndDialog(hDlg, 0);
			break;
		}
		break;

	}
	return 0;
}