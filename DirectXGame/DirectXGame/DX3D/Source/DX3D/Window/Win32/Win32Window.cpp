#include <DX3D/Window/Window.h>
#include <Windows.h>
#include <stdexcept>

static LRESULT CALLBACK WindowProcedure(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam) {
	switch (msg) {
	case WM_CLOSE:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hwnd, msg, wparam, lparam);
		break;
	}
}

dx3d::Window::Window(const WindowDesc& desc)
	: Base(desc.base),
	m_Size{ desc.size }
{

	auto registerWindowClassFunction = []() {
		WNDCLASSEX wc{};
		wc.cbSize = sizeof(WNDCLASSEX);
		wc.lpszClassName = L"DX3DWindow";
		wc.lpfnWndProc = &WindowProcedure;
		return RegisterClassEx(&wc);
		};

	static const auto windowClassId = std::invoke(registerWindowClassFunction);
	

	if (!windowClassId) DX3DLogErrorAndThrow("RegisterClassEx failed.");

	RECT rc{ 0,0,m_Size.width,m_Size.height };
	AdjustWindowRect(&rc, WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU, false);


	m_Handle = CreateWindowEx(NULL, MAKEINTATOM(windowClassId), L"PardCode | C++ 3D Game Tutorial Series",
		WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU,
		CW_USEDEFAULT, CW_USEDEFAULT,
		rc.right - rc.left, rc.bottom - rc.top,
		NULL, NULL, NULL, NULL);

	if (!m_Handle)DX3DLogErrorAndThrow("CreateWindowEx failed.");

	ShowWindow(static_cast<HWND>(m_Handle), SW_SHOW);
}

dx3d::Window::~Window() {
	DestroyWindow(static_cast<HWND>(m_Handle));
}