#include "stdafx.h"
#include "resource.h"
#include "SolidWindow.h"
#include "Debug.h"

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}

LRESULT SolidWindow::handleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_DESTROY:
		if (onClose) {
			onClose(this, 0);
		}
		//PostQuitMessage(0);
		return 0;
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(_hwnd, &ps);
		FillRect(hdc, &ps.rcPaint, background);
		EndPaint(_hwnd, &ps);
		return 0;
	}
	case WM_COMMAND:
	{
		int wmId = LOWORD(wParam);
		// Parse the menu selections:
		switch (wmId)
		{
		case IDM_ABOUT:
			DialogBox(_instance, MAKEINTRESOURCE(IDD_ABOUTBOX), _hwnd, About);
			break;
		case IDM_EXIT:
			DestroyWindow(_hwnd);
			break;
		default:
			return DefWindowProc(_hwnd, uMsg, wParam, lParam);
		}
	}
	default:
		return DefWindowProc(_hwnd, uMsg, wParam, lParam);
	}
}

void SolidWindow::updateClass(WNDCLASSEXW & wcex)
{
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hIcon = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_ZRECOVERY));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = background;
	wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_ZRECOVERY);
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));
}
