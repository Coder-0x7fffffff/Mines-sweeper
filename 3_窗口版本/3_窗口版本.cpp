// 3_窗口版本.cpp : 定义应用程序的入口点。
//

#include "stdafx.h"
#include "3_窗口版本.h"
#include "CGame.h"
#include "define.h"

#define MAX_LOADSTRING 100

// 全局变量:
CGame *game;
HINSTANCE hInst;                                // 当前实例
WCHAR szTitle[MAX_LOADSTRING];                  // 标题栏文本
WCHAR szWindowClass[MAX_LOADSTRING];            // 主窗口类名

// 此代码模块中包含的函数的前向声明:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: 在此处放置代码。

    // 初始化全局字符串
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_MY3, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // 执行应用程序初始化:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_MY3));

    MSG msg;

    // 主消息循环:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}



//
//  函数: MyRegisterClass()
//
//  目标: 注册窗口类。
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MY3));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = NULL;
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   函数: InitInstance(HINSTANCE, int)
//
//   目标: 保存实例句柄并创建主窗口
//
//   注释:
//
//        在此函数中，我们在全局变量中保存实例句柄并
//        创建和显示主程序窗口。
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // 将实例句柄存储在全局变量中

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      20, 20, WND_WIDE, WND_WIDE, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  函数: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  目标: 处理主窗口的消息。
//
//  WM_COMMAND  - 处理应用程序菜单
//  WM_PAINT    - 绘制主窗口
//  WM_DESTROY  - 发送退出消息并返回
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	static HWND button_start = NULL;
	static HWND restart_start = NULL;
	static HWND set_level_start = NULL;
	static bool l_down = false, r_down = false;
	switch (message)
	{
	case WM_CREATE:
	{
		game = new CGame;
		restart_start = CreateWindow(TEXT("BUTTON"), TEXT("重新开始"), WS_CHILD | WS_VISIBLE, WND_FRAME_GAP + WND_FRAME_GAP / 5 + (WND_WIDE - WND_FRAME_GAP * 2) / 3 * 1, WND_HEIGHT - GetSystemMetrics(SM_CYSIZE) - WND_FRAME_GAP, (WND_WIDE - WND_FRAME_GAP * 2) / 3 - WND_FRAME_GAP / 5 * 2, WND_FRAME_GAP / 5 * 3, hWnd, (HMENU)2, NULL, NULL);
		set_level_start = CreateWindow(TEXT("BUTTON"), TEXT("游戏难度:简单"), WS_CHILD | WS_VISIBLE, WND_FRAME_GAP + WND_FRAME_GAP / 5 + (WND_WIDE - WND_FRAME_GAP * 2) / 3 * 2, WND_HEIGHT - GetSystemMetrics(SM_CYSIZE) - WND_FRAME_GAP, (WND_WIDE - WND_FRAME_GAP * 2) / 3 - WND_FRAME_GAP / 5 * 2, WND_FRAME_GAP / 5 * 3, hWnd, (HMENU)3, NULL, NULL);
		break;
	}
	case WM_LBUTTONDOWN:
		l_down = true;
		if (r_down)
		{
			int x = LOWORD(lParam);
			int y = HIWORD(lParam);
			x -= WND_FRAME_GAP;
			y -= WND_FRAME_GAP - GetSystemMetrics(SM_CYSIZE);
			int block_wide = (WND_WIDE - WND_FRAME_GAP * 2) / game->GetMapWide();
			int zx = x / block_wide + 1;
			int zy = y / block_wide + 1;
			game->LROpen(zx, zy);
		}
		break;
	case WM_RBUTTONDOWN:
		r_down = true;
		if (l_down)
		{
			int x = LOWORD(lParam);
			int y = HIWORD(lParam);
			x -= WND_FRAME_GAP;
			y -= WND_FRAME_GAP - GetSystemMetrics(SM_CYSIZE);
			int block_wide = (WND_WIDE - WND_FRAME_GAP * 2) / game->GetMapWide();
			int zx = x / block_wide + 1;
			int zy = y / block_wide + 1;
			game->LROpen(zx, zy);
		}
		break;
	case WM_LBUTTONUP:
		{
			l_down = false;
			int x = LOWORD(lParam);
			int y = HIWORD(lParam);
			x -= WND_FRAME_GAP;
			y -= WND_FRAME_GAP - GetSystemMetrics(SM_CYSIZE);
			int block_wide = (WND_WIDE - WND_FRAME_GAP * 2) / game->GetMapWide();
			int zx = x / block_wide + 1;
			int zy = y / block_wide + 1;
			game->Open(zx, zy);
			game->Judge();
			if (game->GameEnd() && game->GetAllMine())
			{
				MessageBox(hWnd, TEXT("恭喜！你找到了所有的炸弹~"), TEXT("提示"), MB_OK);
				game->StartGame();
			}
			else if(game->GameEnd())
			{
				MessageBox(hWnd, TEXT("Bomb!"), TEXT("提示"), MB_OK);
				game->StartGame();
			}
			InvalidateRect(hWnd, NULL, TRUE);
			break;
		}
	case WM_RBUTTONUP:
		{
			r_down = false;
			int x = LOWORD(lParam);
			int y = HIWORD(lParam);
			x -= WND_FRAME_GAP;
			y -= WND_FRAME_GAP - GetSystemMetrics(SM_CYSIZE);
			int block_wide = (WND_WIDE - WND_FRAME_GAP * 2) / game->GetMapWide();
			int zx = x / block_wide  + 1;
			int zy = y / block_wide + 1;
			if (!game->IfFlaged(zx,zy))
			{
				game->FlgMine(zx, zy);
				game->Judge();
				if (game->GameEnd() && game->GetAllMine())
				{
					MessageBox(hWnd, TEXT("恭喜！你找到了所有的炸弹~"), TEXT("提示"), MB_OK);
					game->StartGame();
				}
				else if (game->GameEnd())
				{
					MessageBox(hWnd, TEXT("Bomb！踩雷了~"), TEXT("提示"), MB_OK);
					game->StartGame();
				}
			}
			else game->RemoveFlgMine(zx, zy);
			InvalidateRect(hWnd, NULL, TRUE);
			break;
		}
    case WM_COMMAND:
        {
			int id = LOWORD(wParam);
			switch(id)
			{
			case 2:
				game->StartGame();
				InvalidateRect(hWnd, NULL, TRUE);
				break;
			case 3:
				game->LevelUp();
				game->StartGame();
				wchar_t str[50];
				if (game->GetLevel() == 0)
					swprintf_s(str,TEXT( "游戏难度:简单"));
				else if (game->GetLevel() == 1)
					swprintf_s(str, TEXT("游戏难度:中等"));
				else if (game->GetLevel() == 2)
					swprintf_s(str, TEXT("游戏难度:困难"));
				SetWindowText(set_level_start, str);
				InvalidateRect(hWnd, NULL, TRUE);
				break;
			}
        }
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: 在此处添加使用 hdc 的任何绘图代码...
			game->Print(hdc);
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
		delete game;
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}