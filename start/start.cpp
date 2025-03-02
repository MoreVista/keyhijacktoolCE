#include <windows.h>
#include <stdafx.h>

// ウィンドウプロシージャ
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
    if (message == WM_HOTKEY) {
        if (wParam == 1) {  
            keybd_event(*出力キーコード*, 0, 0, 0);  // 出力キー押下
            keybd_event(*出力キーコード*, 0, KEYEVENTF_KEYUP, 0);  // 出力キー離す
        }
    }
    return DefWindowProc(hWnd, message, wParam, lParam);
}

// Windows CE / Pocket PC 2003 用の `WinMain`
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow) {
    WNDCLASS wc = { 0 };
    wc.lpfnWndProc = WndProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = L"MyHiddenClass";

    RegisterClass(&wc);
    HWND hWnd = CreateWindow(L"MyHiddenClass", L"", 0, 0, 0, 0, 0, NULL, NULL, hInstance, NULL);

    // 入力キーコードを設定
    RegisterHotKey(hWnd, 1, 0, *入力キーコード*);

    // メッセージループ
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    UnregisterHotKey(hWnd, 1);
    return 0;
}