#include "stdafx.h"
#include "Canvas.h"


#include "stdafx.h"
#include "resource.h"
#include "SolidWindow.h"
#include "Debug.h"

LRESULT Canvas::handleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_DESTROY:
		//PostQuitMessage(0);
		return 0;
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		static UINT32 color = 0;
		const UINT32 mask_r = 0xff0000;
		const UINT32 mask_g = 0x00ff00;
		const UINT32 mask_b = 0x0000ff;
		color += 0x010204;

		HDC hdc = BeginPaint(_hwnd, &ps);
		//FillRect(hdc, &ps.rcPaint, CreateSolidBrush(RGB((color & mask_r) >> 16, (color & mask_g) >> 8, color & mask_b)));
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

void Canvas::updateClass(WNDCLASSEXW & wcex)
{
	/*HBRUSH brush = (HBRUSH)(COLOR_WINDOW + 1);
	try {
		auto wnd = query_window(_parent);
		auto hwnd = wnd->getHandler();
		WNDCLASSEX wcex;
		auto ui = dynamic_cast<UIBase*>(wnd);
		if (hwnd) {
			if (GetClassInfoEx(ui->getInstance(), ui->getClassName(), &wcex)) {
				brush = wcex.hbrBackground;
			}
			else {
				auto k = GetLastError();
				k = k + 0;
			}
		}
	} catch (...) {}
	*/
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hIcon = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_ZRECOVERY));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = background;
	wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_ZRECOVERY);
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));
}

void Canvas::bind_event_handler(std::string event_name, IUIElement::EventHandler handler)
{
}

HTMLUI_TypeInfo::UIConstructor Canvas::create_from_html = [](HTMLUI_UIDescriptor& des) -> std::shared_ptr<UIBase> {
	DWORD style = 0;
	if (des.border) {
		style |= WS_BORDER;
	}
	auto ret = std::shared_ptr<UIBase>(new Canvas(des.parent, des.identifer(L"Canvas"), des.position(), style), [](auto& p) {delete (Canvas*)p; });
	
	ret->create();
	return ret;
};
HTMLUI_TypeInfo::UIMatchAttrMap Canvas::match_attributes {
	{"class", "canvas"}
};
HTMLUI_TypeInfo::UISupportedEventsSet Canvas::supported_events{
	
};