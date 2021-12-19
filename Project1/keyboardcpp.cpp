#include <Windows.h>
#pragma comment(lib, "key.lib")

extern "C" {
	// ��װ����
	__declspec(dllimport) BOOL InstallHook();
	// ж�ع���
	__declspec(dllimport) BOOL UninstallHook();
}

LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

// ʹ�ô�ӣ�����̨������������ں�����һ��
// ��ں��� 
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPreInstance, LPSTR lpCmdLine, int nCmdShow) {
	// 1. ����
		// 1����ƴ�����
	TCHAR szAppClassName[] = TEXT("DunKaiEDU");
	WNDCLASS wc = { 0 };
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);    // ���ذ�ɫ��ˢ
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);				   // ���ع��
	wc.hIcon = NULL;
	wc.hInstance = hInstance;								   // ��ǰӦ��ʵ�����
	wc.lpfnWndProc = WindowProc;							   // ���ڴ�����
	wc.lpszClassName = szAppClassName;						   // ����������
	wc.style = CS_HREDRAW | CS_VREDRAW;

	// 2��ע�ᴰ����
	RegisterClass(&wc);
	// 3����������
	HWND hWnd = CreateWindow(szAppClassName, TEXT("���̼�¼��"), WS_BORDER | WS_CAPTION | WS_SYSMENU | WS_THICKFRAME | WS_MAXIMIZEBOX | WS_MINIMIZEBOX, 300, 200, 600, 400, NULL, NULL, hInstance, NULL);
	// 4����ʾ���ں͸��´���
	ShowWindow(hWnd, SW_SHOW);
	UpdateWindow(hWnd);
	// 5����Ϣѭ�� 
	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0)) {
		// ���������Ϣת��Ϊ�ַ���Ϣ
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	// 2. HOOK
	// 3. ���� 

	return 0;
}

LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {

	switch (uMsg) {
		case WM_CREATE: {
			InstallHook();
			break;
		}
		case WM_CLOSE: {   // ���ڹر���Ϣ
			DestroyWindow(hWnd);
			break;
		}
		case WM_DESTROY: {   // ����������Ϣ
			UninstallHook();
			PostQuitMessage(0);
			break;
		}
	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}


