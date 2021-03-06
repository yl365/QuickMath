#include "stdafx.h"
#include "QuickMath.h"
#include "external_variables.h"
#include "InitHelpShortcutDialog.h"

LRESULT CALLBACK subDialogProc(HWND hwndDlg, UINT msg, WPARAM wParam, LPARAM lParam) {

	PAINTSTRUCT ps;
	HDC hdc;

	switch (msg) {
	case WM_INITDIALOG: {
		HWND hwndDlgTextBox = CreateWindowW(
			L"EDIT",  // Predefined class; Unicode assumed 
			NULL,      // Button text 
			WS_TABSTOP | WS_VISIBLE | WS_CHILD | ES_READONLY | WS_VSCROLL | ES_LEFT | ES_MULTILINE | ES_AUTOVSCROLL,  // Styles 
			10,         // x position 
			10,         // y position 
			500,        // Button width
			215,        // Button height
			hwndDlg,     // Parent window
			(HMENU)ID_DIALOG_EDIT1,       // No menu.
			hInst,
			NULL);      // Pointer not needed.

		HFONT hFontDlgtextBox = CreateFont(20, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, ANSI_CHARSET,
			OUT_TT_PRECIS, CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY,
			DEFAULT_PITCH | FF_DONTCARE, TEXT("Segoe UI")); 

		SendMessage(hwndDlgTextBox, WM_SETFONT, (WPARAM)hFontDlgtextBox, TRUE);

		WCHAR *shortcuts_explanation = new WCHAR[200];
		LoadStringW(hInst, IDS_SHORTCUTLIST, shortcuts_explanation, 200);
		SendMessage(hwndDlgTextBox, WM_SETTEXT, NULL, (LPARAM)shortcuts_explanation);
		delete[] shortcuts_explanation;
		return TRUE;
	} break;
	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		case IDOK:
			EndDialog(hwndDlg, wParam);
			return TRUE;
		} break;
	case WM_CLOSE:
		EndDialog(hwndDlg, wParam);
		return TRUE;
	}
	return 0;
}

void InitHelpShortcutDialog() {
	CreateDialog(NULL, MAKEINTRESOURCE(IDD_SHORTCUTHELPDIALOG), hWnd, subDialogProc);
}