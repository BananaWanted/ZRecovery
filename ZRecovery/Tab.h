#pragma once
#include "stdafx.h"
#include "ControlBase.h"
#include "Canvas.h"
#include "HTMLUI.h"

class Tab : public ControlBase, public IUIContainer<Canvas>, public HTMLUI<Tab>
{
	typedef struct {
		TCITEMHEADER header;
		void*  lParam;
	} TabItem;
public:
	Tab(HWND parent, RECT position, DWORD style = 0) :
		ControlBase(position, L"", WS_CHILD | WS_CLIPSIBLINGS | WS_VISIBLE | style, parent, NULL, NULL)
	{
		_window_class = WC_TABCONTROL;
	}
	Tab(HWND parent, DWORD style = 0) :
		ControlBase(RECT{ 0,0,0,0 }, L"", WS_CHILD | WS_CLIPSIBLINGS | WS_VISIBLE | style, parent, NULL, NULL)
	{
		_window_class = WC_TABCONTROL;
		RECT rc;
		GetClientRect(_parent, &rc);
		_position = rc;
	}
	virtual ~Tab() {
		destroy();
	}
		
	void insert(std::wstring name);
	Canvas& at(size_t index);
	Canvas& operator[](size_t index);
	//void insert(std::wstring name, size_t position);

	
private:
	size_t _count = 0;
	std::vector<Canvas> _tab_content;

	// Override IUIElement
public:
	virtual void create();
	virtual void destroy();
	virtual LRESULT handleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);

	// Inherited via IUIContainer
	virtual void insert(Canvas&& item) override;
	virtual size_t count() override;
	virtual void erase(size_t index) override;
	virtual Canvas & back() override;
	virtual Canvas & front() override;
	virtual void clear() override;

	// Inherited via HTMLUI
public:
	virtual void bind_event_handler(std::string event_name, IUIElement::EventHandler handler) override;
	static HTMLUI_TypeInfo::UIConstructor create_from_html;
	static HTMLUI_TypeInfo::UIMatchAttrMap match_attributes;
	static HTMLUI_TypeInfo::UISupportedEventsSet supported_events;
};

