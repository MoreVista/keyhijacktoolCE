#include <windows.h>
#include <stdafx.h>

// �E�B���h�E�v���V�[�W��
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
    if (message == WM_HOTKEY) {
        if (wParam == 1) {  
            keybd_event(*�o�̓L�[�R�[�h*, 0, 0, 0);  // �o�̓L�[����
            keybd_event(*�o�̓L�[�R�[�h*, 0, KEYEVENTF_KEYUP, 0);  // �o�̓L�[����
        }
    }
    return DefWindowProc(hWnd, message, wParam, lParam);
}

// Windows CE / Pocket PC 2003 �p�� `WinMain`
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow) {
    WNDCLASS wc = { 0 };
    wc.lpfnWndProc = WndProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = L"MyHiddenClass";

    RegisterClass(&wc);
    HWND hWnd = CreateWindow(L"MyHiddenClass", L"", 0, 0, 0, 0, 0, NULL, NULL, hInstance, NULL);

    // ���̓L�[�R�[�h��ݒ�
    RegisterHotKey(hWnd, 1, 0, *���̓L�[�R�[�h*);

    // ���b�Z�[�W���[�v
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    UnregisterHotKey(hWnd, 1);
    return 0;
}